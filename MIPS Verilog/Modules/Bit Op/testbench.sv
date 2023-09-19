module ALU_TB;
  
//reg[15:0] din; //Sign extend
//reg[31:0] din, din2; // ADDER
reg[31:0] din; // SHIFTER

wire [31:0] dout;
  

  
  //SIGN_EXTEND alu_dut(din, dout);
  //ADDER alu_dut(din, din2, dout);
  SHIFTER #(.IN_LEN(26), .OUT_LEN(28)) alu_dut (.in(din), .dout(dout));

  
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
  
  
  task writeSE(input [15:0] dint);
    begin
      din = dint;
    end
  endtask

//     task writeADD(input [31:0] dint, input[31:0] dint2);
//     begin
//       din = dint;
//       din2 = dint2;
//     end
//   endtask


    task writeSH(input [26:0] dint);
    begin
      din = dint;
    end
  endtask


  initial begin
    //All tests gave the expected result

    // #5 write(-16'd8);
    // #5 write(16'd8);

    //#5 writeADD(32'd10, 32'd4);

    #5 writeSH(-26'd8);


  end
    
    
  
endmodule