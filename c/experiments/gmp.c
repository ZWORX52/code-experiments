#include <stdbool.h>
#include <stdio.h>
#include <gmp.h>

// mpz_t tmp;

bool check_if_even(mpz_t i) {
	// mpz_mod_ui(tmp, i, 2);
	// return !mpz_cmp_ui(tmp, 0);
	return mpz_divisible_ui_p(i, 2);
}

void double_mpz(mpz_t i) {
	mpz_mul_ui(i, i, 2);
}

int main() {
	// mpz_init(tmp);
	mpz_t i;
	mpz_init(i);
	mpz_add_ui(i, i, 10000);
	mpz_out_str(stdout, 10, i);
	printf("\nPlease enter a number to double: ");
	mpz_inp_str(i, stdin, 10);
	mpz_out_str(stdout, 10, i);
	printf("\nPlease enter a number to check if it's boolean: ");
	mpz_inp_str(i, stdin, 10);
	printf("Is your number even? %i\n", check_if_even(i));
}
