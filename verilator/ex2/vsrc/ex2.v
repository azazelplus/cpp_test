/*
decoder
*最后，请读者自行设计一个8-3优先编码器及七段数码管显示.
伊吉斯将另一面白色的帆交给领航，特别交代他在回航的时候，如果帖修斯平安归来，就将这面船帆升起来；要是事与愿违就用黑色的船帆，等于是悬挂出不幸的信号。
*/




module decoder24(
  input logic [1:0]x,
  input logic en,
  output logic [3:0] y
);
  always @(*)
    if(en) begin
      case (x)
        2'b00: y = 4'b0001;
        2'b01: y = 4'b0010; 
        2'b10: y = 4'b0100;
        2'b11: y = 4'b1000;
      endcase
    end
    else
      y = 4'b0000;
endmodule



module decoder38(
  input logic [2:0] x,
  input logic en,
  output logic [7:0] y
);
  integer i;
  always @(*) begin
    y = 8'b0;               // default assignment. 保证所有路径都有意义, 避免锁存器.
    if(en) begin
      for(i = 0; i <= 7; i = i+1)
        y[i] = (x == i);
    end
  end
endmodule




//优先编码器. 优先编码器允许同时在几个输入端有输入信号，即输入不止一个1,编码器按输入信号排定的优先顺序，只对同时输入的几个信号中优先权最高的一个进行编码。
module encoder42_priority(
  input logic [3:0] x,
  input logic en,
  output logic [1:0] y
);
  assign y[1] = (en) & (x[3] | x[2]);
  assign y[0] = (en) & (x[3] | (~x[2] & x[1]));
  
endmodule


//for循环风格.
// i 遍历 0-7
// 检查每一位输入 x[i] 是否为 1。
// 如果是，就把 i 转成 3 位赋值给输出 y
// 遍历从低到高. 也就是最后的最高位优先编码器.
module encoder83_priority(
  input logic [7:0] x,
  input logic en,
  output logic [2:0] y,
  output logic valid //表示输入x是否为非0
);
  integer i;

  assign valid = en & (|x); //输入是否非0

  always @(*) begin
    y = 3'b000; // default assignment.
    if(en) begin
      for(i=0; i<=7; i=i+1) begin
        if(x[i]) y = i[2:0]; //把 i 转成 3 位赋值给输出 y
      end
    end
  end
endmodule


module bcd7seg(
  input  [3:0] b,
  output reg [6:0] h
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
  // switches
  input  wire SW0,
  input  wire SW1,
  input  wire SW2,
  input  wire SW3,
  input  wire SW4,
  input  wire SW5,
  input  wire SW6,
  input  wire SW7,
  input  wire SW8, // enable

  // HEX0数码管
  output wire SEG0A,
  output wire SEG0B,
  output wire SEG0C,
  output wire SEG0D,
  output wire SEG0E,
  output wire SEG0F,
  output wire SEG0G,
  output wire DEC0P     //小数点打算拉高不用
);

  // pack switches
  wire [7:0] SW = {SW7,SW6,SW5,SW4,SW3,SW2,SW1,SW0};

  // 实例化一个encoder83_priority
  wire [2:0] code;
  wire       valid;
  encoder83_priority u_enc (
    .x(SW),
    .en(SW8),
    .y(code),
    .valid(valid)
  );


  // display code (extended to 4 bits)
  wire [3:0] bcd0 = {1'b0, code};
  wire [6:0] h;

  //实例化一个bcd7seg查找表
  bcd7seg u_bcd (
    .b(bcd0),
    .h(h)
  );

  // map segments
  assign SEG0A = h[0];
  assign SEG0B = h[1];
  assign SEG0C = h[2];
  assign SEG0D = h[3];
  assign SEG0E = h[4];
  assign SEG0F = h[5];
  assign SEG0G = h[6];

  // 小数点拉高不用
  assign DEC0P = 1'b1;

endmodule




//booth算法: 补码移位乘

module booth_multiplier(
  input  [3:0] M, //被乘数
  input  [3:0] Q, //乘数
  input        Qn,//附加位
  output [7:0] P  //积
);

endmodule








