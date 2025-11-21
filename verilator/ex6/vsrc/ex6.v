/*
请实现一个8位的周期为255的伪随机序列，
以按钮为时钟信号，
并请将8位二进制数以十六进制显示在数码管上，
在DE10-Standard开发板上观察生成的随机数序列。
*/









module lfsr3(
  input clk,
  input rst_n,
  output [2:0] q_out 
);

  //定义三个寄存器, 编号3对应MSB最左边的寄存器. lfsr向右移位.
  //当我们声明reg q, 并在always块中对q<=赋值时, 即生成了一个DFF. 当前周期, q信号的值即为该DFF的输出, 也即上个周期锁存进去的值.
  reg [2:0] q_reg;

  //反馈信号
  wire feedback;

  //反馈逻辑: 2号和0号做XOR, 结果馈入
  assign feedback = q_reg[2] ^ q_reg[0];

  always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      // 复位初始值 101 (二进制 3'b101, q[2]=1, q[0]=1)
      q_reg <= 3'b101;
    end else begin
      //右移位并反馈
      q_reg <= {feedback, q_reg[2:1]};
    end
  end

  //接上输出端口
  assign q_out = q_reg;

endmodule







module lfsr8(
  input logic clk,
  input logic rst_n,
  output logic [7:0] q_out
);




  reg [7:0] q_reg;
  wire feedback;
  wire all_zeros;
  assign feedback = q_reg[7] ^ q_reg[5] ^ q_reg[4] ^ q_reg[3];

  // 检测是否进入全0状态
  assign all_zeros = (q_reg == 8'b0);


  always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      q_reg <= 8'b10101010; // 初始值
    end else if (all_zeros) begin
      q_reg <= 8'b10101010; // 初始值
    end else begin
      q_reg <= {feedback, q_reg[7:1]};
    end
  end
  assign q_out = q_reg;

endmodule



module bcd7seg(
  input  [3:0] b, // 4-bit binary input
  output reg [6:0] h  // 7-segment display output. 顺序是： {a,b,c,d,e,f,g}（从 MSB 到 LSB = 从 a 到 g）.
);
  always @(*) begin
    case (b)
      4'd0: h = 7'b1000000; // 0
      4'd1: h = 7'b1111001; // 1
      4'd2: h = 7'b0100100; // 2
      4'd3: h = 7'b0110000; // 3
      4'd4: h = 7'b0011001; // 4
      4'd5: h = 7'b0010010; // 5
      4'd6: h = 7'b0000010; // 6
      4'd7: h = 7'b1111000; // 7
      4'd8: h = 7'b0000000; // 8
      4'd9: h = 7'b0010000; // 9
      // optional hex letters (useful for debug)
      4'hA: h = 7'b0001000; // A
      4'hB: h = 7'b0000011; // b  (lowercase b)
      4'hC: h = 7'b1000110; // C
      4'hD: h = 7'b0100001; // d  (lowercase d)
      4'hE: h = 7'b0000110; // E
      4'hF: h = 7'b0001110; // F
      default: h = 7'b1111111; // all off (blank)
    endcase
  end
endmodule



module top(
  input  logic BTNC,   // step button (use as clock)
  input  logic SW0,    // reset (active high) - use the first switch for reset

  // HEX0 (lower nibble)
  output logic SEG0A, SEG0B, SEG0C, SEG0D, SEG0E, SEG0F, SEG0G, DEC0P,
  // HEX1 (upper nibble)
  output logic SEG1A, SEG1B, SEG1C, SEG1D, SEG1E, SEG1F, SEG1G, DEC1P
);

  //包装两个数码管的7段显示信号
  logic [6:0] seg0_h;
  logic [6:0] seg1_h;
  assign {DEC0P, SEG0G, SEG0F, SEG0E, SEG0D, SEG0C, SEG0B, SEG0A} = {1'b1, seg0_h};
  assign {DEC1P, SEG1G, SEG1F, SEG1E, SEG1D, SEG1C, SEG1B, SEG1A} = {1'b1, seg1_h};


  // LFSR state register (8-bit)
  logic [7:0] lfsr_out;

  lfsr8 lfsr_inst (
    .clk(BTNC),
    .rst_n(~SW0), // active low reset
    .q_out(lfsr_out)
  );

  // q_out分为两个4bit, 分别表示两个二进制数.
  logic [3:0] low_nibble;
  logic [3:0] high_nibble; 
  assign low_nibble  = lfsr_out[3:0];
  assign high_nibble = lfsr_out[7:4];


  //实例化两个数码管控制单元unit, 接入输入输出.
  bcd7seg u_bcd0 (.b(low_nibble),  .h(seg0_h));
  bcd7seg u_bcd1 (.b(high_nibble), .h(seg1_h));

endmodule








