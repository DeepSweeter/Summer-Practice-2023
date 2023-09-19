module FileDataReader;

// reg signed [31:0] data[0:7];
//   reg file_open;
//   integer file;
     integer i;

// reg [31:0] addr;
// wire [31:0] instr;

reg [31:0] din, wd;
reg we, clk;
wire [31:0] dout;

//INSTRUCTION_MEMORY im_dut(addr, instr);
DATA_MEMORY dm_dut(din, wd, we, clk, dout);

initial begin
  #0 clk = 1'b0;
  forever #5 clk =~clk;
end

    task write(input [31:0] dint, input [31:0] wdt, input wet);
      begin
        din= dint;
        wd = wdt;
        we = wet;
      end
    endtask

//Populate addresses

// initial begin
//     for (i=0; i<8; i++) begin
//         data[i] = i*4;
//     end
//     $writememb("instr.txt", data);
// end

  // Close file and finish simulation
initial begin
    $dumpfile("dump.vcd"); // Save simulation data in VCD file
    $dumpvars(0, dm_dut);
    for(i = 0; i < 50; i = i + 1)
      $dumpvars(1, dm_dut.mem[i]);
  end

  initial begin
    // #5 addr = 32'h12;
    // #5 addr = 32'h16;
    #3 write(32'd10, 32'd15, 1'b0);
    #20 write(32'd10, 32'd15, 1'b1);
    #100 $finish;
  end

endmodule
