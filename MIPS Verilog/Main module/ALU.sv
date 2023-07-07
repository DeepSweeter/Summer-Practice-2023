module ALU(input [2:0] ALUControl,
         input[31:0] SrcA,
         input[31:0] SrcB,
         output reg[31:0] ALUResult,
         output reg Zero);
         
    always@(*) begin
        case(ALUControl)
             3'b010: ALUResult = SrcA + SrcB;
             3'b110:begin
                 ALUResult = SrcA - SrcB;
                 Zero = SrcA - SrcB == 0? 1: 0;
             end
             3'b000: ALUResult = SrcA & SrcB;
             3'b001: ALUResult = SrcA | SrcB;
             3'b111: ALUResult = SrcA < SrcB? 1: 0;
             default: begin
                Zero = 1'bx;
                ALUResult = 32'bx;
             end
        endcase
    end

    

endmodule