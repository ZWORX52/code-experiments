#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "analyze.h"

#define BOARDS 730
#define BOARD_SIZE 5
#define NUM_BUCKETS 3001

/*
 *typedef struct node node;
 *
 *struct node {
 *        struct node *next;
 *        char word[BOARD_SIZE + 1];
 *};
 */

char boards[BOARDS][BOARD_SIZE][BOARD_SIZE + 1];
node *words[NUM_BUCKETS] = { NULL };

// Djb2 hash function
// Code from:
// https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f
unsigned long hash(char *str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash % NUM_BUCKETS;
}

bool isword(char *str) {
#ifdef DEBUG
	printf("checking %s\n", str);
#endif
	/*
	 *unsigned long int idx = hash(str);
	 *struct node *node_ptr = words[idx];
	 *while (node_ptr != NULL) {
	 *        printf("while loop ran\n");
	 *        if (!strcmp(node_ptr->word, str)) {
	 *                printf("other str was %s\n", node_ptr->word);
	 *                return true;
	 *        }
	 *        node_ptr = node_ptr->next;
	 *}
	 *return false;
	 */
	unsigned long int idx = hash(str);
#ifdef DEBUG
	printf("hash is %lu\n", idx);
#endif
	node *begin = words[idx];
	if (begin == NULL) {
		return false; // no word at this hash
	}
	while (begin != NULL) {
		// It took me way too long to recognize that strcmp returns a 0 if equal...
#ifdef DEBUG
		printf("comparing %s and %s\n", begin->word, str);
#endif
		if (!strcmp(begin->word, str)) {
			// words match at this part of the linked list
			// at this hash so the word is in the table
			return true;
		}
		begin = begin->next;
	}
	return false;
}

void add(char *str) {
	// Add string to hash table
#ifdef DEBUG
	printf("adding %s...\n", str);
#endif
	/*
	 *unsigned long int idx = hash(str);
	 *struct node *whats_there = words[idx];
	 *struct node new_node;
	 *new_node.word = str;
	 *new_node.next = NULL;
	 *printf("%p\n", &new_node);
	 *if (whats_there == NULL) {
	 *        words[idx] = &new_node;
	 *        return;
	 *}
	 * there's already the start of a linked list there. continue it
	 *while (whats_there->next != NULL) {
	 *        whats_there = whats_there->next;
	 *}
	 *whats_there->next = &new_node;
	 */
	unsigned long int idx = hash(str);
	node *there = words[idx];
	node *new_node = malloc(sizeof(node));
	strcpy(new_node->word, str);
	new_node->next = there;
	
	if (there == NULL) {
		// empty linked list at this hash, start a new one
		new_node->next = NULL;
		words[idx] = new_node;
	}
	// we need to insert the new node into the start of the linked
	// list that we found. this can be done by moving pointers
	// back and forth.
	words[idx] = new_node;
}

int main() {
	FILE *boards_file = fopen("files/boards", "r");
	char c[BOARD_SIZE + 1] = { 0 };
	int count = 0;
	int sub_board_count = 0;
	/*
	 *boards = malloc(sizeof(char**) * BOARDS);
	 *for (int i = 0; i < BOARDS; i++) {
	 *        boards[i] = malloc(sizeof(char*) * BOARD_SIZE);
	 *        for (int j = 0; j < BOARD_SIZE; j++) {
	 *                boards[i][j] = calloc(1, BOARD_SIZE + 1);
	 *        }
	 *}
	 */

#ifdef DEBUG
	printf("loading...\n");
#endif
	while (fread(&c, 1, BOARD_SIZE, boards_file)) {
		strcat(boards[count][sub_board_count], c);
#ifdef DEBUG
		printf("%s -> %s (%i, %i)\n", c, boards[count][sub_board_count], count, sub_board_count);
#endif

		fseek(boards_file, 1, SEEK_CUR);
		sub_board_count++;
		if (sub_board_count == 5) {
			// We reached the end of the board!
			count++;
			sub_board_count = 0;
		}
	}
#ifdef DEBUG
	printf("done loading, printing...\n-----\n");
	for (int i = 0; i < BOARDS; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			printf("%s\n", boards[i][j]);
		}
		printf("-----\n");
	}
	printf("done loading boards, loading words...\n");
#endif
	fclose(boards_file);

	FILE *words_file = fopen("files/words", "r");
	char c2[BOARD_SIZE + 1] = { 0 };
	while (fread(&c2, 1, BOARD_SIZE, words_file)) {
		add(c2);
		fseek(words_file, 1, SEEK_CUR);
		// Debug
		/*
		 *for (int i = 0; i < NUM_BUCKETS; i++) {
		 *        if (words[i] != NULL) {
		 *                printf("%p\n", words[i]);
		 *        }
		 *}
		 *printf("--------------------------\n");
		 */
	}

#ifdef DEBUG
	for (int i = 0; i < NUM_BUCKETS; i++) {
		node *there = words[i];
		while (there != NULL) {
			printf("%s ", there->word);
			there = there->next;
		}
	}
	printf("\n");
#endif
	
	printf("enter a string to check: ");
	char buf[BOARD_SIZE + 1] = { 0 };
	scanf("%s", buf);
	printf("%s", buf);
	printf("%s\n", isword(buf) ? " is a word" : " is not a word");

	analyze("files/analyze_output");

#ifdef DEBUG
	printf("program done!\n");
#endif
	/*
	 *for (int i = 0; i < BOARDS; i++) {
	 *        for (int j = 0; j < BOARD_SIZE; j++) {
	 *                free(boards[i][j]);
	 *        }
	 *        free(boards[i]);
	 *}
	 *free(boards);
	 */
	for (int i = 0; i < NUM_BUCKETS; i++) {
		node *there = words[i];
		node *next_there;
		while (there != NULL) {
			next_there = there->next;
			free(there);
			there = next_there;
		}
	}
}
