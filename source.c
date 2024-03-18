#include "header.h"

void init(Player P[], Map *M, int width, int wide) {
	int i, j;
	srand(time(NULL));
	
	M->map = malloc(sizeof(char*) * width);
	
	for (i = 0 ; i < wide ; i++) {
		M->map[i] = malloc(sizeof(char) * wide);
	}
		
	P[0].turn = true;
	P[1].turn = !P[0].turn;
	
	P[0].put = 'X';
	P[1].put = 'O';

	for (i = 0; i < width ; i++) {
		for (j = 0 ; j < wide ; j++) {
			M->map[i][j] = '-';
		}
	}
}

void freeMap(Map *M, int width, int wide) {
	int i;
	
	for (i = 0 ; i < wide ; i++) {
		free(M->map[i]);
	}
		
	free(M->map);
}

void showMenu() {
	system("cls");
	printf(" ---- Tic Tac Toe ----\n");
	printf("\n [1] Play");
	printf("\n [2] How To Play");
	printf("\n [3] Change Board Size");
	printf("\n [4] Exit \n");
}

void showHowTo() {
	system("cls");
	printf("\n There will be box you just need to write it coordinate in console");
	printf("\n Choose your box and line up the 'X' or 'O' symbol to win");
	printf("\n Line can be diagonal or straight.");
	printf("\n\n You can modify your tic tac toe board\n to be minimum of 3x3 and maximum of 9x9");
	printf("\n\n\t\tPress any button to back...");
}

void showBoard(Map M, int width, int wide) {
	int i, j;
	int k = 1;
	
	for (i = 0 ; i < width ; i++) {
		printf("\t");
		for (j = 0 ; j < wide ; j++) {
			if (M.map[i][j] == '-') {
				printf("%02d", k);
			} else if (j == wide - 1) {
				printf("%c ", M.map[i][j]);
			} else if (j == 0) {
				printf(" %c", M.map[i][j]);
			} else {
				printf("%c ", M.map[i][j]);
			}
			
			if (j != wide-1) {
				printf(" | ");
			}
				
			k++;
		}
		
		printf("\n\t");
		
		if (j == wide && i == width-1) 
			continue;
		
		for (j = 0 ; j < 2 + (width - 1) * 5; j++) {
			// Helped by https://github.com/Leviynn
			printf("-");
		}
			
		printf("\n");
	}
}

void move(Player P[], Map *M, int width, int wide) {
	int i, j, k = 1, pick, max = width * wide;
	string buffer;
	
	while(true) {
		printf("\n Select your box : "); fgets(buffer, MAX_STRING, stdin);
		pick = atoi(buffer);
		
		if (pick < 1 || pick > max) {
			printf("\n\tInput must be in range of 1 - %d", max);
			getch();
			
			break;
		}

		int* coords = getLocation(*M, width, wide, pick);
		i = coords[0];
		j = coords[1];
		
		if (checkFill(*M, i, j)) {
			printf("\n\tBox already filled");
			getch();
			
			break;
		}
	
		free(coords);
		
		M->map[i][j] = P[getTurn(P)].put;
		
		changeTurn(P);
		
		break;
	}
	
}

void changeTurn(Player P[]) {
	P[0].turn = P[1].turn;
	P[1].turn = !P[0].turn;
}

int getTurn(Player P[]) {
	return !P[0].turn; // Return current player index
}

int checkFill(Map M, int i, int j) {
	return (M.map[i][j] == 'X') ?  1 :
           (M.map[i][j] == 'O') ?  1 : 0;
}

