module SIPO_DUT;
  reg dint ,clkt;
  wire[3:0] doutt;
  
  SIPO sipo_dut(dint, clkt, doutt);
   initial dint= 1'b1;
   initial clkt= 1'b0;
  
  initial forever #5 clkt = ~clkt;
  initial forever #3 dint = ~dint;


  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0, sipo_dut);
    #100;
    $finish(1);
  end
endmodule