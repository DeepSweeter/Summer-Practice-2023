module ALU_TB;
  

// reg[31:0] din, din2; // MUX32
// reg sel;
// wire [31:0] dout;

reg[4:0] din, din2; // MUX5
reg sel;
wire [4:0] dout;
  

  

  //MUX_32BIT alu_dut(din, din2, sel, dout);
  MUX_5BIT alu_dut(din, din2, sel, dout);


  
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
  
  

//     task write(input [31:0] dint, input [31:0] dint2, input selt);
//     begin
//       din = dint;
//       din2 = dint2;
//       sel = selt;
//     end
//   endtask

      task write(input [5:0] dint, input [5:0] dint2, input selt);
    begin
      din = dint;
      din2 = dint2;
      sel = selt;
    end
  endtask


  initial begin
    //All tests gave the expected result


    #5 write(-5'd8, 5'd8, 0);
    #5 write(-5'd8, 5'd8, 1);



  end
    
    
  
endmodule