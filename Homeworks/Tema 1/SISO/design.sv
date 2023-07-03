module  SISO(
    input din,
    input clk,
    output reg dout  
); 
reg[3:0] data=4'b0;
always@(posedge clk)
    begin
        dout <= data[0];
        data <= {din, data[3:1]};
        
    end
    
endmodule
