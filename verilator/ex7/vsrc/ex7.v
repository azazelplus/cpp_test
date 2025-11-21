`timescale 1ns / 1ps
/*
在实际物理键盘测试时，建议先将键盘控制模块的ready、sampling或overflow等重要信号引至顶层模块用LED显示，确保键盘基本通信正常。 然后如果需要测试键码的准确性，可将收到的每个键码用2个七段数码管显示出来。开发板上的6个七段数码管可以显示三位键码，如果每次将前面收到的键码左移，就可以看到历史记录中最新收到的三个键码。 在这种情况下认真反复测试，确保没有丢键码，重复键码的情况。例如按下并放开 A 键一次，七段数码管上应该显示 1C F0 1C 。

上板验收: 实现单个按键的ASCII码显示

七段数码管低两位显示当前按键的键码，中间两位显示对应的ASCII码（转换可以考虑自行设计一个ROM并初始化）。只需完成字符和数字键的输入，不需要实现组合键和小键盘。

当按键松开时，七段数码管的低四位全灭。

七段数码管的高两位显示按键的总次数。按住不放只算一次按键。只考虑顺序按下和放开的情况，不考虑同时按多个键的情况。


*/



// 这是一个FSM的示例. 教你怎麽写fsm.
//其中SimReg, MuxKeyWithDefault, MuxKey...是官方提供的可复用模块.
//.lut({}) 把所有“键值对”拼成一个大括号数组.
module FSM_bin
(
  input   clk, in, reset,
  output reg out
);

parameter[3:0] S0 = 0, S1 = 1, S2 = 2, S3 = 3,
          S4 = 4, S5 = 5, S6 = 6, S7 = 7, S8 = 8;

wire [3:0] state_din, state_dout;
wire state_wen;

assign state_wen = 1;

// 仿真用寄存器.  SimReg#(WIDTH, RESET_VALUE) 实例名 (端口);
// 其中 WIDTH 是寄存器宽度, RESET_VALUE 是复位时的值. 
SimReg#(4,0) state(clk, reset, state_din, state_dout, state_wen);
// 等价于:
//
// module state_equivalent (
//   input  wire        clk,
//   input  wire        reset,
//   input  wire [3:0]  state_din,
//   output wire [3:0]  state_dout,
//   input  wire        state_wen //write enable
// );

//   // 这是寄存器本体（SimReg 内部的寄存器）
//   reg [3:0] q;

//   assign dout = q;

//   always @(posedge clk) begin
//     if (reset)
//       q <= 4'b0000;     // RESET_VAL = 0
//     else if (wen)
//       q <= din;         // 写入下一状态
//   end

// endmodule



// 查表式多路选择器（LUT-based MUX）. 
// MuxKeyWithDefault#(key_width, value_width, num_entries) 实例名 (端口);
// 其中 key_width 是选择信号宽度, value_width 是输出宽度, num_entries 是查找表中键值对的数量.
// 显然, num_entries要小于等于 2^key_width.
// 可以把它理解成 switch-case 的封装版本.
MuxKeyWithDefault#(9, 4, 1) outMux(.out(out), .key(state_dout), .default_out(0), .lut({
  S0, 1'b0,
  S1, 1'b0,
  S2, 1'b0,
  S3, 1'b0,
  S4, 1'b1,
  S5, 1'b0,
  S6, 1'b0,
  S7, 1'b0,
  S8, 1'b1
}));

MuxKeyWithDefault#(9, 4, 4) stateMux(.out(state_din), .key(state_dout), .default_out(S0), .lut({
  S0, in ? S5 : S1,
  S1, in ? S5 : S2,
  S2, in ? S5 : S3,
  S3, in ? S5 : S4,
  S4, in ? S5 : S4,
  S5, in ? S6 : S1,
  S6, in ? S7 : S1,
  S7, in ? S8 : S1,
  S8, in ? S8 : S1
}));

endmodule


// BCD to 7-segment decoder
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



//以下为接收键盘数据的Verilog HDL代码，此代码只负责接收键盘送来的数据，如何识别出按下的到底是什么按键由其他模块来处理。如何显示出这些数据或键符也请读者自行设计.
module ps2_keyboard(clk,clrn,ps2_clk,ps2_data,data,
                    ready,nextdata_n,overflow);
  //clrn: 复位, n有效. (clear negative)
  //ps2_clk: 键盘发出的时钟信号.
  input clk,clrn,ps2_clk,ps2_data;  
  input nextdata_n;
  output [7:0] data;
  output reg ready;
  output reg overflow;     // fifo overflow
  // internal signal, for test
  reg [9:0] buffer;        // ps2_data bits
  reg [7:0] fifo[7:0];     // data fifo
  reg [2:0] w_ptr,r_ptr;   // fifo write and read pointers
  reg [3:0] count;  // count ps2_data bits
  // detect falling edge of ps2_clk
  reg [2:0] ps2_clk_sync;

  always @(posedge clk) begin
      ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};
  end

  wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

  always @(posedge clk) begin
      if (clrn == 0) begin // reset
          count <= 0; w_ptr <= 0; r_ptr <= 0; overflow <= 0; ready<= 0;
      end
      else begin
          if ( ready ) begin // read to output next data
              if(nextdata_n == 1'b0) //read next data
              begin
                  r_ptr <= r_ptr + 3'b1;
                  if(w_ptr==(r_ptr+1'b1)) //empty
                      ready <= 1'b0;
              end
          end
          if (sampling) begin
            if (count == 4'd10) begin
              if ((buffer[0] == 0) &&  // start bit
                  (ps2_data)       &&  // stop bit
                  (^buffer[9:1])) begin      // odd  parity
                  fifo[w_ptr] <= buffer[8:1];  // kbd scan code
                  w_ptr <= w_ptr+3'b1;
                  ready <= 1'b1;
                  overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
              end
              count <= 0;     // for next
            end else begin
              buffer[count] <= ps2_data;  // store ps2_data
              count <= count + 3'b1;
            end
          end
      end
  end
  assign data = fifo[r_ptr]; //always set output data

endmodule




module top(
    input clk,          // 系统时钟
    input rst,          // 复位信号 (高电平有效, 对应 SW0)
    input ps2_clk,      // PS/2 接口时钟信号
    input ps2_data,     // PS/2 接口数据信号
    output [7:0] seg0,  // 七段数码管0 (低位扫描码)
    output [7:0] seg1,  // 七段数码管1 (高位扫描码)
    output [7:0] seg2,  // 七段数码管2 (低位ASCII码)
    output [7:0] seg3,  // 七段数码管3 (高位ASCII码)
    output [7:0] seg4,  // 七段数码管4 (低位按键计数)
    output [7:0] seg5   // 七段数码管5 (高位按键计数)
);

    wire [7:0] data;
    wire ready;
    wire overflow;
    reg nextdata_n;
    
    // ps2_keyboard instantiation.
    // Note: clrn is active low reset. rst is usually active high from button.
    ps2_keyboard inst_ps2_keyboard(
        .clk(clk),
        .clrn(~rst),
        .ps2_clk(ps2_clk),
        .ps2_data(ps2_data),
        .data(data),
        .ready(ready),
        .nextdata_n(nextdata_n),
        .overflow(overflow)
    );

    reg [7:0] cur_key;
    reg [7:0] cur_ascii;
    reg [7:0] count;
    reg [1:0] state; // 0: IDLE, 1: BREAK
    reg display_on;

    wire [7:0] ascii_out;
    scancode_to_ascii lut_ascii(.code(data), .ascii(ascii_out));

    always @(posedge clk) begin
        if (rst) begin
            count <= 0;
            cur_key <= 0;
            cur_ascii <= 0;
            display_on <= 0;
            state <= 0;
            nextdata_n <= 1;
        end else begin
            nextdata_n <= 1; // Default high
            if (ready && nextdata_n) begin // If ready and we haven't acknowledged yet
                nextdata_n <= 0; // Read pulse
                
                if (state == 0) begin // IDLE / EXPECT MAKE
                    if (data == 8'hF0) begin
                        state <= 1; // Break code prefix
                    end else begin
                        // Make code
                        if (!display_on || cur_key != data) begin
                            cur_key <= data;
                            cur_ascii <= ascii_out;
                            if (ascii_out != 0) begin // Only count valid keys
                                count <= count + 1;
                                display_on <= 1;
                            end
                        end
                    end
                end else if (state == 1) begin // BREAK
                    // data is the key being released
                    display_on <= 0;
                    state <= 0;
                end
            end
        end
    end

    // Display logic
    // seg0, seg1: Key Code
    // seg2, seg3: ASCII
    // seg4, seg5: Count

    wire [7:0] seg0_out, seg1_out, seg2_out, seg3_out, seg4_out, seg5_out;

    // Key Code
    display_byte d0(.val(cur_key), .seg_h(seg1_out), .seg_l(seg0_out));
    // ASCII
    display_byte d1(.val(cur_ascii), .seg_h(seg3_out), .seg_l(seg2_out));
    // Count
    display_byte d2(.val(count), .seg_h(seg5_out), .seg_l(seg4_out));

    // Blanking
    assign seg0 = display_on ? seg0_out : 8'hFF;
    assign seg1 = display_on ? seg1_out : 8'hFF;
    assign seg2 = display_on ? seg2_out : 8'hFF;
    assign seg3 = display_on ? seg3_out : 8'hFF;
    assign seg4 = seg4_out; // Count always on
    assign seg5 = seg5_out;

endmodule

//
module display_byte(
    input [7:0] val,
    output [7:0] seg_h,
    output [7:0] seg_l
);
    wire [6:0] h_raw, l_raw;
    
    // high nibble
    bcd7seg h_dec(.b(val[7:4]), .h(h_raw));
    // Map bcd7seg output (G..A) to NVBoard pinout (A..G, DP)
    assign seg_h[7] = h_raw[0]; // A
    assign seg_h[6] = h_raw[1]; // B
    assign seg_h[5] = h_raw[2]; // C
    assign seg_h[4] = h_raw[3]; // D
    assign seg_h[3] = h_raw[4]; // E
    assign seg_h[2] = h_raw[5]; // F
    assign seg_h[1] = h_raw[6]; // G
    assign seg_h[0] = 1;        // DP

    // low nibble
    bcd7seg l_dec(.b(val[3:0]), .h(l_raw));
    assign seg_l[7] = l_raw[0]; // A
    assign seg_l[6] = l_raw[1]; // B
    assign seg_l[5] = l_raw[2]; // C
    assign seg_l[4] = l_raw[3]; // D
    assign seg_l[3] = l_raw[4]; // E
    assign seg_l[2] = l_raw[5]; // F
    assign seg_l[1] = l_raw[6]; // G
    assign seg_l[0] = 1;        // DP
endmodule


//
module scancode_to_ascii(
    input [7:0] code,
    output reg [7:0] ascii
);
    always @(*) begin
        case(code)
            8'h1C: ascii = "A";
            8'h32: ascii = "B";
            8'h21: ascii = "C";
            8'h23: ascii = "D";
            8'h24: ascii = "E";
            8'h2B: ascii = "F";
            8'h34: ascii = "G";
            8'h33: ascii = "H";
            8'h43: ascii = "I";
            8'h3B: ascii = "J";
            8'h42: ascii = "K";
            8'h4B: ascii = "L";
            8'h3A: ascii = "M";
            8'h31: ascii = "N";
            8'h44: ascii = "O";
            8'h4D: ascii = "P";
            8'h15: ascii = "Q";
            8'h2D: ascii = "R";
            8'h1B: ascii = "S";
            8'h2C: ascii = "T";
            8'h3C: ascii = "U";
            8'h2A: ascii = "V";
            8'h1D: ascii = "W";
            8'h22: ascii = "X";
            8'h35: ascii = "Y";
            8'h1A: ascii = "Z";
            8'h45: ascii = "0";
            8'h16: ascii = "1";
            8'h1E: ascii = "2";
            8'h26: ascii = "3";
            8'h25: ascii = "4";
            8'h2E: ascii = "5";
            8'h36: ascii = "6";
            8'h3D: ascii = "7";
            8'h3E: ascii = "8";
            8'h46: ascii = "9";
            default: ascii = 8'h00;
        endcase
    end
endmodule













