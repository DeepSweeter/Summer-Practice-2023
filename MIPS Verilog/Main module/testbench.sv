module MIPS_TESTBENCH;


	reg clk;
  reg reset;
  integer i;

  MIPS mips_dut(clk, reset);
  


  initial begin
    #0 clk = 1'b0;
    forever #5 clk=~clk;
  end
  initial
    #200 $finish;



  // Close file and finish simulation
initial begin
    $dumpfile("dump.vcd"); // Save simulation data in VCD file
  $dumpvars(1);
  for(i = 0 ; i < 32; i= i+1)
    $dumpvars(1, mips_dut.reg_bank.registers[i]);
for(i = 0 ; i < 32; i= i+1)
    $dumpvars(1, mips_dut.dat_mem.mem[i]);

  $dumpvars(1,mips_dut.rs);
  $dumpvars(1,mips_dut.rd);
  $dumpvars(1,mips_dut.rt);
  $dumpvars(1,mips_dut.mux_datamem_out);
  $dumpvars(1, mips_dut.sel_mux_2_out);
  $dumpvars(1, mips_dut.pcout);
  $dumpvars(1, mips_dut.sel_mux_1_out);
  $dumpvars(1, mips_dut.add_address_out);
  $dumpvars(1, mips_dut.jump_address);
  $dumpvars(1, mips_dut.zeroflag);
  $dumpvars(1, mips_dut.opcode);
  $dumpvars(1, mips_dut.funct);
  $dumpvars(1, mips_dut.ALUConOut);
  $dumpvars(1, mips_dut.ALUOp);
  $dumpvars(1, mips_dut.instruction);

  //Control unit variables
  $dumpvars(1, mips_dut.RegDst);
  $dumpvars(1, mips_dut.Jump);
  $dumpvars(1, mips_dut.Branch);
  $dumpvars(1, mips_dut.MemToReg);
  $dumpvars(1, mips_dut.ALUSrc);
  $dumpvars(1, mips_dut.MemWrite);
  $dumpvars(1, mips_dut.RegWrite);
  $dumpvars(1, mips_dut.ALUOp);






  
  end
  
  initial begin
    #0 reset = 1'b1;
    #5 reset = 1'b0;
  end

endmodule
