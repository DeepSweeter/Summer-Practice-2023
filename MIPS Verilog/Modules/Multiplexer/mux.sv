module MUX_5BIT(input [4:0] in1,
                input [4:0] in2,
                input sel,
                output [4:0] dout);

    assign dout = sel ? in2 : in1;

endmodule

module MUX_32BIT(input [31:0] in1,
                 input [31:0] in2,
                 input sel,
                 output [31:0] dout);

    assign dout= sel ? in2 : in1;

endmodule