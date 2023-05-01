#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>

#define B_WIDTH 7
#define B_WIDE 7

typedef char string[50];

typedef struct Player{
	char put;
	bool turn;
}Player;

typedef struct Map{
	char map[B_WIDTH][B_WIDE];
}Map;

void init(Player P[], Map *M);
void menu(int *menuSelect);
void howTo();
void board(Map map);
void move(Player P[], Map *M, int *pick, int *check);
void changeTurn(Player P[], int *check);

int checkFill(Map M, int pick);
int checkWin(Map M);

#endif
