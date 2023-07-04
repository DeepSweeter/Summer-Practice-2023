module FileDataReader;

// reg signed [31:0] data[0:7];
//   reg file_open;
//   integer file;
//     integer i;

reg [31:0] addr;
wire [31:0] instr;

INSTRUCTION_MEMORY im_dut(addr, instr);



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
    $dumpvars(0, im_dut);
  end

  initial begin
    #5 addr = 32'h12;
    #5 addr = 32'h16;

    #100 $finish;
  end

endmodule
