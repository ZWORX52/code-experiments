#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "analyze.h"

char tmp_board[BOARD_SIZE][BOARD_SIZE + 1] = { 0 };

// TODO: make check for words function
int words_on_board() {
	// Counts the number of words on the board using
	// the isword function and the tmp_board variable
	
	int count = 0;
	// Check rows
	for (int i = 0; i < BOARD_SIZE; i++) {
		count += isword(tmp_board[i]);
	}

	char *tmpbuf = calloc(BOARD_SIZE + 1, 1);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			tmpbuf[j] = tmp_board[j][i];
		}
		bool thereisword = isword(tmpbuf);
		if (thereisword) {
			printf("found word: %s\n", tmpbuf);
		}
		count += thereisword;
	}
	return count;
}

void rotate(bool rot_row, int idx, int amnt) {
	printf("-----\n");
	// Rotates "tmp" board based on specs
	int amnt_abs = abs(amnt);
	char this_row[BOARD_SIZE + 1] = { 0 };
	char *buf = calloc(amnt_abs + 1, 1);
	if (rot_row) {
		// We are rotating a row; simple enough.
		memcpy(this_row, tmp_board[idx], sizeof(tmp_board[idx]));
	}
	else {
		// We are rotating a column. This will be harder, but I think
		// just turning this into a row rotater problem (by temp-storing
		// the column as a row and then rotating as a row and then
		// writing the temp row back into the column) will be sufficient.
		for (int i = 0; i < BOARD_SIZE; i++) {
			this_row[i] = tmp_board[i][idx];
		}
	}

	if (amnt < 0) {
		// We are rotating to the left (ABCDE rot -1 = BCDEA)
		memcpy(buf, this_row, amnt_abs);
		printf("%s\n", buf);
		int i = 0;
		for (; i < BOARD_SIZE - amnt_abs + 1; i++) {
			// copy every element amnt_abs to the left
			// printf("%s\n", this_row);
			this_row[i] = this_row[i + amnt_abs];
		}
		memcpy(&this_row[i - 1], buf, amnt_abs);
		printf("%i %s %s\n", i, buf, this_row);
	}
	else {
		// We are rotating to the right (ABCDE rot 1 = EABCD)
		// memcpy(buf, &tmp_board[5 - amnt][idx], amnt); Faulty
		// memcpy, should use this_row instead
		memcpy(buf, &this_row[5 - amnt], amnt);
		printf("%s\n", buf);
		for (int i = BOARD_SIZE - 1; i >= amnt; i--) {
			// printf("%s\n", this_row);
			this_row[i] = this_row[i - amnt];

		}
		memcpy(&this_row[0], buf, amnt);
		printf("%s %s\n", buf, this_row);
	}
	
	free(buf);
	printf("-----\n");

	if (rot_row)
		memcpy(tmp_board[idx], this_row, BOARD_SIZE + 1);
	else
		for (int i = 0; i < BOARD_SIZE; i++)
			tmp_board[i][idx] = this_row[i];
}

void unrotate(bool rot_row, int idx, int amnt) {
	rotate(rot_row, idx, -amnt);
}

void analyze_board(int id) {
	// request rotation (debugging)
	memcpy(tmp_board, boards[id], sizeof(boards[id]));

#ifdef DEBUG
	printf("before:\n");
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("%s\n", tmp_board[i]);
	}
	printf("\n");

	char rot_mode;
	int rot_idx, rot_amnt;
	printf("mode: ");
	rot_mode = getchar();
	while (rot_mode == '\n') {
		rot_mode = getchar();
	}

	printf("idx: ");
	scanf("%d", &rot_idx);
	printf("amnt: ");
	scanf("%d", &rot_amnt);
	printf("%c %d %d\n", rot_mode, rot_idx, rot_amnt);

	rotate(rot_mode == 'r', rot_idx, rot_amnt);
	printf("after:\n");
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("%s\n", tmp_board[i]);
	}
#endif
	// find move with most words after
	for (int i = 0; i < BOARD_SIZE; i++) {
		// brute-forcing index
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			// brute-forcing amount
			printf("testing move %c %i %i\n", 'r', i, j);
			rotate(true, i, j);
			int words = words_on_board();
			printf("there are %i words after this move\n", words);
			if (words) {
				for (int k = 0; k < BOARD_SIZE; k++)
				{
					printf("%s\n", tmp_board[k]);
				}
			}
			unrotate(true, i, j);

			printf("testing move %c %i %i\n", 'c', i, j);
			rotate(true, i, j);
			int words = words_on_board();
			printf("there are %i words after this move\n", words);
			if (words) {
				for (int k = 0; k < BOARD_SIZE; k++)
				{
					printf("%s\n", tmp_board[k]);
				}
			}
			unrotate(true, i, j);
		}
	}
}

void analyze(char *file) {
	// Analyze all boards and output to file with name 'file'
	printf("%s\n", file);
	for (int i = 0; i < BOARDS; i++) {
		printf("analyzing board #%i\n", i);
		analyze_board(i);
	}
}

