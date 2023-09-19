module PC(
    input [31:0] in,
    input clk,
  input reset,
    output reg [31:0] dout);

  always@(negedge clk, posedge reset) 
        begin
          if(reset)
            dout <= 32'b0;
          else
            dout <= in;
        end
    
endmodule