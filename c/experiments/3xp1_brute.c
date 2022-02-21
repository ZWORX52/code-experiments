#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

void _3xp1(mpz_t x) {
	// Gotta check for overflows etc...
	int sign = mpz_sgn(x);
	if (sign == -1) {
		printf("Oh no! Either an overflow happened or you tried to trick me! :(\n");
		return;
	}
	if (!mpz_cmp_ui(x, 1)) {  // mpz_cmp_ui compares arg1 to arg2 and returns 0 if equal
		printf("Done!\n");
		return;
	}
	else if (mpz_divisible_ui_p(x, 2)) {
		printf("Currently at even#: ");
		mpz_out_str(stdout, 10, x);
		printf("\n");
		mpz_divexact_ui(x, x, 2);
		return _3xp1(x);
	}
	else {
		printf("Currently at odd#: ");
		mpz_out_str(stdout, 10, x);
		printf("\n");
		mpz_mul_ui(x, x, 3);
		mpz_add_ui(x, x, 1);
		return _3xp1(x);
	}
}

int main(int argc, char *argv[]) {
	mpz_t x;
	mpz_t x2;
	mpz_t lowlim;
	mpz_t upplim;
	mpz_init(x);
	mpz_init(x2);
	mpz_init(lowlim);
	mpz_init(upplim);
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
	// printf("%i\n", mpz_cmp(x, upplim));
	for (mpz_set(x, lowlim); mpz_cmp(x, upplim); mpz_add_ui(x, x, 1)) {
		// the cmp returns 0 if they are equal
		mpz_set(x2, x);
		_3xp1(x2);
		// mpz_out_str(stdout, 10, x2);
		// printf("\n");
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
}
