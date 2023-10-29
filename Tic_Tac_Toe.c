#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Tic_Tac_Toe.h"

// Define the game board and symbols
char board[3][3];

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
char* findEmptyCell();


int main() {

    char response;

    do {
        response = ' '; // Initialize response to a space character

        // Start and play a game of Tic Tac Toe
        playGame();
        
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response); // Read the user's response
        response = toupper(response); // Convert the response to uppercase

    } while (response == 'Y'); // Repeat the loop if the response is 'Y'

    printf("Thanks for playing!"); // Display a thank-you message when the game is over

    return 0;
}


void playGame() {

    char winner = ' '; // Initialize the winner variable to a space character
    resetBoard(); // Reset the game board for a new game

    // Main game loop that continues until there is a winner or no more free spaces
    while (winner == ' ' && checkFreeSpaces() != 0) {

        printBoard(); // Display the current game board
        playerMove(); // Allow the player to make a move
        winner = checkWinner(); // Check if there is a winner after the player's move

        // If there's a winner or no more free spaces, break out of the loop
        if (winner != ' ' || checkFreeSpaces() == 0) {

            break;
        }

        computerMove(); // Let the computer make its move
        winner = checkWinner(); // Check if there is a winner after the computer's move

        // If there's a winner or no more free spaces, break out of the loop
        if (winner != ' ' || checkFreeSpaces() == 0) {

            break;
        }
    }

    printBoard(); // Display the final game board
    printWinner(winner); // Print the winner or indicate a tie
}


void resetBoard() {

    // Loop through the rows and columns of the game board
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {

            board[i][j] = ' '; // Set each cell to an empty space character
        }
    }
}


void printBoard() {

    // Display the current state of the Tic Tac Toe board
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");

    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");

    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}


int checkFreeSpaces() {

    int freeSpaces = 9; // Initialize the count of free spaces to the total number of cells (9 in a 3x3 board)

    // Loop through the rows and columns of the game board
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {

            if (board[i][j] != ' ') {

                freeSpaces--; // Decrement the count for each non-empty cell
            }
        }
    }

    return freeSpaces; // Return the count of remaining free spaces
}


void playerMove() {

    int x, y;

    do {

        printf("Enter row #(1-3): ");
        scanf("%d", &x); // Read the row number from the player
        x--;

        printf("Enter column #(1-3): ");
        scanf("%d", &y); // Read the column number from the player
        y--;

        if (board[x][y] != ' ') {

            printf("Invalid move!\n"); // Inform the player of an invalid move if the selected cell is not empty
        } 
        else {

            board[x][y] = PLAYER; // Place the player's symbol ('X') in the selected empty cell
            break; // Exit the loop when a valid move is made
        }

    } while (board[x][y] != ' '); // Continue looping until a valid move is entered
}


void computerMove() {

    if (checkFreeSpaces() > 0) { // Check if there are empty spaces left on the board

        char *emptyCell = findEmptyCell(); // Find an empty cell on the board

        if (emptyCell != NULL) { // Ensure there is an empty cell available

            *emptyCell = COMPUTER; // Place the computer's symbol ('O') in the selected empty cell
        }
    } 
    else {

        printWinner(EMPTY); // If no empty spaces are left, indicate a tie by passing 'EMPTY' to printWinner
    }
}


char* findEmptyCell() {

    srand(time(0)); // Seed the random number generator with the current time
    int x, y;

    do {

        x = rand() % 3; // Generate a random row index between 0 and 2
        y = rand() % 3; // Generate a random column index between 0 and 2
    } while (*(board[x] + y) != EMPTY); // Continue looping until an empty cell is found

    return &(board[x][y]); // Return a pointer to the address of the empty cell
}



char checkWinner() {

    char winner = ' '; // Initialize the winner variable to a space character

    // Check rows and columns for a winner
    for (int i = 0; i < 3; i++) {

        // Check rows
        winner = checkLine(&board[i][0], &board[i][1], &board[i][2]); // Check a row for a winner
        if (winner != EMPTY) { // If a winner is found in a row, return the winner

            return winner;
        }

        // Check columns
        winner = checkLine(&board[0][i], &board[1][i], &board[2][i]); // Check a column for a winner
        if (winner != EMPTY) { // If a winner is found in a column, return the winner

            return winner;
        }
    }

    // Check diagonals for a winner
    winner = checkLine(&board[0][0], &board[1][1], &board[2][2]); // Check the main diagonal
    if (winner != EMPTY) { // If a winner is found in the main diagonal, return the winner

        return winner;
    }

    winner = checkLine(&board[0][2], &board[1][1], &board[2][0]); // Check the other diagonal
    if (winner != EMPTY) { // If a winner is found in the other diagonal, return the winner

        return winner;
    }

    return EMPTY; // If no winner is found in rows, columns, or diagonals, return 'EMPTY'
}


char checkLine(char *c1, char *c2, char *c3) {
    // Check if all three cells in the line have the same non-empty symbol and return that symbol
    if (*c1 != EMPTY && *c1 == *c2 && *c2 == *c3) {

        return *c1;
    } 
    else {

        return EMPTY; // If the cells don't have the same non-empty symbol, return 'EMPTY'
    }
}


void printWinner(char winner) {

    // Display the outcome of the game based on the 'winner' parameter

    switch (winner) {

        case PLAYER:
            printf("You Win!!"); // If the player wins, print a victory message
            break;

        case COMPUTER:

            printf("You lose!!"); // If the computer wins, print a defeat message
            break;

        default:
        
            printf("Draw!"); // If there is no winner (a draw), print a draw message
            break;
    }
}