int checkDraw(Map M, int width, int wide) {
    int i, j;
	int haveX = 0;
	int haveO = 0;
	int checkBaris = 0;
	int checkKolom = 0;
	int checkDiagonalKiri = 0;
	int checkDiagonalKanan = 0;

    //Cek per baris
    for (i = 0; i < width; i++) {
		haveX = 0;
		haveO = 0;

		for(j = 0; j < wide; j++) {
			if (M.map[i][j] == 'X') {
				haveX++;
			} else if (M.map[i][j] == 'O') {
				haveO++;
			}
		}

		checkBaris += haveX > 0 && haveO > 0 ? 1 : 0;
	}

    // Cek per kolom
    for (j = 0; j < wide ; j++) {
		haveX = 0;
		haveO = 0;
		
        for(i = 0; i < width; i++) {
			if (M.map[i][j] == 'X') {
				haveX++;
			} else if (M.map[i][j] == 'O') {
				haveO++;
			}
		}

		checkKolom += haveX > 0 && haveO > 0 ? 1 : 0;
    }

    // Cek diagonal ke kanan bawah
    for (j = 0; j < wide; j++) {
		if (M.map[j][j] == 'X') {
			haveX++;
		} else if (M.map[j][j] == 'O') {
			haveO++;
		}
	}
    
	checkDiagonalKanan += haveX > 0 && haveO > 0 ? 1 : 0;

    // Cek diagonal ke kanan atas    
	for (j = 0; j < wide; j++) {
 		if (M.map[j][wide-1-j] == 'X') {
			haveX++;
		} else if (M.map[j][wide-1-j] == 'O') {
			haveO++;
		}
	}
       
	checkDiagonalKiri += haveX > 0 && haveO > 0 ? 1 : 0;
                 
	return checkBaris == width && checkKolom == wide && checkDiagonalKanan == 1 && checkDiagonalKiri == 1;
}

int checkWin(Map M, int width, int wide) {
	int count = 0;
    int i, j;

	//Cek per baris
    for (i = 0; i < width; i++) {
        count = 0;
        
		for(j = 0; j < wide; j++) {
			count += (M.map[i][j] == 'X')?  1 :
                     (M.map[i][j] == 'O')? -1 : 0;
		}

        if (count == width || count == -(width)) {
			return count / abs(count);
		}			
    }

    // Cek per kolom
    for (j = 0; j < wide ; j++){
        count = 0;
        
        for(i = 0; i < width; i++) {
			count += (M.map[i][j] == 'X')?  1 :
                     (M.map[i][j] == 'O')? -1 : 0;
		}
            
		if (count == wide || count == -(wide)) {
			return count / abs(count);
		}
    }

    // Cek diagonal ke kanan bawah
    count = 0;

    for (j = 0; j < wide; j++) {
		count += (M.map[j][j] == 'X')?  1 :
                 (M.map[j][j] == 'O')? -1 : 0;
	}
        
    
    if (count == wide || count == -(wide))  {
		return count / abs(count); 
	}

    // Cek diagonal ke kanan atas
    count = 0;
    
	for (j = 0; j < wide; j++) {
		count += (M.map[j][wide-1-j] == 'X')?  1 :
                 (M.map[j][wide-1-j] == 'O')? -1 : 0;
	}

    if (count == wide || count == -(wide)) {
		return count / abs(count); 
	}
		
    return 0;
}

void showWinOrDraw(Player P[], Map M, int width, int wide) {
	int win = checkWin(M, width, wide);
	int draw = checkDraw(M, width, wide);
	
	if (win == 1 || win == -1) {
		printf("\n\t %s\n\n", !P[0].turn ? 
			"Player 1 Win" : "Player 2 Win");
	} 
	
	if (draw) {
		printf("\n\t Draw!\n\n");
	}
		
	showBoard(M, width, wide);
	printf("\n\n\tPress any button to back...");
}

int* getLocation(Map M, int width, int wide, int pick) {
	int i, j, k = 1;
	
	int* locArr = malloc(sizeof(int) * 2);
	
	for (i = 0 ; i < width ; i++) {
		for (j = 0 ; j < wide ; j++) {
			if (pick == k) {
				break; 
			}
			
			k++;
		}	
		
		if (pick == k && j == wide) {
			continue;
		}
			
		
		if (pick == k) {
			break;
		}
	}
	
	locArr[0] = i;
	locArr[1] = j;
	
	return locArr;
}
