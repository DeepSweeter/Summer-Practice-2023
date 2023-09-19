module CONTROL_UNIT (
    input[5:0] opcode,
    output reg Jump,
    output reg [1:0] ALUOp,
    output reg MemtoReg,
    output reg MemWrite,
    output reg Branch,
    output reg ALUSrc,
    output reg RegDst,
    output reg RegWrite);

    always@(*)begin
    case(opcode)
        6'b0: begin //R-type
            Jump = 1'b0;
            ALUOp = 2'b10;
            MemtoReg = 1'b0;
            MemWrite = 1'b0;
            Branch = 1'b0;
            ALUSrc = 1'b0;
            RegDst = 1'b1;
            RegWrite = 1'b1;
        end
        6'b100_011: begin //lw
            Jump = 1'b0;
            ALUOp = 2'b00;
            MemtoReg = 1'b1;
            MemWrite = 1'b0;
            Branch = 1'b0;
            ALUSrc = 1'b1;
            RegDst = 1'b0;
            RegWrite = 1'b1;
        end
        6'b101_011: begin //sw
            Jump = 1'b0;
            ALUOp = 2'b00;
            MemtoReg = 1'b0;
            MemWrite = 1'b1;
            Branch = 1'b0;
            ALUSrc = 1'b1;
            RegDst = 1'b0;
            RegWrite = 1'b0;
        end
        6'b000_100: begin //beq
            Jump = 1'b0;
            ALUOp = 2'b01;
            MemtoReg = 1'b0;
            MemWrite = 1'b0;
            Branch = 1'b1;
            ALUSrc = 1'b0;
            RegDst = 1'b0;
            RegWrite = 1'b0;
        end
        6'b001_000: begin //addi
            Jump = 1'b0;
            ALUOp = 2'b00;
            MemtoReg = 1'b0;
            MemWrite = 1'b0;
            Branch = 1'b0;
            ALUSrc = 1'b1;
            RegDst = 1'b0;
            RegWrite = 1'b1;
        end
        6'b000_010: begin //jump
            Jump = 1'b1;
            ALUOp = 2'b00;
            MemtoReg = 1'b0;
            MemWrite = 1'b0;
            Branch = 1'b0;
            ALUSrc = 1'b0;
            RegDst = 1'b0;
            RegWrite = 1'b0;
        end


        //Format for the rest of instructions
        // 6'b0: begin
        //     Jump = 1'b0;
        //     ALUOp = 2'b10;
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