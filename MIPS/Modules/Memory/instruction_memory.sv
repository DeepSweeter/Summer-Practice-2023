module INSTRUCTION_MEMORY(
    input [31:0] addr,
    output [31:0] instr
);

    reg [31:0] mem [0:31];
    initial $readmemb("D:\\Facultate\\AMD\\Summer Practice 2023\\MIPS\\Modules\\Memory\\instr.txt", mem);
    assign instr = mem[addr>>2];
    //$display("%h", mem[addr>>2]);
    


endmodule