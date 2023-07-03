module SIGN_EXTEND(input [15:0] din, output [31:0] dout);
    assign dout = {{16{din[15]}},din[15:0]};
endmodule

module ADDER(input[31:0] op1, input [31:0] op2, output [31:0] dout);
    assign dout = op1 + op2;
endmodule

module SHIFTER(input[31:0] in, output [31:0] dout);
    assign dout = in << 2;
endmodule