module SISO_DUT;
  reg dint ,clkt;
  wire doutt;
  
  SISO siso_dut(dint, clkt, doutt);
   initial dint= 1'b1;
   initial clkt= 1'b0;
  
  initial forever #5 clkt = ~clkt;
  initial forever #3 dint = ~dint;


  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0, siso_dut);
    #100;
    $finish(1);
  end
endmodule