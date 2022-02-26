#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "analyze.h"

#define NUM_MOVES 20
#define POSSIBLE_MOVES 50

char tmp_board[BOARD_SIZE][BOARD_SIZE + 1] = { 0 };

struct move
{
	bool rot_row;
	int idx;
	int amnt;
};

struct movetree {
	struct move this_move;
	struct movetree *next_moves[50];
	int points;
};

int current_max_score[NUM_MOVES] = { 0 };
// Tracks the current max score for all of the depths

struct movetree move_tree[BOARDS];

// TODO: make check for words function
int get_words_on_board() {
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

void rotate(struct move this_move) {
	printf("-----\n");
	// Rotates "tmp" board based on specs
	int amnt_abs = abs(this_move.amnt);
	char this_row[BOARD_SIZE + 1] = { 0 };
	char *buf = calloc(amnt_abs + 1, 1);
	if (this_move.rot_row) {
		// We are rotating a row; simple enough.
		memcpy(this_row, tmp_board[this_move.idx],
			sizeof(tmp_board[this_move.idx]));
	}
	else {
		// We are rotating a column. This will be harder, but I think
		// just turning this into a row rotater problem (by temp-storing
		// the column as a row and then rotating as a row and then
		// writing the temp row back into the column) will be sufficient.
		for (int i = 0; i < BOARD_SIZE; i++) {
			this_row[i] = tmp_board[i][this_move.idx];
		}
	}

	if (this_move.amnt < 0) {
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
		memcpy(buf, &this_row[5 - this_move.amnt], this_move.amnt);
		printf("%s\n", buf);
		for (int i = BOARD_SIZE - 1; i >= this_move.amnt; i--) {
			// printf("%s\n", this_row);
			this_row[i] = this_row[i - this_move.amnt];

		}
		memcpy(&this_row[0], buf, this_move.amnt);
		printf("%s %s\n", buf, this_row);
	}
	
	free(buf);
	printf("-----\n");

	if (this_move.rot_row)
		memcpy(tmp_board[this_move.idx], this_row, BOARD_SIZE + 1);
	else
		for (int i = 0; i < BOARD_SIZE; i++)
			tmp_board[i][this_move.idx] = this_row[i];
}

void unrotate(struct move this_move) {
	this_move.amnt = -this_move.amnt;
	rotate(this_move);
}

void analyze_board(int id, int movenum, int pathtotal, int penaltyleft) {
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
	if (movenum >= NUM_MOVES) {
		return;
	}
	// find move with most words after
	for (int i = 0; i < BOARD_SIZE; i++) {
		// brute-forcing index
		for (int j = 1; j < BOARD_SIZE + 1; j++)
		{
			// brute-forcing amount
			struct move this_move;
			this_move.rot_row = true;
			this_move.idx = i;
			this_move.amnt = j;
			rotate(this_move);
			int num_words = get_words_on_board();
			// check if this move is worth pursuing,
			// i.e. if doing this move will result
			// in a total that's more than
			// the current depth's total
			if ((pathtotal + num_words) > current_max_score[movenum]) {
				current_max_score[movenum] = pathtotal + num_words;
				analyze_board(id, movenum + 1, pathtotal + num_words, penaltyleft);
			}
			else {
				if (penaltyleft == 1) {
					return;
				}
				analyze_board(id, movenum + 1, pathtotal + num_words, penaltyleft - 1);
			}
#ifdef DEBUG
			printf("testing move %c %i %i\n", 'r', i, j);
			printf("there are %i words after this move\n", num_words);
			if (num_words) {
				for (int k = 0; k < BOARD_SIZE; k++)
				{
					printf("%s\n", tmp_board[k]);
				}
			}
#endif
			unrotate(this_move);

			this_move.rot_row = false;
			rotate(this_move);
			num_words = get_words_on_board();
#ifdef DEBUG
			printf("testing move %c %i %i\n", 'c', i, j);
			printf("there are %i words after this move\n", num_words);
			if (num_words) {
				for (int k = 0; k < BOARD_SIZE; k++)
				{
					printf("%s\n", tmp_board[k]);
				}
			}
#endif
			unrotate(this_move);
		}
	}
}

void analyze(char *file) {
	// Analyze all boards and output to file with name 'file'
	printf("%s\n", file);
	for (int i = 0; i < BOARDS; i++) {
		printf("analyzing board #%i\n", i);
		analyze_board(i, 0, 0, 5);
	}
}
