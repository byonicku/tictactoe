#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#define B_WIDTH 7
#define B_WIDE 7
#define MAX_STRING 50

typedef char string[MAX_STRING];

typedef struct Player{
	char put;
	bool turn;
}Player;

typedef struct Map{
	char map[B_WIDTH][B_WIDE];
}Map;

void init(Player P[], Map *M);
void showMenu();
void showHowTo();
void showWin(Player P[], Map M);
void showBoard(Map map);
void move(Player P[], Map *M);
void changeTurn(Player P[]);
int getTurn(Player P[]);

int checkFill(Map M, int pick);
int checkWin(Map M);

#endif
