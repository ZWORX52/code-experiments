#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
	char **test = malloc(sizeof(char *) * 10);
	for (int i = 0; i < 10; i++) {
		test[i] = malloc(10);
	}
	strcat(test[0], "hello");
	printf("%s, %s\n", test[0], test[1]);
}
