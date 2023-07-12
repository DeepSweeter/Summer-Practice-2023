module INSTRUCTION_MEMORY(
    input [31:0] addr,
    output [31:0] instr
);
    // 256 blocks of 32 bits each
    reg [31:0] mem [0:255];
    initial $readmemb("instr.txt", mem);
    //The address is multiple of 4, but because of the addresing mode I've used the address must be shifted to the right with 2
    assign instr = mem[addr>>2];
    
endmodule

module DATA_MEMORY(
    input [31:0] din,
    input [31:0] wd,
    input we,
    input clk,
    output [31:0] dout
);
    // 256 blocks of 32 bits each
    reg [31:0] mem [0:255];
    //Same logic as Instruction Memory
    assign dout = mem[din>>2];

    always@(posedge clk)
        if(we)
            mem[din>>2] = wd;



endmodule