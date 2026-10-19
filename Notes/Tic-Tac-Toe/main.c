#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{in_progress, tie, p1win, p2win} game_status;
typedef enum{player1 = 1, player2 = 2} player;

void renderBoard(char **layout);
bool captureBox(player playerToMove, int coordX, int coordY, char **layout);
game_status checkGameStatus(char **layout);
game_status checkWinnerHelper(char input);

int main(){

	char **board = malloc(3 * sizeof(char *));
	for(int i = 0; i < 3; i++){
		board[i] = malloc(3);
		for(int j = 0; j < 3; j++){
			board[i][j] = ' ';
		}
	}

	game_status status = in_progress;
	player currentPlayer = player1;
	int coordX = 0;
	int coordY = 0;

	while(status == in_progress){
		printf("Its Your Turn, Player%d\n", currentPlayer);
		printf("Enter coords to capture (seperated by a space: x y): ");
		if(scanf("%d %d", &coordX, &coordY) == 2){
			if(coordX > 2 || coordY > 2){
				printf("Invalid Coord! (Range 0, 1, 2)\n");
			}
			else if(captureBox(currentPlayer, coordX, coordY, board)){
				printf("Capture Successful!\n");
				renderBoard(board);
				status = checkGameStatus(board);

				// swap player turn, clear coord input
				currentPlayer = currentPlayer == player1? player2 : player1;
				coordX = 0;
				coordY = 0;		
			}
			else{
				printf("Failed to capture!\n");
			}
		}
		else{
			printf("Invalid Coord! Try Again\n");
		}
	}
	

	switch(status){
		case p1win: printf("Player1 (X) Wins!\n"); break;
		case p2win: printf("PLayer2 (O) Wins!\n"); break; 
		case tie: printf("Its a TIE!\n"); break;   
	}

	for(int i = 0; i < 3; i++){
		free(board[i]);
		board[i] = NULL;
	}
	free(board);
	board = NULL;
	return 0;
}

void renderBoard(char **layout){
    printf("\nCurrent Board:\n");
    printf("     0   1   2 \n"); // Optional: Column coordinate labels
    printf("   -------------\n");
    for(int i = 0; i < 3; i++){
        printf(" %d |", i); // Row label and left border
        for(int j = 0; j < 3; j++){
            printf(" %c |", layout[i][j]); // Cell content with right border
        }
        printf("\n   -------------\n");
    }
    printf("\n");
}

bool captureBox(player playerToMove, int coordX, int coordY, char **layout){

	if(layout[coordX][coordY] != ' '){
		return false;
	}
	else{
		layout[coordX][coordY] = playerToMove == player1? 'X' : 'O';
		return true;
	}

}

game_status checkWinnerHelper(char input){
	switch(input){
		case 'X': return p1win;
		case 'O': return p2win;
	}
}

game_status checkGameStatus(char **layout){
	// check - winner
	for(int i = 0; i < 3; i++){
		if(layout[i][0] != ' ' && layout[i][0] == layout[i][1] && layout[i][1] == layout[i][2]){
			return checkWinnerHelper(layout[i][0]);
		}
	}

	// check | winner
	for(int j = 0; j < 3; j++){
		if(layout[0][j] !=' ' && layout[0][j] == layout[1][j] && layout[1][j] == layout[2][j]){
			return checkWinnerHelper(layout[0][j]);
		}
	}

	// check \ winner
	if(layout[0][0] != ' ' && layout[0][0] == layout[1][1] && layout[1][1] == layout[2][2]){
		return checkWinnerHelper(layout[0][0]);
	} 

	// check / winner
	if(layout[0][2] != ' ' && layout[0][2] == layout[1][1] && layout[1][1] == layout[2][0]){
		return checkWinnerHelper(layout[0][2]);
	}

	for(int i = 0; i < 3; i++){
    		for(int j = 0; j < 3; j++){
        		if(layout[i][j] == ' ') {
            			return in_progress; // Found an empty spot, game keeps going
        		}
    		}
	}
	return tie; // No winner found and no empty spots left = TIE!	
}
