module PC(
    input [31:0] in,
    input clk,
    output reg [31:0] dout);

    always@(posedge clk) 
        begin
            dout = in;
        end
    
endmodule