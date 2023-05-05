#include "header.h"

int main() {
	Player P[2];
	Map M;
		
	int menuSelect = 0;
	int width = DEFAULT_WIDTH, wide = DEFAULT_WIDE;
	string buffer;
	
	do{
		showMenu();

		printf("\n >>> "); fgets(buffer, MAX_STRING, stdin);
		menuSelect = atoi(buffer);
		
		switch(menuSelect){
			case 1 :
				init(P, &M, width, wide);

				do{
					system("cls");
					
					if(checkWin(M, width, wide) != 0) {
						showWin(P, M, width, wide);
						break;
					}
					
					printf("\n\t %s\n\n", P[0].turn ? " Player 1 <X>" : " Player 2 <O>");
					
					showBoard(M, width, wide);

					move(P, &M, width, wide);
				} while(true);
				
				freePointer(&M, width, wide);
				break;
			case 2:
				showHowTo();
				break;
			case 3:
				printf("\n\t [!] Thanks for playing!");
				freePointer(&M, width, wide);
				break;
			default:
				printf("\n\t [!] Menu not found!");
		} getch();
		
	}while(menuSelect != 3);
	
	return 0;
}
