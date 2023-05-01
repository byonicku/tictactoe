#include "header.h"

void init(Player P[], Map *M){
	int i, j;
	char k = '1';
	
	P[0].turn = true;
	P[0].put = 'X';
	P[1].turn = false;
	P[1].put = 'O';

	for(i=0;i<B_WIDE;i++){
		for(j=0;j<B_WIDTH;j++){
			if(i == 2 || i == 4) M->map[i][j] = '-';
			else if(j == 2 || j == 4) M->map[i][j] = '|';
			else if(i == 0 || j == 0 || j == B_WIDTH-1 || i == B_WIDE-1) M->map[i][j] = ' ';
			else M->map[i][j] = k++;
		}
	}
}

void showMenu(){
	system("cls");
	printf(" ---- Tic Tac Toe ----\n");
	printf("\n [1] Play");
	printf("\n [2] How To Play");
	printf("\n [3] Exit \n");
}

void showHowTo(){
	system("cls");
	printf("\n There will be 9 box you just need to write it in console");
	printf("\n Choose your box and line up the 'X' or 'O' symbol to win");
	printf("\n Line can be diagonal or straight.");
	printf("\n\n\t\tPress any button to back...");
}

void showBoard(Map M){
	int i, j;
	for(i=0;i<B_WIDE;i++){
		printf("\t");
		for(j=0;j<B_WIDTH;j++){
			printf("%c ", M.map[i][j]);
		}
		printf("\n");
	}
}

void move(Player P[], Map *M){
	int i, pick;
	string buffer;
	
	while(1){
		printf("\n Select your box : "); fgets(buffer, MAX_STRING, stdin);
		pick = atoi(buffer);
		
		if(pick<1 || pick>9){
			printf("\n\tInput must be in range of 1 - 9");
			getch();
			
			break;
		}

		if(checkFill(*M, pick)==1){
			printf("\n\tBox already filled");
			getch();
			
			break;
		}
		
		i = getTurn(P);
		
		if(pick==1) M->map[1][1] = P[i].put;
		else if(pick==2) M->map[1][3] = P[i].put;
		else if(pick==3) M->map[1][5] = P[i].put;
		else if(pick==4) M->map[3][1] = P[i].put;
		else if(pick==5) M->map[3][3] = P[i].put;
		else if(pick==6) M->map[3][5] = P[i].put;
		else if(pick==7) M->map[5][1] = P[i].put;
		else if(pick==8) M->map[5][3] = P[i].put;
		else if(pick==9) M->map[5][5] = P[i].put;	
		
		changeTurn(P);
		
		break;
	}
	
}

void changeTurn(Player P[]){
	P[0].turn = P[1].turn;
	P[1].turn = !P[0].turn;
}

int getTurn(Player P[]){
	return !P[0].turn; // Return current player index
}

int checkFill(Map M, int pick){
	if(pick==1){
		if(M.map[1][1] == 'X' || M.map[1][1] == 'O') return 1;
		else return -1;
	}
	else if(pick==2){
		if(M.map[1][3] == 'X' || M.map[1][3] == 'O') return 1;
		else return -1;
	}
	else if(pick==3){
		if(M.map[1][5] == 'X' || M.map[1][5] == 'O') return 1;
		else return -1;
	}
	else if(pick==4){
		if(M.map[3][1] == 'X' || M.map[3][1] == 'O') return 1;
		else return -1;
	}
	else if(pick==5){
		if(M.map[3][3] == 'X' || M.map[3][3] == 'O') return 1;
		else return -1;
	}
	else if(pick==6){
		if(M.map[3][5] == 'X' || M.map[3][5] == 'O') return 1;
		else return -1;
	}
	else if(pick==7){
		if(M.map[5][1] == 'X' || M.map[5][1] == 'O') return 1;
		else return -1;
	}
	else if(pick==8){
		if(M.map[5][3] == 'X' || M.map[5][3] == 'O') return 1;
		else return -1;
	}
	else if(pick==9){
		if(M.map[5][5] == 'X' || M.map[5][5] == 'O') return 1;
		else return -1;
	}
	else {
		return -1;
	}
}

int checkWin(Map M){
	if((M.map[1][1] == 'X' && M.map[1][3] == 'X' && M.map[1][5] == 'X') || (M.map[1][1] == 'O' && M.map[1][3] == 'O' && M.map[1][5] == 'O')){
		return 1;
	}
	else if((M.map[3][1] == 'X' && M.map[3][3] == 'X' && M.map[3][5] == 'X') || (M.map[3][1] == 'O' && M.map[3][3] == 'O' && M.map[3][5] == 'O')){
		return 1;
	}
	else if((M.map[5][1] == 'X' && M.map[5][3] == 'X' && M.map[5][5] == 'X') || (M.map[5][1] == 'O' && M.map[5][3] == 'O' && M.map[5][5] == 'O')){
		return 1;
	}
	else if((M.map[1][1] == 'X' && M.map[3][1] == 'X' && M.map[5][1] == 'X') || (M.map[1][1] == 'O' && M.map[3][1] == 'O' && M.map[5][1] == 'O')){
		return 1;
	}
	else if((M.map[1][3] == 'X' && M.map[3][3] == 'X' && M.map[5][3] == 'X') || (M.map[1][3] == 'O' && M.map[3][3] == 'O' && M.map[5][3] == 'O')){
		return 1;
	}
	else if((M.map[1][5] == 'X' && M.map[3][5] == 'X' && M.map[5][5] == 'X') || (M.map[1][5] == 'O' && M.map[3][5] == 'O' && M.map[5][5] == 'O')){
		return 1;
	}
	else if((M.map[1][1] == 'X' && M.map[3][3] == 'X' && M.map[5][5] == 'X') || (M.map[1][1] == 'O' && M.map[3][3] == 'O' && M.map[5][5] == 'O')){
		return 1;
	}
	else if((M.map[1][5] == 'X' && M.map[3][3] == 'X' && M.map[5][1] == 'X') || (M.map[1][5] == 'O' && M.map[3][3] == 'O' && M.map[5][1] == 'O')){
		return 1;
	}
	else if(M.map[1][1] != '1' && M.map[1][3] != '2' && M.map[1][5] != '3' && M.map[3][1] != '4' && M.map[3][3] != '5' && M.map[3][5] != '6' && M.map[5][1] != '7' && M.map[5][3] != '8' && M.map[5][5] != '9'){
		return 2;
	}
	else return -1;
}

void showWin(Player P[], Map M){
	if(checkWin(M) == 1){
		printf("\n\t %s\n\n", !P[0].turn ? "Player 1 Win" : "Player 2 Win");
	}
	else if(checkWin(M) == 2){
		printf("\nDraw!");
	}
	
	showBoard(M);
	printf("\n\n\tPress any button to back...");
}
