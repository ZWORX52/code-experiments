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
		printf("Finally done!\n");
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
	mpz_init(x);
	if (argc == 2) {
		mpz_set_str(x, argv[1], 10);
		printf("Using argument as starting number (");
		mpz_out_str(stdout, 10, x);
		printf(")\n");
		_3xp1(x);
	}
	else if (argc > 2) {
		printf("Improper usage! ./complex [number]\n");
		return 1;
	}
	else {
		printf("Enter a number for 3x+1: ");
		mpz_inp_str(x, stdin, 10);
		_3xp1(x);
	}
}
