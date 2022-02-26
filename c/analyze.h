#include <stdbool.h>

#ifndef ANALYZE_H_INCLUDED
#define ANALYZE_H_INCLUDED

// #define DEBUG

#define BOARDS 730
#define BOARD_SIZE 5
#define NUM_BUCKETS 3001

void analyze_board(int id, int movenum, int pathtotal, int penaltyleft);
void analyze(char *file);

bool isword(char *str);

typedef struct node node;
struct node {
	struct node *next;
	char word[BOARD_SIZE + 1];
};

extern node *words[NUM_BUCKETS];
extern char boards[BOARDS][BOARD_SIZE][BOARD_SIZE + 1];

#endif
