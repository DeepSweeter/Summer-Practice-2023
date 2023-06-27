module PISO_DUT;
  reg[3:0] dint;
  reg clkt, shift_plt;
  wire doutt;
  
  PISO piso_dut(dint, clkt, shift_plt, doutt);
   initial dint= 4'b1101;
   initial clkt= 1'b0;
   initial shift_plt= 1'b0;
  
  initial forever #5 clkt = ~clkt;
  //initial forever #3 dint = ~dint;


  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0, piso_dut);
    #6; shift_plt= 1'b1;
    #100;
    $finish(1);
  end
endmodule