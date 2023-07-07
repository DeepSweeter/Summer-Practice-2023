module ALU_TB;
  



reg[31:0] din; // MUX5
reg clkt;
wire [31:0] dout;
  

  

  //MUX_32BIT alu_dut(din, din2, sel, dout);
  PC alu_dut(din, clkt, dout);


  
  initial
    begin
      $dumpfile("dump.vcd");
      $dumpvars(0, alu_dut);
    end
  
  initial begin
    #0 clkt = 1'b0;
    forever #5 clkt =~ clkt;
  end
  
  initial
    #100 $finish;
  
  



    task write(input [31:0] dint);
    begin
      din = dint;
    end
  endtask


  initial begin
    //All tests gave the expected result


    #6 write(32'h0040_0000);
    #12 write(32'h0040_0004);




  end
    
    
  
endmodule