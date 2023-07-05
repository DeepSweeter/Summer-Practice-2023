`include "ALU.sv"
`include "ALUDec.sv"
`include "bit_operations.sv"
`include "control_unit.sv"
`include "memory.sv"
`include "mux.sv"
`include "pc.sv"
`include "register_file.sv"

module MIPS(input clk);

    //Data path
    //PC
    wire [31:0] pcout; 

    //Instruction memory
    wire [31:0] instruction
    wire [5:0] opcode;
    wire [4:0] rs, rt, rd;
    wire [15:0] immediate;
    wire [15:0] funct;
    
    //Register bank
    wire [31:0] rd1, rd2;
    
    //ALU
    wire [31:0] ALU_out;
    wire zeroflag;
    
    //ALUControl
    wire [2:0] ALUConOut;

    //Data memory
    wire[31:0] data_mem_out;

    //Shift regs, sign extend, muxes, adders
    //...
    wire [4:0] mux_regbank_out;
    wire [31:0] mux_mainalu_out;
    wire [31:0] mux_datamem_out;
    wire [31:0] sign_ex_out;
    wire [31:0] add_pc4_out;
    wire [31:0] shift_adder_out;

    //Control
    wire RegDst, Jump, Branch, MemToReg, ALUSrc, MemWrite, RegWrite; //MemRead??
    wire [1:0] ALUOp;


    //Instances

    PC prog_counter(.in(muxout), .clk(clk), .dout(pcout));
    INSTRUCTION_MEMORY instr_mem(.addr(pcout), .instr(instruction));
    assign opcode = instruction[31:26];
    assign rs = instruction[25:21];
    assign rt = instruction[20:16];
    assign rd = instruction[15:11];
    assign immediate = instruction[15:0];
    assign funct = instr[5:0];

    CONTROL_UNIT(.opcode(opcode), .Jump(Jump), .ALUOp(ALUOp), .MemtoReg(MemToReg), .MemWrite(MemWrite), .Branch(Branch), .ALUSrc(ALUSrc), .RegDst(RegDst), .RegWrite(RegWrite));

    MUX_5BIT mux_reg_bank(.in1(rt), .in2(rd), .sel(RegDst), .dout(mux_regbank_out));
    REGISTER_BANK reg_bank(.a1(rs), .a2(rt), .a3(mux_regbank_out), .wd3(mux_datamem_out), .we3(RegWrite), .clk(clk), .rd1(rd1), .rd2(rd2));

    MUX_32BIT mux_main_alu(.in1(rd2), .in2(sign_ex_out), .sel(ALUSrc), .dout(mux_mainalu_out));
    ALU mainalu(.ALUControl(ALUConOut), .SrcA(rd1), .SrcB(mux_mainalu_out), .ALUResult(ALU_out), .Zero(zeroflag));

    DATA_MEMORY dat_mem(.din(ALU_out), .wd(rd2), .we(MemWrite), .clk(clk), .dout(data_mem_out)); //memread?
    MUX_32BIT mux_data_mem(.in1(ALU_out),.in2(data_mem_out), .sel(MemToReg), .dout(mux_datamem_out));

    SIGN_EXTEND sign_ex(.din(immediate), .dout(sign_ex_out));
    ALUDEC alu_con(.aluop(ALUOp), .funct(funct), .alucontrol(ALUConOut));

    ADDER add_pc4(.op1(pcout), .op2(32'd4), .dout(add_pc4_out));
    //shifter parametrizat

    
    SHIFTER shift_adder(.in(sign_ex_out), .dout(shift_adder_out));


endmodule