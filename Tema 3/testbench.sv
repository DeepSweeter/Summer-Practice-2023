module FileDataReader;

  reg signed [15:0] data[0:7];
//   reg file_open;
  integer file;
   integer i;
//   integer scanRet;

//WRITE

// initial begin
//     for (i=0; i<8; i++) begin
//         data[i] = i;
//     end
//     $writememb("memory_binary.txt", data);
//     $writememh("memory_hex.txt", data);
// end


//READ

initial $readmemh("memory_hex.txt", data);


initial begin

     $display("rdata:");

     for (i=0; i < 8; i=i+1)

     $display("%d:%h",i,data[i]);

end




// Nu functioneaza deoarece icarus nu suporta $fscanf  :/
  // File operations
//   initial begin
//     // Open file
//     file = $fopen("file_toRead.txt", "r");
//     if (file == 0) begin
//       $display("Error opening the file");
//       $finish;
//     end
    
//     i = 0;
//     do begin
//     scanRet = $fscanf(file, "%d\n", data[i]);
//       i = i + 1;
//     end while(i < $size(data) && scanRet > 0);
    


 

  // Close file and finish simulation
  initial begin
    $dumpfile("waveform.vcd"); // Save simulation data in VCD file
     
    for (i = 0; i < 8; i = i + 1) $dumpvars(0, data[i]);
     
    // Save all variables in the module
    $finish; // Terminate the simulation
    $fclose(file); // Close the file
  end

endmodule
