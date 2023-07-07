module stack_TB;
  
  reg[1:0] aluopt;
  reg[5:0] functt;
  wire [2:0] alucontrolt;
  

  
  ALUDEC aludec_dut(aluopt, functt, alucontrolt);
  
  initial
    begin
      $dumpfile("dump.vcd");
      $dumpvars(0, aludec_dut);
    end
  
//   initial begin
//     #5 clkt = 1'b1;
//     forever #5 clkt =~ clkt;
//   end
  
  initial
    #900 $finish;
  
  
  task write(input [7:0] din);
    begin
      aluopt = din[7:6];
      functt = din[5:0];
    end
  endtask
  
  
  initial begin
    #7 write(8'b1x_100000);
    #7 write(8'b1x_100010);
    #7 write(8'bx1_xxxxxx);
    #7 write(8'b00_xxxxxx);
    #7 write(8'b1x_100100);
    #7 write(8'b1x_100101);
    #7 write(8'b1x_101010);



  end
    
    
  
endmodule