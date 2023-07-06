module ALUDEC(input [1:0] aluop, input [5:0] funct, output reg [2:0] alucontrol);
  always@(*)
    casex({aluop, funct})
      8'b00_xxxxxx: alucontrol = 3'b010; 		//add
      8'b01_xxxxxx: alucontrol = 3'b110;    //sub
      8'b1x_100000: alucontrol = 3'b010;    //add
      8'b1x_100010: alucontrol = 3'b110; 		//sub
      8'b1x_100100: alucontrol = 3'b000;			//and
      8'b1x_100101: alucontrol = 3'b001;		//or
      8'b1x_101010: alucontrol = 3'b111;			//set less than
    endcase
  
endmodule
  