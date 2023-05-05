#include "header.h"

int main() {
	Player P[2];
	Map M;
		
	int menuSelect = 0;
	int width = DEFAULT_WIDTH, wide = DEFAULT_WIDE;
	int newWidth = 0, newWide = 0;
	string buffer;
	
	system("color 81");
	
	do{
		showMenu();

		printf("\n >>> "); fgets(buffer, MAX_STRING, stdin);
		menuSelect = atoi(buffer);
		
		switch(menuSelect){
			case 1 :
				init(P, &M, width, wide);
				
				do{
					system("cls");
					
					if(checkWin(M, width, wide)  != 0 ||
					   checkDraw(M, width, wide) != 0) {
					   	
						showWinOrDraw(P, M, width, wide);
						break;
					}
					
					printf("\n\t%s\n\n", P[0].turn ? 
						"Player 1 <X>" : "Player 2 <O>");
					
					showBoard(M, width, wide);

					move(P, &M, width, wide);
				} while(true);
				
				freePointer(&M, width, wide);
				break;
			case 2:
				showHowTo();
				break;
			case 3:
				printf("\n\t ==== Update Board Size ====");
				
				printf("\n\t Input width	: "); fgets(buffer, MAX_STRING, stdin);
				newWidth = atoi(buffer);
				
				printf("\t Input wide 	: "); fgets(buffer, MAX_STRING, stdin);
				newWide = atoi(buffer);
				
				if(newWidth < 3 || newWide < 3)
					printf("\n\t Board size cannot be under 3 x 3 !");
				else if(newWidth > 9 || newWide > 9)
					printf("\n\t Board size cannot be over 9 x 9 !");
				else if(newWidth != newWide)
					printf("\n\t Board width and wide size must be same !");
				else{
					width = newWidth;
					wide = newWide;
					
					printf("\n\t Successfully update board size!");
				}
								
				break;
			case 4:
				printf("\n\t [!] Thanks for playing!");
				break;
			default:
				printf("\n\t [!] Menu not found!");
		} getch();
		
	}while(menuSelect != 4);
	
	return 0;
}
