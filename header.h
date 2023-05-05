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

typedef struct Player{
	char put;
	bool turn;
}Player;

typedef struct Map{
	char** map;
}Map;

typedef struct{
	string nama;
	int umur;
	float uang;
	string gender;
}Manusia;

void init(Player P[], Map *M, int width, int wide);
void setMapSize(Map *M, int width, int wide);
void showMenu();
void showHowTo();
void showWin(Player P[], Map M, int width, int wide);
void showBoard(Map map, int width, int wide);
void move(Player P[], Map *M, int width, int wide);
void changeTurn(Player P[]);
int getTurn(Player P[]);

int checkFill(Map M, int pick, int width, int wide);
int checkWin(Map M, int width, int wide);

int* getLocation(Map M, int width, int wide, int pick);

void freePointer(Map *M, int width, int wide);

#endif
