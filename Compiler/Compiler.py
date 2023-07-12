#This script transforms the mips assembly code in machine code.
import sys
from bitstring import Bits
#Variables
registers = {
    "$zero": "00000",
    "$at" : "00001",
    "$v0" : "00010",
    "$v1" : "00011",
    "$a0" : "00100",
    "$a1" : "00101",
    "$a2" : "00110",
    "$a3" : "00111",
    "$t0" : "01000",
    "$t1" : "01001",
    "$t2" : "01010",
    "$t3" : "01011",
    "$t4" : "01100",
    "$t5" : "01101",
    "$t6" : "01110",
    "$t7" : "01111",
    "$s0" : "10000",
    "$s1" : "10001",
    "$s2" : "10010",
    "$s3" : "10011",
    "$s4" : "10100",
    "$s5" : "10101",
    "$s6" : "10110",
    "$s7" : "10111",
    "$t8" : "11000",
    "$t9" : "11001",
    "$k0" : "11010",
    "$k1" : "11011",
    "$gp" : "11100",
    "$sp" : "11101",
    "$fp" : "11110",
    "$ra" : "11111",
}

R_TYPES = ["add", "sub", "and", "or", "slt"]
R_TYPES_CODES={
    "add" : "100000",
    "sub" : "100010",
    "and" : "100100",
    "or"  : "100101",
    "slt" : "101010"
}

instruction_lines = []

machine_file_name = "instr.txt"


#Code
def compile(codes):
    machine_file = open(machine_file_name, "a")
    machine_file.write("// 0x00000000\n")
    labels = {}
    for code in codes:
        if ":" in code[1]:
            labels[code[1].lower().replace(":", "")] = code[0]
    for code in codes:
        #initialize fields
        opcode = ""
        rs = ""
        rt = ""
        rd = ""
        shamt = "00000"
        funct = ""
        immediate = ""
        immediateJ = ""
        binary_code = ""
        addr = code[0]
        instr_split = code[1].lower().split(" ")
        
        #Check the instruction
        if instr_split[0] in R_TYPES:
            opcode = "000000"
            rs = registers[instr_split[2]]
            rt = registers[instr_split[3]]
            rd = registers[instr_split[1]]
            funct = R_TYPES_CODES[instr_split[0]]
            binary_code = opcode + "_" + rs + "_" + rt + "_" + rd + "_" + shamt + "_" + funct +"\n"

        elif instr_split[0] == "addi":
            opcode= "001000"
            rs = registers[instr_split[2]]
            rt = registers[instr_split[1]]
            immediate= Bits(int=int(instr_split[3]), length=16).bin
            binary_code = opcode + "_"+ rs + "_" + rt + "_" + immediate + "\n"

        elif instr_split[0] == "sw":
            opcode = "101011"
            rs = registers[instr_split[3]]
            rt = registers[instr_split[1]]
            immediate = Bits(int=int(instr_split[2]), length=16).bin
            binary_code = opcode + "_"+ rs + "_" + rt + "_" + immediate + "\n"

        elif instr_split[0] == "lw":
            opcode = "100011"
            rs = registers[instr_split[3]]
            rt = registers[instr_split[1]]
            immediate = Bits(int=int(instr_split[2]), length=16).bin
            binary_code = opcode + "_"+ rs + "_" + rt + "_" + immediate + "\n"

        elif instr_split[0] == "beq":
            opcode = "000100"
            rs = registers[instr_split[1]]
            rt = registers[instr_split[2]]
            immediate = Bits(int=(labels[instr_split[3]] - addr-1), length=16).bin
            binary_code = opcode + "_"+ rs + "_" + rt + "_" + immediate + "\n"

        elif instr_split[0] == "j":
            opcode="000010"
            immediateJ = Bits(int=labels[instr_split[1]], length=26).bin
            binary_code = opcode + "_" + immediateJ + "\n"
        machine_file.write(binary_code)


if __name__ == '__main__':
    #Process the file before calling the compiler function
    assembly_file_name = "code.s" #sys.argv[1]
    try:
        assembly_file = open(assembly_file_name, 'r')
        code = list(map(lambda x: x.strip("\n"), assembly_file.readlines()))
        i = 0
        for line in code:
            instruction_lines.append([i, line.replace(",", "").replace("("," ").replace(")", "")])
            if ":" not in line:
                i+=1
        #print(instruction_lines)
        compile(instruction_lines)
    except FileNotFoundError:
        print("Error: File not found")