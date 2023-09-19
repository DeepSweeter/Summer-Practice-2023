module  SIPO(
    input din,
    input clk,
    output reg [3:0] dout  
); 
reg[3:0] data=4'b0;
always@(posedge clk)
    begin
        dout <= data;
        data <= {din, data[3:1]};
        
    end
    
endmodule