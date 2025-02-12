module tb();

import "DPI-C" function int c_func(int a, int b);
import "DPI-C" context task c_progress_clk(int cycles);

export "DPI" task progress_clk;

function integer sv_func(integer a, integer b);
	return c_func(a, b);
endfunction
//
reg[3:0] a;

reg clk;

task progress_clk();
	#10; clk = ~clk;
endtask

initial begin
	clk = 0;
	a = sv_func(4, 5);

	c_progress_clk(20);

	//a = c_func(4, 5);
	$display ("SV %d", a);
end

endmodule
