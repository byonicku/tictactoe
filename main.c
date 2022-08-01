#include "header.h"

int main() {
	Player P[2];
	Map M;
	int menuSelect, check = 0, pick;

	do{
		menu(&menuSelect);
		switch(menuSelect){
			case 1 :
				init(P, &M);
				check = 0;
				do{
					if(checkWin(M) == 1){
						system("cls");
						if(check%2==0) printf("Player 1\n");
						else printf("Player 2\n");
						board(M);
						if(check%2!=0) printf("\nPlayer 1 Win");
						else printf("\nPlayer 2 Win");
						break;
					}
					else if(checkWin(M) == 2){
						system("cls");
						if(check%2==0) printf("Player 1\n");
						else printf("Player 2\n");
						board(M);
						printf("\nDraw!");
						break;
					}
					do{
						system("cls");
						if(check%2==0) printf("Player 1\n");
						else printf("Player 2\n");
						board(M);
						move(P, &M, &pick, &check);
							if(pick<1 || pick>9){
								printf("\n\tInput must be in range of 1 - 9");
								getch();
							}
					}while(pick<1 || pick>9);
				}while(true);
				break;
			case 2:
				howTo();
				break;
			case 0:
				printf("\n\t [!] Thanks for playing!");
				break;
			default:
				printf("\n\t [!] Menu not found!");
		} getch();
	}while(menuSelect!=0);
	
	return 0;
}
