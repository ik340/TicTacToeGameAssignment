#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TicTacToe.h"

int main() {
    int size;
    printf("Enter the board size N (3 <= N <= 10): ");   // Ask the board size from the user
    scanf("%d", &size);

    if (size < MIN_SIZE || size > MAX_SIZE) {       // Validation of the board size
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

    srand(time(NULL)); // Set up random seed for computer moves

  
    char players[3] = {'X', 'O', 'Z'};      // Symbols of players
    int isComputer[3] = {0, 0, 0};         // 0 = human user, 1 = computer

    
    printf("Player selection - At least one player must be human.\n");     // Selection of players(At least one player must be human)
    for (int i = 0; i < 3; i++) {
        char choice;
        printf("Is Player %c a Human user  or Computer? (Enter h or c) -   ", players[i]);
        scanf(" %c", &choice);
        if (choice == 'c' || choice == 'C')
            isComputer[i] = 1;
        else
            isComputer[i] = 0;
    }

    
    if (isComputer[0] && isComputer[1] && isComputer[2]) {      // Checking that at least one player is human
        printf("All players were set as computer.Player X is now set as Human.\n");
        isComputer[0] = 0;
    }

    int turn = 0;     // Begins with Player X
    int row, col;

    while (1) {    // Starting the game(Main game loop)
        displayBoard(board, size);
        printf("Turn: Player %c (%s)\n", players[turn], isComputer[turn] ? "Computer" : "Human");

        if (isComputer[turn]) {
           
            getComputerMove(&row, &col, size, board);    // Move of computer
            board[row * size + col] = players[turn];
            printf("Computer (%c) played at (%d, %d)\n", players[turn], row, col);
            logMove(logFile, board, size, row, col, players[turn]);
        } else {
            
            getUserInput(&row, &col, size, players[turn]);   // Move of human
            if (!isValidMove(row, col, size, board)) {
                printf("Invalid move! Please Try again.\n");
                continue;
            }
            board[row * size + col] = players[turn];     //  Updating  the board and log move
            logMove(logFile, board, size, row, col, players[turn]);
        }

        
        if (checkWin(board, size, players[turn])) {      // Checking for win
            displayBoard(board, size);
            printf("Player %c (%s) WINS!\n", players[turn], isComputer[turn] ? "Computer" : "Human");
            break;
        }

        
        if (checkDraw(board, size)) {         // Checking for draw
            displayBoard(board, size);
            printf("Game is a draw!\n");
            break;
        }

        
        turn = (turn + 1) % 3;  // to get the turns in cylic order
    }

    fclose(logFile);
    free(board);
    return 0;
}


char *initBoard(int size) {       // Initialization of the board
    char *board = (char *)malloc(size * size * sizeof(char));
    if (board != NULL) {
        for (int i = 0; i < size * size; i++)
            board[i] = ' ';
    }
    return board;
}

void displayBoard(char *board, int size) {    // Show the board as a grid
    printf("\n    ");
    for (int j = 0; j < size; j++) {
        printf("  %d   ", j);
    }
    printf("\n    ");
    for (int j = 0; j < size; j++)
	    printf("------");
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf(" %d |", i);
        for (int j = 0; j < size; j++) {
            printf("  %c  |", board[i * size + j]);
        }
        printf("\n    ");
        for (int j = 0; j < size; j++)
	       	printf("------");
        printf("\n");
    }
    printf("\n");
}

void getUserInput(int *row, int *col, int size, char player) {   // Get the row and colomn from the user
    printf("Player %c, enter row and column (0-%d): ", player, size - 1);
    scanf("%d %d", row, col);
}

void getComputerMove(int *row, int *col, int size, char *board) {    // Generate random computer move
    do {
        *row = rand() % size;
        *col = rand() % size;
    } while (!isValidMove(*row, *col, size, board));
}

int isValidMove(int row, int col, int size, char *board) {      // Validation of the move
    if (row < 0 || col < 0 || row >= size || col >= size)
        return 0;
    if (board[row * size + col] != ' ')
        return 0;
    return 1;
}

int checkWin(char *board, int size, char symbol) {   // Check if the player has won
    int win;
    for (int i = 0; i < size; i++) {    // Check for the rows
        win = 1;
        for (int j = 0; j < size; j++)
            if (board[i * size + j] != symbol) win = 0;
        if (win) return 1;
    }
    for (int j = 0; j < size; j++) {   // Check for the colomns
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

int checkDraw(char *board, int size) {    // Check if the board is draw
    for (int i = 0; i < size * size; i++)
        if (board[i] == ' ')
            return 0;
    return 1;
}

void logMove(FILE *log, char *board, int size, int row, int col, char symbol) {    // Write the move to file
    fprintf(log, "Player %c: (%d, %d)\n", symbol, row, col);
}

