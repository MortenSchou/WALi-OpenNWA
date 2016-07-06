// C4B output: 3+2|[0,x]|+|[0,y]|

#include "tick.h"

void count_down(int x) {
	tick(1);
	if (x > 0) {
		x--;
		count_down(x);
	}
}

int copy(int x, int y) {
	tick(1);
	if (x > 0) {
		y++;
		x--;
		y = copy(x, y);
	}
	return y;
}

void start(int x, int y) {
	tick(1);
	y = copy(x, y);
	count_down(y);
}

void run(int x, int y)
{
    start(x,y);
    __VERIFIER_print_hull(__cost);
}

int main() 
{
	init_tick(0);

	int x = __VERIFIER_nondet_int();
	int y = __VERIFIER_nondet_int();

	run(x, y);
	
	int bnd = 3 + 2 * ((x > 0) ? x : 0) + ((y > 0) ? y : 0);
	assert(__cost <= bnd);
	
	return 0;
}
