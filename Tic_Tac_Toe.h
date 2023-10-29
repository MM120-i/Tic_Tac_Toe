#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

// Define the game board and symbols
extern char board[3][3];

enum Symbol {
    EMPTY = ' ',   // Represents an empty cell
    PLAYER = 'X',  // Represents the player's move
    COMPUTER = 'O' // Represents the computer's move
};

// Function prototypes
void playGame();
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);
char checkLine(char *c1, char *c2, char *c3);
char *findEmptyCell();

#endif
