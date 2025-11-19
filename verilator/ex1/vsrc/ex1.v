/*
基于LUT的MUX模块.
NR_KEY: 键值对数量. 最大可以为2^KEY_LEN. 但一般是稀疏查表...
KEY_LEN: 键的位宽.
DATA_LEN: 数据的位宽.
一个 LUT 的宽度为 (键的位宽+数据位宽) * 键值对数量. 它存储了所有的键值对. 组织形式为: {key[NR_KEY-1], data[NR_KEY-1], key[NR_KEY-2], data[NR_KEY-2], ... , key[0], data[0]}
LUT输入为key. 比较key和LUT中的KEY_LEN个已有key, 输出对应的数据.
LUT就是个 NR_KEY 路 MUX.
HAS_DEFAULT: 是否有默认输出.

该模块是纯组合逻辑实现. 这意味着综合后没有reg. Verilog 的 reg 不代表“寄存器硬件”, 而是代表“能被 always 块驱动的变量”, 即所谓always过程赋值.
*/
module MuxKeyInternal #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1, HAS_DEFAULT = 0) (
  output reg [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  //PAIR_LEN: 键值对位宽. 即键宽+值宽.
  localparam PAIR_LEN = KEY_LEN + DATA_LEN;

  //声明wire数组: 键值对pair_list. 数组长度为NR_KEY, 每个元素宽度为PAIR_LEN.
  // 其实就是声明了 NR_KEY 条宽度为 PAIR_LEN 的导线.
  wire [PAIR_LEN-1:0] pair_list [NR_KEY-1:0];

  wire [KEY_LEN-1:0] key_list [NR_KEY-1:0];
  wire [DATA_LEN-1:0] data_list [NR_KEY-1:0];

 // 连接pair_list, key_list, data_list到LUT的相应位置.
  generate
    for (genvar n = 0; n < NR_KEY; n = n + 1) begin
      assign pair_list[n] = lut[PAIR_LEN*(n+1)-1 : PAIR_LEN*n];
      assign data_list[n] = pair_list[n][DATA_LEN-1:0];
      assign key_list[n]  = pair_list[n][PAIR_LEN-1:DATA_LEN];
    end
  endgenerate
  //lut的输出.
  reg [DATA_LEN-1 : 0] lut_out;
  
  reg hit;  // 是否命中标志位.
  integer i;
  always @(*) begin
    lut_out = 0;
    hit = 0;

    //查找表
    for (i = 0; i < NR_KEY; i = i + 1) begin
      // 复制运算符: {N{expression}} 把`expression`复制N次, 拼接成一个更长的位向量.
      // {DATA_LEN{ key == key_list[i] }}生成一个长度为DATA_LEN的位向量, key匹配时为全1, 否则全0. 作为data的掩码. 然后和data_list[i]按位与, 取出匹配的data[i]. 如果匹配成功, 则取出data_list[i], 否则取出0.    
      lut_out = lut_out | ({DATA_LEN{key == key_list[i]}} & data_list[i]); //循环结束后, lut_out累加了一次, 变成最终输出data.
      hit = hit | (key == key_list[i]); //累加每次循环的key查询结果. 循环结束后如果匹配成功, 则hit应当=1.
    end

    if (!HAS_DEFAULT) out = lut_out;  //若无 未命中时的默认输出, 则直接连线即可. 不匹配out=lut_out=0.
    else out = (hit ? lut_out : default_out); //若有默认输出, 则根据hit信号选择输出.
  end

endmodule


//下面是MuxKey模块的两种封装版本: 带默认输出和不带默认输出.
//不带默认输出的版本.
module MuxKey #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 0) i0 (out, key, {DATA_LEN{1'b0}}, lut);
endmodule



//带默认输出的版本.
module MuxKeyWithDefault #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 1) i0 (out, key, default_out, lut);
endmodule



//ex1: 用上述选择器模板实现2bit 4to1选择器, 选择器有5个2位输入端，分别为X0, X1, X2, X3和Y，输出端为F；X0, X1, X2, X3是四个2位的输入变量。输出F端受控制端Y的控制. 选择开发板上的SW0和SW1作为控制端Y，SW2—SW9作为四个两位数据输入端X0–X3.
module mux4to1_2bit (
  output [1:0] F,
  input [1:0] Y,
  input [1:0] X0,
  input [1:0] X1,
  input [1:0] X2,
  input [1:0] X3
);
  MuxKey #(
    .NR_KEY(4),
    .KEY_LEN(2),
    .DATA_LEN(2)
  ) mux_instance(
    .out(F),
    .key(Y),
    .lut({
        2'b00, X0, // key = 00 → output X0
        2'b01, X1, // key = 01 → output X1
        2'b10, X2, // key = 10 → output X2
        2'b11, X3  // key = 11 → output X3
       })
  );
endmodule


module tb;
  reg [1:0] Y;
  reg [1:0] X0, X1, X2, X3;
  wire [1:0] F;

  mux4to1_2bit uut (
    .F(F),
    .Y(Y),
    .X0(X0),
    .X1(X1),
    .X2(X2),
    .X3(X3)
  );

  initial begin
    // 初始化输入信号
    X0 = 2'b00;
    X1 = 2'b01;
    X2 = 2'b10;
    X3 = 2'b11;

    // 测试不同的选择信号
    Y = 2'b00; #10;
    $display("Y=%b, F=%b", Y, F); // 应输出 X0

    Y = 2'b01; #10;
    $display("Y=%b, F=%b", Y, F); // 应输出 X1

    Y = 2'b10; #10;
    $display("Y=%b, F=%b", Y, F); // 应输出 X2

    Y = 2'b11; #10;
    $display("Y=%b, F=%b", Y, F); // 应输出 X3

    $finish;
  end
  endmodule











