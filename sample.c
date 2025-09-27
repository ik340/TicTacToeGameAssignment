#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 3
#define MAX_SIZE 10

// ------------------- Function Prototypes -------------------
char *initBoard(int size);                           // Initialize game board (dynamic memory allocation)
void displayBoard(char *board, int size);            // Display current state of the board
void getUserInput(int *row, int *col, int size, char player);  // Ask user for row/column input
int isValidMove(int row, int col, int size, char *board);      // Validate move position
int checkWin(char *board, int size, char symbol);    // Check if a player has won
int checkDraw(char *board, int size);                // Check if the game is a draw
void logMove(FILE *log, char *board, int size);      // Log board state to a file

// ------------------------ MAIN FUNCTION ------------------------
int main() {
    int size;
    printf("Enter the board size (%d <= N <= %d): ", MIN_SIZE, MAX_SIZE);
    scanf("%d", &size);

    if (size < MIN_SIZE || size > MAX_SIZE) {
        printf("Invalid size! Exiting...\n");
        return 1;
    }

    // Allocate memory for the board dynamically
    char *board = initBoard(size);
    if (board == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    FILE *logFile = fopen("game_log.txt", "w");
    if (!logFile) {
        printf("Error opening log file.\n");
        free(board);
        return 1;
    }

    char players[2] = {'X', 'O'};
    int turn = 0;
    int row, col;
    int gameOver = 0;

    while (!gameOver) {
        displayBoard(board, size);

        // Get input until a valid move is entered
        do {
            getUserInput(&row, &col, size, players[turn]);
            if (!isValidMove(row - 1, col - 1, size, board)) {
                printf("Invalid move! Please try again.\n");
            } else {
                break;
            }
        } while (1);

        // Update the board
        board[(row - 1) * size + (col - 1)] = players[turn];

        // Log the board state after the move
        logMove(logFile, board, size);

        // Check for win/draw
        if (checkWin(board, size, players[turn])) {
            displayBoard(board, size);
            printf("Player %c wins!\n", players[turn]);
            gameOver = 1;
        } 
        else if (checkDraw(board, size)) {
            displayBoard(board, size);
            printf("It's a draw!\n");
            gameOver = 1;
        } 
        else {
            turn = 1 - turn; // Switch player
        }
    }

    fclose(logFile);
    free(board);
    return 0;
}

// ---------------------- FUNCTION DEFINITIONS ----------------------

// Allocate memory and initialize the board with spaces
char *initBoard(int size) {
    char *board = (char *)malloc(size * size * sizeof(char));
    if (board != NULL) {
        for (int i = 0; i < size * size; i++) {
            board[i] = ' ';
        }
    }
    return board;
}

// Print the board to the console
void displayBoard(char *board, int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i * size + j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");
        if (i < size - 1) {
            for (int k = 0; k < size; k++)
                printf("---%s", (k < size - 1) ? "+" : "");
            printf("\n");
        }
    }
    printf("\n");
}

// Ask the player for input
void getUserInput(int *row, int *col, int size, char player) {
    printf("Player %c, enter row and column (1-%d): ", player, size);
    scanf("%d %d", row, col);
}

// Check if the move is valid
int isValidMove(int row, int col, int size, char *board) {
    if (row < 0 || col < 0 || row >= size || col >= size)
        return 0;
    if (board[row * size + col] != ' ')
        return 0;
    return 1;
}

// Check if the player has won (rows, columns, diagonals)
int checkWin(char *board, int size, char symbol) {
    for (int i = 0; i < size; i++) {
        int rowWin = 1, colWin = 1;
        for (int j = 0; j < size; j++) {
            if (board[i * size + j] != symbol) rowWin = 0;
            if (board[j * size + i] != symbol) colWin = 0;
        }
        if (rowWin || colWin) return 1;
    }
    int diag1 = 1, diag2 = 1;
    for (int i = 0; i < size; i++) {
        if (board[i * size + i] != symbol) diag1 = 0;
        if (board[i * size + (size - i - 1)] != symbol) diag2 = 0;
    }
    return diag1 || diag2;
}

// Check if the board is full (draw condition)
int checkDraw(char *board, int size) {
    for (int i = 0; i < size * size; i++)
        if (board[i] == ' ')
            return 0;
    return 1;
}

// Write current board state to log file
void logMove(FILE *log, char *board, int size) {
    fprintf(log, "\nBoard State:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            fprintf(log, "%c ", board[i * size + j]);
        fprintf(log, "\n");
    }
    fflush(log);
}

