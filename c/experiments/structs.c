#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

struct test {
	mpz_t num;
	mpz_t high;
};

struct test* begin(int count) {
	return malloc(sizeof(struct test) * count);
}

int main() {
	/*
	 *struct test test1;
	 *mpz_init(test1.num);
	 *mpz_init(test1.high);
	 *printf("num for test1:  ");
	 *mpz_inp_str(test1.num, stdin, 10);
	 *printf("high for test1: ");
	 *mpz_inp_str(test1.high, stdin, 10);
	 *printf("\noutputting...\n");
	 *mpz_out_str(stdout, 10, test1.num);
	 *printf("\n");
	 *mpz_out_str(stdout, 10, test1.high);
	 *printf("\n");
	 */

	struct test* arr = begin(3);
	for (int i = 0; i < 3; i++) {
		printf("num for idx %i:  ", i);
		mpz_inp_str(arr[i].num, stdin, 10);
		printf("high for idx %i: ", i);
		mpz_inp_str(arr[i].high, stdin, 10);
	}
	printf("READ IN TO ARRAY COMPLETE, PRINTING...\n");
	for (int i = 0; i < 3; i++) {
		mpz_out_str(stdout, 10, arr[i].num);
		printf("\n");
		mpz_out_str(stdout, 10, arr[i].high);
		printf("\n");
	}
	printf("DONE WOOOOOOO\n");
}
