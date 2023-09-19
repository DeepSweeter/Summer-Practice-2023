module INSTRUCTION_MEMORY(
    input [31:0] addr,
    output [31:0] instr
);

    reg [31:0] mem [0:255];
    initial $readmemb("instr.txt", mem);
    assign instr = mem[addr>>2];
   // $display("%d", mem[addr>>2]);
    
endmodule

module DATA_MEMORY(
    input [31:0] din,
    input [31:0] wd,
    input we,
    input clk,
    output [31:0] dout
);
  reg [31:0] mem [0:255];

    assign dout = mem[din>>2];

    always@(posedge clk)
        if(we)
            mem[din>>2] = wd;



endmodule