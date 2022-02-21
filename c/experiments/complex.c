#include <stdlib.h>
#include <stdio.h>

void _3xp1(int x) {
	// Gotta check for overflows etc...
	if (x < 1) {
		printf("Oh no! Either an overflow happened or you tried to trick me! :(\n");
		return;
	}
	if (x == 1) {
		printf("Finally done!\n");
		return;
	}
	else if (x % 2) {
		printf("Currently at odd#: %i\n", x);
		return _3xp1(x * 3 + 1);
	}
	else {
		printf("Currently at even#: %i\n", x);
		return _3xp1(x / 2);
	}
}

int main(int argc, char *argv[]) {
	int x = 0;
	if (argc == 2) {
		x = atoi(argv[1]);
		printf("Using argument as starting number (%i)\n", x);
		_3xp1(x);
	}
	else if (argc > 2) {
		printf("Improper usage! ./complex [number]\n");
		return 1;
	}
	else {
		printf("Enter a number for 3x+1: ");
		scanf("%i", &x);
		printf("You entered: %i\n", x);
		_3xp1(x);
	}
}
