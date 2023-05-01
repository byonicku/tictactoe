#include "header.h"

int main() {
	Player P[2];
	Map M;
	int menuSelect = 0;
	string buffer;
	
	do{
		showMenu();

		printf("\n >>> "); fgets(buffer, MAX_STRING, stdin);
		menuSelect = atoi(buffer);
		
		switch(menuSelect){
			case 1 :
				init(P, &M);
				
				do{
					system("cls");
					
					if(checkWin(M) != -1) {
						showWin(P, M);
						break;
					}
					
					printf("\n\t %s\n\n", P[0].turn ? " Player 1 <X>" : " Player 2 <O>");
					
					showBoard(M);

					move(P, &M);
				} while(true);
				break;
			case 2:
				showHowTo();
				break;
			case 3:
				printf("\n\t [!] Thanks for playing!");
				break;
			default:
				printf("\n\t [!] Menu not found!");
		} getch();
		
	}while(menuSelect != 3);
	
	return 0;
}
