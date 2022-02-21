#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

struct high {
	mpz_t num;
	mpz_t high;
};

void _3xp1(mpz_t x, mpz_t max) {
	// Gotta check for overflows etc...
	if (mpz_sgn(x) == -1) {
		printf("Oh no! Either an overflow happened or you tried to trick me! :(\n");
		return;
	}
	if (mpz_cmp(x, max) == 1) {
		// x > max
		mpz_set(max, x);
	}
	if (!mpz_cmp_ui(x, 1)) {
		// mpz_cmp_ui compares arg1 to arg2 and returns 0 if equal
		printf("Done!\n");
		return;
	}
	else if (mpz_divisible_ui_p(x, 2)) {
		printf("Currently at even#: ");
		mpz_out_str(stdout, 10, x);
		printf("\n");
		mpz_divexact_ui(x, x, 2);
		return _3xp1(x, max);
	}
	else {
		printf("Currently at odd#: ");
		mpz_out_str(stdout, 10, x);
		printf("\n");
		mpz_mul_ui(x, x, 3);
		mpz_add_ui(x, x, 1);
		return _3xp1(x, max);
	}
}

int main(int argc, char *argv[]) {
	mpz_t x;
	mpz_t x2;
	mpz_t max;
	mpz_t lowlim;
	mpz_t upplim;
	mpz_inits(x, x2, max, lowlim, upplim, NULL);
	// I need NULL because otherwise mpz_inits will just
	// keep on initializing memory that isn't an mpz_t
	// AKA undefined behavior!

	if (argc > 3) {
		// Error out, too many args
		printf("Too many arguments! Usage: %s [lower limit] [upper limit]\n", argv[0]);
		return 1;
	}
	if (argc > 1) {
		// They gave at least 1 argument
		mpz_set_str(lowlim, argv[1], 10);
	}
	else {
		// And this else runs if there was no lower limit supplied as well.
		printf("Please enter a lower limit: ");
		mpz_inp_str(lowlim, stdin, 10);
	}
	if (argc > 2) {
		// They gave both
		mpz_set_str(upplim, argv[2], 10);
	}
	else {
		// Sorry this is confusing
		// This runs if there was no upper limit supplied
		printf("Please enter an upper limit: ");
		mpz_inp_str(upplim, stdin, 10);
	}

	unsigned long int upplim_ui = mpz_get_ui(upplim);
	unsigned long int lowlim_ui = mpz_get_ui(lowlim);
	unsigned long int count = 0;
	unsigned long int amount = upplim_ui - lowlim_ui;
	struct high* arr = malloc(sizeof(struct high) * (upplim_ui - lowlim_ui));
	// printf("%i\n", mpz_cmp(x, upplim));
	for (mpz_set(x, lowlim); mpz_cmp(x, upplim); mpz_add_ui(x, x, 1)) {
		// the cmp returns 0 if they are equal
		struct high this_high;
		mpz_inits(this_high.num, this_high.high, NULL);

		mpz_set(x2, x);
		mpz_set(this_high.num, x);
		_3xp1(x2, max);
		mpz_set(this_high.high, max);
		arr[count] = this_high;
		count++;
		mpz_out_str(stdout, 10, arr[count].num);
		printf("\n");
		/*
		 *mpz_out_str(stdout, 10, x);
		 *printf("\n");
		 *printf("%i\n", mpz_cmp(x, upplim));
		 */
	}
	 /*
	  * Debug
	  * mpz_out_str(stdout, 10, x);
	  * printf("\n");
	  * mpz_out_str(stdout, 10, lowlim);
	  * printf("\n");
	  * mpz_out_str(stdout, 10, upplim);
	  * printf("\n");
	  */
	for (int i = 0; i < amount; i++) {
		mpz_out_str(stdout, 10, arr[count].num);
		printf("; ");
		mpz_out_str(stdout, 10, arr[count].high);
		printf("\n");
	}
	// Let go of all malloc'd memory
	free(arr);
}
