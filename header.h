#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

#define DEFAULT_WIDTH 3
#define DEFAULT_WIDE 3
#define MAX_STRING 50

typedef char string[MAX_STRING];

typedef struct Player {
	char put;
	bool turn;
} Player;

typedef struct Map {
	char** map;
} Map;

void init(Player P[], Map *M, int width, int wide);
void showMenu();
void showHowTo();
void showWinOrDraw(Player P[], Map M, int width, int wide);
void showBoard(Map map, int width, int wide);
void move(Player P[], Map *M, int width, int wide);
void changeTurn(Player P[]);
int getTurn(Player P[]);

int checkFill(Map M, int i, int j);
int checkWin(Map M, int width, int wide);

int* getLocation(Map M, int width, int wide, int pick);
void freeMap(Map *M, int width, int wide);

#endif
