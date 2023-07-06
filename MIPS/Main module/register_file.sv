module REGISTER_BANK(
  input [4:0] a1,
  input [4:0] a2,
  input [4:0] a3,
  input [31:0] wd3,
  input we3,
  input clk,
  output [31:0] rd1,
  output [31:0] rd2
);

	integer i;
  reg [31:0] registers [0:31];

  initial for(i = 0; i < 32; i = i + 1)
      registers[i] = 32'b0;

  assign rd1 = (a1 != 0) ? registers[a1] : 0;
  assign rd2 = (a2 != 0) ? registers[a2] : 0;

  always@(posedge clk) begin
    if(we3)
      registers[a3] = (a3 != 0)? wd3 :0;

  end
   
    


endmodule