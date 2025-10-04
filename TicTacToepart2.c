#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TicTacToe.h"

int main() {
    int size;
    printf("Enter the board size N (3 <= N <= 10): "); //Ask the board size from the user
    scanf("%d", &size);

    if (size < MIN_SIZE || size > MAX_SIZE) {    // Validation of the board size
        printf("Invalid size!\n");
        return 1;
    }

    char *board = initBoard(size);  // Memory allocation
    if (board == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    FILE *logFile = fopen("game_log.txt", "w");   // Open file to log moves
    if (!logFile) {
        printf("Error opening log file.\n");
        free(board);
        return 1;
    }

    srand(time(NULL)); // Set up random seed to computer moves

    char user = 'X';
    char computer = 'O';
    int row, col;
    int userTurn = 1; // Always starts by the user

    // Main game loop
    while (1) {
        displayBoard(board, size); // Show current board

        if (userTurn) {
	       
	    // User moves
            getUserInput(&row, &col, size, user); // Get the row and colomn from the user to check the validation of the move
            if (!isValidMove(row, col, size, board)) {
                printf("Invalid move! Please try again.\n");
                continue;
            }
            board[row * size + col] = user;     // Update the board and log move
            logMove(logFile, board, size, row, col, user);

            if (checkWin(board, size, user)) {   // Checking for win
                displayBoard(board, size);
                printf("Player %c wins!\n", user);
                break;
            }
        } else {
	    // Computer moves
            getComputerMove(&row, &col, size, board); // Get the row and colomn
            board[row * size + col] = computer;
            printf("Computer played at (%d, %d)\n", row, col);
            logMove(logFile, board, size, row, col, computer);

            if (checkWin(board, size, computer)) {  // Checking for win
                displayBoard(board, size);
                printf("Computer (%c) wins!\n", computer);
                break;
            }
        }

        if (checkDraw(board, size)) {  // Checking for draw
            displayBoard(board, size);
            printf("Game is a draw!\n");
            break;
        }

        userTurn = 1 - userTurn; // Switch  the turn 
    }

    fclose(logFile);
    free(board);
    return 0;
}


char *initBoard(int size) {    // Initialization of the board
    char *board = (char *)malloc(size * size * sizeof(char));
    if (board != NULL) {
        for (int i = 0; i < size * size; i++)
            board[i] = ' ';
    }
    return board;
}

void displayBoard(char *board, int size) {  // Show the board as a grid
    printf("\n    ");
    for (int j = 0; j < size; j++) {
        printf("  %d   ", j);
    }
    printf("\n");

    printf("    ");
    for (int j = 0; j < size; j++)
	    printf("------");
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf(" %d |", i);
        for (int j = 0; j < size; j++) {
            printf("  %c  |", board[i * size + j]);
        }
        printf("\n");

        printf("    ");
        for (int j = 0; j < size; j++)
	       	printf("------");
        printf("\n");
    }
    printf("\n");
}


void getUserInput(int *row, int *col, int size, char player) {       // Get tthe row and colomn from the user
    printf("Player %c, enter row and column (0-%d): ", player, size - 1);
    scanf("%d %d", row, col);
}


void getComputerMove(int *row, int *col, int size, char *board) {   // Make  random for computer move
    do {
        *row = rand() % size;
        *col = rand() % size;
    } while (!isValidMove(*row, *col, size, board));
}


int isValidMove(int row, int col, int size, char *board) {    // Validation of the move
    if (row < 0 || col < 0 || row >= size || col >= size)
        return 0;
    if (board[row * size + col] != ' ')
        return 0;
    return 1;
}


int checkWin(char *board, int size, char symbol) {    // Check if the player has won
    int win;
    for (int i = 0; i < size; i++) {    // Check for the rows
        win = 1;
        for (int j = 0; j < size; j++)
            if (board[i * size + j] != symbol) win = 0;
        if (win) return 1;
    }
    for (int j = 0; j < size; j++) {    // Check for the colomns
        win = 1;
        for (int i = 0; i < size; i++)
            if (board[i * size + j] != symbol) win = 0;
        if (win) return 1;
    }
    win = 1; 
    for (int i = 0; i < size; i++)    // Check for the main diagonal
        if (board[i * size + i] != symbol) win = 0;
    if (win) return 1;

    win = 1;
    for (int i = 0; i < size; i++)    // Check for the anti diagonal
        if (board[i * size + (size - i - 1)] != symbol) win = 0;
    if (win) return 1;

    return 0;
}


int checkDraw(char *board, int size) {   // Check if the board is draw
    for (int i = 0; i < size * size; i++)
        if (board[i] == ' ')
            return 0;
    return 1;
}

void logMove(FILE *log, char *board, int size, int row, int col, char symbol) {    // Write the move to file 
    fprintf(log, "Player %c: (%d, %d)\n", symbol, row, col);
}

