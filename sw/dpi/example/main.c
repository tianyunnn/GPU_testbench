#include "svdpi.h"
#include "svdpi_src.h"
#include "dpiheader.h"
#include <stdio.h>

extern int progress_clk();

int c_func(int a, int b) {
	printf("C %d %d %d\n", a, b, a + b);
	return a + b;
}

int c_progress_clk(int cycles) {
	for (int i = 0; i < cycles * 2; i++) {
		progress_clk();
	}
	return 0;
}

