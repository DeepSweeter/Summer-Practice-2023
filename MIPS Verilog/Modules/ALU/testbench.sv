module ALU_TB;
  
  reg[2:0] alcontrolt;
  reg[31:0] src1, src2;
  wire [31:0] result;
  wire zero;
  

  
  ALU alu_dut(alcontrolt, src1, src2, result, zero);
  
  initial
    begin
      $dumpfile("dump.vcd");
      $dumpvars(0, alu_dut);
    end
  
//   initial begin
//     #5 clkt = 1'b1;
//     forever #5 clkt =~ clkt;
//   end
  
  initial
    #900 $finish;
  
  
  task write(input [2:0] din);
    begin
      alcontrolt = din;
    end
  endtask

  task writeSources(input [31:0] din1, input [31:0] din2);
    begin
        src1 = din1;
        src2 = din2;
    end
  endtask

  initial begin
    //All tests gave the expected result
    #5 writeSources(32'd17, 32'd10); write(3'b010);//27
    #5 write(3'b110); //7
    #5 write(3'b000); //0
    #5 write(3'b001); //27
    #5 write(3'b111); //Zero = 0;
    #5 write(3'b101); //undefined

    #5 writeSources(32'd10, 32'd10); write(3'b111); //Zero = 1; 




  end
    
    
  
endmodule