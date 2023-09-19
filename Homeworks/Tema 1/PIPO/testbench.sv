module PIPO_DUT;
  reg[3:0] dint;
  reg clkt;
  wire[3:0] doutt;
  
  PIPO pipo_dut(dint, clkt, doutt);
   initial dint= 4'b1101;
   initial clkt= 1'b0;
//    initial shift_plt= 1'b0;
  
  initial forever #5 clkt = ~clkt;
  initial forever #3 dint = ~dint;


  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0, pipo_dut);
    #100;
    $finish(1);
  end
endmodule