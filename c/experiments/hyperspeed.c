#include <stdio.h>


int main() {
	for (unsigned long long int i = 0; i < 10000000; i++) {
		printf("%lli ", i);
	}
	printf("\n");
}

