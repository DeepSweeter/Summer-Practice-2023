module  PISO(
    input[3:0] din,
    input clk,
    input shift_pl,
    output reg dout  
); 
reg[3:0] data=4'b0;
always@(posedge clk)
    begin
        if(~shift_pl)
            data <= din;
        else
            begin
                data <= {1'b0, data[3:1]};
                dout <= data[0];
            end
    end
    
endmodule