#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];

enum Symbol {
    EMPTY = ' ',
    PLAYER = 'X',
    COMPUTER = 'O'
};


void playGame();
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);
char checkLine(char *c1, char *c2, char *c3);
char* findEmptyCell();


int main() {
    char response;

    do {

        response = ' ';
        playGame();
        
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response);
        response = toupper(response);

    } while (response == 'Y');
    
    printf("Thanks for playing!");

    return 0;
}

void playGame() {

    char winner = ' ';
    resetBoard();

    while (winner == ' ' && checkFreeSpaces() != 0) {
        
        printBoard();
        playerMove();
        winner = checkWinner();

        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }

        computerMove();
        winner = checkWinner();

        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }
    }

    printBoard();
    printWinner(winner);
}

void resetBoard(){

    for(int i = 0; i < 3; i++){

        for(int j = 0; j < 3; j++){

            board[i][j] = ' ';
        }
    }
}
void printBoard(){

    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");

    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");

    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}
int checkFreeSpaces(){

    int freeSpaces = 9;

    for(int i = 0; i < 3; i++){

        for(int j = 0; j < 3; j++){

            if(board[i][j] != ' '){
                freeSpaces--;
            }
        }
    }

    return freeSpaces;
}
void playerMove(){

    int x, y;   

    do{

        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;

        printf("Enter column $(1-3): ");
        scanf("%d", &y);
        y--;

        if(board[x][y] != ' '){

           printf("Invalid move!\n");
        }
        else{

            board[x][y] = PLAYER;
            break;
        }

    } while (board[x][y] != ' ');
}

void computerMove() {

    if (checkFreeSpaces() > 0) {

        char *emptyCell = findEmptyCell();

        if (emptyCell != NULL) {

            *emptyCell = COMPUTER;
        }
    } else {

        printWinner(EMPTY);
    }
}

char* findEmptyCell() {

    srand(time(0));
    int x, y;

    do {

        x = rand() % 3;
        y = rand() % 3;
    } while (*(board[x] + y) != EMPTY);

    return &(board[x][y]);
}


char checkWinner() {

    char winner = ' ';
    
    // Check rows and columns
    for (int i = 0; i < 3; i++) {

        winner = checkLine(&board[i][0], &board[i][1], &board[i][2]);

        if (winner != EMPTY) {

            return winner;
        }

        winner = checkLine(&board[0][i], &board[1][i], &board[2][i]);
        if (winner != EMPTY) {

            return winner;
        }
    }

    // Check diagonals
    winner = checkLine(&board[0][0], &board[1][1], &board[2][2]);
    if (winner != EMPTY) {

        return winner;
    }

    winner = checkLine(&board[0][2], &board[1][1], &board[2][0]);
    if (winner != EMPTY) {

        return winner;
    }

    return EMPTY;
}

char checkLine(char *c1, char *c2, char *c3) {

    if (*c1 != EMPTY && *c1 == *c2 && *c2 == *c3) {

        return *c1;
    } else {

        return EMPTY;
    }
}

void printWinner(char winner) {

    
    switch (winner) {
        
        case 'X':
            printf("You Win!!");
            break;

        case 'O':
            printf("You lose!!");
            break;
            
        default:
            printf("Draw!");
            break;
    }
}