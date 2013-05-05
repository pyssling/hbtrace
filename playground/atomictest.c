#include <stdbool.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	long i;
	bool val = false;

	for (i = 0; i < 1000000000; i++) {
		__sync_bool_compare_and_swap(&val, false, true);
	}
}
