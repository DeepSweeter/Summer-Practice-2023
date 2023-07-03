module CONTROL_UNIT (
    input[5:0] opcode,
    output reg MemtoReg,
    output reg MemWrite,
    output reg Branch,
    output reg ALUSrc,
    output reg RegDst,
    output reg RegWrite);

    always@(*)begin
    case(opcode)
        6'b0: begin //R-type
            MemtoReg = 1'b0;
            MemWrite = 1'b0;
            Branch = 1'b0;
            ALUSrc = 1'b0;
            RegDst = 1'b1;
            RegWrite = 1'b1;
        end
        6'b100_011: begin //lw
            MemtoReg = 1'b1;
            MemWrite = 1'b0;
            Branch = 1'b0;
            ALUSrc = 1'b1;
            RegDst = 1'b0;
            RegWrite = 1'b1;
        end
        6'b101_011: begin //sw
            MemtoReg = 1'bx;
            MemWrite = 1'b1;
            Branch = 1'b0;
            ALUSrc = 1'b1;
            RegDst = 1'bx;
            RegWrite = 1'b0;
        end
        6'b000_100: begin //beq
            MemtoReg = 1'bx;
            MemWrite = 1'b0;
            Branch = 1'b1;
            ALUSrc = 1'b0;
            RegDst = 1'bx;
            RegWrite = 1'b0;
        end
        6'b001_000: begin //addi
            MemtoReg = 1'b0;
            MemWrite = 1'b0;
            Branch = 1'b0;
            ALUSrc = 1'b1;
            RegDst = 1'b0;
            RegWrite = 1'b1;
        end

        //Format for the rest of instructions
        // 6'b0: begin
        //     MemtoReg = ;
        //     MemWrite = ;
        //     Branch = ;
        //     ALUSrc = ;
        //     RegDst = ;
        //     RegWrite = ;
        // end
    endcase

    end
    
endmodule