#include <stdio.h>

void print_something_else(int i) {
	if (i == 0) {
		printf("Done!\n");
		return;
	}
	else {
		printf("Got to %i\n", i);
	}
	print_something_else(i - 1);
}

int main() {
	printf("Hello World!\n");
	printf("To prove we are in the test file ;\n");
	int variable = 0;
	print_something_else(100);
}
