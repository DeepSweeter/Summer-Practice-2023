module ALU_TB;
  



reg[5:0] opcode; // MUX5
wire MemtoReg,MemWrite,Branch,ALUSrc,RegDst,RegWrite;
  

  

  //MUX_32BIT alu_dut(din, din2, sel, dout);
  CONTROL_UNIT alu_dut(opcode, MemtoReg,MemWrite,Branch,ALUSrc,RegDst,RegWrite);


  
  initial
    begin
      $dumpfile("dump.vcd");
      $dumpvars(0, alu_dut);
    end
  
//   initial begin
//     #0 clkt = 1'b0;
//     forever #5 clkt =~ clkt;
//   end
  
  initial
    #100 $finish;
  
  



    task write(input [6:0] dint);
    begin
      opcode = dint;
    end
  endtask


  initial begin
    //All tests gave the expected result


    #5 write(6'b0);
    #5 write(6'b100_011);
    #5 write(6'b101_011);
    #5 write(6'b000_100);
    #5 write(6'b001_000);




  end
    
    
  
endmodule