#include "header.h"

void init(Player P[], Map *M, int width, int wide){
	int i, j;
	srand(time(NULL));
	
	M->map = malloc(sizeof(char*) * width);
	
	for(i = 0 ; i < wide ; i++)
		M->map[i] = malloc(sizeof(char) * wide);
	
	//random start
	P[0].turn = rand() % 2 ? true : false;
	P[1].turn = !P[0].turn;
	
	P[0].put = 'X';
	P[1].put = 'O';

	for(i = 0; i < width ; i++)
		for(j = 0 ; j < wide ; j++)
			M->map[i][j] = '-';	
}

void freePointer(Map *M, int width, int wide){
	int i;
	
	for(i = 0 ; i < wide ; i++)
		free(M->map[i]);
		
	free(M->map);
}

void setMapSize(Map *M, int width, int wide){
	int i, j;
	
	M->map = realloc(M->map, sizeof(char*) * width);
	
	for(i = 0 ; i < wide ; i++){
		M->map[i] = realloc(M->map[i], sizeof(char) * wide);
		
		if(M->map[i] == NULL) exit(1);
	}
	
	for(i = 0; i < width ; i++)
		for(j = 0 ; j < wide ; j++)
			M->map[i][j] = '-';
}

void showMenu(){
	system("cls");
	printf(" ---- Tic Tac Toe ----\n");
	printf("\n [1] Play");
	printf("\n [2] How To Play");
	printf("\n [3] Change Board Size");
	printf("\n [4] Exit \n");
}

void showHowTo(){
	system("cls");
	printf("\n There will be 9 box you just need to write it in console");
	printf("\n Choose your box and line up the 'X' or 'O' symbol to win");
	printf("\n Line can be diagonal or straight.");
	printf("\n\n\t\tPress any button to back...");
}

void showBoard(Map M, int width, int wide){
	int i, j;
	int k = 1;
	
	for(i = 0 ; i < width ; i++){
		printf("\t");
		for(j = 0 ; j < wide ; j++){
			if(M.map[i][j] == '-') printf("%02d", k);
			else if(j == wide - 1) printf("%c ", M.map[i][j]);
			else if(j == 0) printf(" %c", M.map[i][j]);
			else printf("%c ", M.map[i][j]);
			
			if(j != wide-1) printf(" | ");
			k++;
		}
		printf("\n\t");
		
		if(j == wide && i == width-1) continue;
		
		for(j = 0 ; j < 2 + (width-1)*5; j++){ // dibantu jeanny https://github.com/Leviynn
			printf("-");
		}
		
		printf("\n");
	}
}

void move(Player P[], Map *M, int width, int wide){
	int i, j, k = 1, pick;
	string buffer;
	
	while(1){
		printf("\n Select your box : "); fgets(buffer, MAX_STRING, stdin);
		pick = atoi(buffer);
		
		if(pick<1 || pick>width*wide){
			printf("\n\tInput must be in range of 1 - %d", width * wide);
			getch();
			
			break;
		}

		if(checkFill(*M, pick, width, wide)){
			printf("\n\tBox already filled");
			getch();
			
			break;
		}
	
		//get location
		int* temp = getLocation(*M, width, wide, pick);
		
		i = temp[0];
		j = temp[1];
		
		free(temp);
		
		M->map[i][j] = P[getTurn(P)].put;
//		printf("i : %d, j : %d, input : %d\n map %c put %c", i, j, pick, M->map[i][j], P[getTurn(P)].put); debug
//		getch();
		
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

int checkFill(Map M, int pick, int width, int wide){
	int* temp = getLocation(M, width, wide, pick);
	int i, j;
	
	i = temp[0];
	j = temp[1];
	
	return (M.map[i][j] == 'X') ?  1 :
           (M.map[i][j] == 'O') ?  1 : 0;
}

int checkWin(Map M, int width, int wide){
	int count = 0;
    int i, j;

    // Check each of 3 rows:
    for(i = 0; i < width; i++){
        count = 0;
        
		for(j = 0; j < wide; j++){
            count += (M.map[i][j] == 'X')?  1 :
                     (M.map[i][j] == 'O')? -1 : 0;
        }

        if (count == width || count == -(width)) 
			return count / abs(count); // Return either 1 or -1
    }

    // Check each of 3 columns.
    for(j = 0; j < wide ; j++){
        count = 0;
        for(i = 0; i < width; i++){
            count += (M.map[i][j] == 'X')?  1 :
                     (M.map[i][j] == 'O')? -1 : 0;
        }
        
		if (count == wide || count == -(wide))
			return count / abs(count); // Return either 1 or -1
    }

    // Check Left-to-Right downward Diagonal:
    count = 0;

    for(j = 0; j < wide; ++j){
        count += (M.map[j][j] == 'X')?  1 :
                 (M.map[j][j] == 'O')? -1 : 0;
    }
    if (count == wide || count == -(wide)) 
		return count / abs(count); // Return either 1 or -1

    // Check Left-to-Right upward Diagonal
    count = 0;
    
	for(j = 0; j < wide; j++){
        count += (M.map[j][2-j] == 'X')?  1 :
                 (M.map[j][2-j] == 'O')? -1 : 0;
    }

    if (count == wide || count == -(wide)) 
		return count / abs(count); // Return either 1 or -1
		
	count = 0;
	
	for(i = 0 ; i < width ; i++){
		for(j = 0 ; j < wide ; j++){
			if(M.map[i][j] != 'X' && M.map[i][j] != 'O') 
				count++;
		}
	}
	
	if(count == 0)
		return 2;
	
    return 0;
}

void showWin(Player P[], Map M, int width, int wide){
	int win = checkWin(M, width, wide);
	
	if(win == 1 || win == -1){
		printf("\n\t %s\n\n", !P[0].turn ? "Player 1 Win" : "Player 2 Win");
	}
	else if(win == 2){
		printf("\n\t Draw!\n\n");
	}
	
	showBoard(M, width, wide);
	printf("\n\n\tPress any button to back...");
}

int* getLocation(Map M, int width, int wide, int pick){
	int i, j, k = 1;
	
	int* locArr = malloc(sizeof(int) * 2);
	
	for(i = 0 ; i < width ; i++){			
		for(j = 0 ; j < wide ; j++){
			if(pick == k) break; 
			k++;
		}	
		if(pick == k && j == wide) continue;
		
		if(pick == k) break;
	}
	
	locArr[0] = i;
	locArr[1] = j;
	
	return locArr;
}
