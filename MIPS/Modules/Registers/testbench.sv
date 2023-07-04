module FileDataReader;

  reg [4:0] a1, a2, a3;
  reg[31:0] wd3;
  reg clkt, we3;
  wire[31:0] rd1, rd2;
  integer i;

  REGISTER_BANK rb_dut(a1, a2, a3, wd3, we3, clkt, rd1, rd2);



  
    task write(input [4:0] a1t, input [4:0]a2t, input[4:0] a3t, input [31:0] wd3t);
      begin
        a1 = a1t;
        a2 = a2t;
        a3 = a3t;
        wd3 = wd3t;
      end
    endtask

  initial begin
    #0 clkt = 1'b0;
    forever #5 clkt =~ clkt;
  end

  // Close file and finish simulation
initial begin
  $dumpfile("dump.vcd"); // Save simulation data in VCD file
  $dumpvars(0, rb_dut);
    for(i = 0; i < 32; i = i + 1)
      $dumpvars(1, rb_dut.registers[i]); // am pierdut 3 ore deoarece am scris rd_dut in loc de rb_dut :/
    
  end

  initial
    #100 $finish;

  initial begin
    #3 write(5'd10, 5'd2, 5'd8, 32'd16); we3 = 1'b0;
    //$display("%d", rb_dut.registers[8]);
    #20 write(5'd10, 5'd2, 5'd8, 32'd16); we3 = 1'b1;

    //$display("%d", rb_dut.registers[8]);

  end

endmodule
