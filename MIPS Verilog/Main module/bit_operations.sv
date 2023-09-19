module SIGN_EXTEND(input [15:0] din, output [31:0] dout);
    assign dout = {{16{din[15]}},din[15:0]};
endmodule

module ADDER(input signed[31:0] op1, input signed[31:0] op2, output signed[31:0] dout);
    assign dout = op1 + op2;
endmodule

module SHIFTER #(parameter IN_LEN = 32, parameter OUT_LEN = 32) 
                (input[IN_LEN-1:0] in,
                 output [OUT_LEN-1:0] dout);
    assign dout = in << 2;
endmodule