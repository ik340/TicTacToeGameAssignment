#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 3
#define MAX_SIZE 10

// Function prototypes
char *initBoard(int size);
void displayBoard(char *board, int size);
void getUserInput(int *row, int *col, int size, char player);
int isValidMove(int row, int col, int size, char *board);
int checkWin(char *board, int size, char symbol);
int checkDraw(char *board, int size);
void logMove(FILE *log, char *board, int size);

int main() {
        int size;
        printf("Enter the board size (%d <= N <= %d): ", MIN_SIZE, MAX_SIZE); // Ask the board size from the user
        scanf("%d", &size);

        if (size < MIN_SIZE || size > MAX_SIZE) { // Validation of the board size
           printf("Invalid size! \n");
           return 1;
        }

        char *board = initBoard(size);  // Memory allocation
        if (board == NULL) {
           printf("Memory allocation failed.\n");
           return 1;
        }

        FILE *logFile = fopen("game_log.txt", "w"); // Open file to log moves
        if (!logFile) {
           printf("Error opening log file.\n");
          free(board);
           return 1;
        }

        char players[2] = {'x', 'o'};
        int turn = 0;
        int row, col;
    // Main game loop      
    while (1) {
        displayBoard(board, size); // Show current board
            
          	
         getUserInput(&row, &col, size, players[turn]);
            if (!isValidMove(row, col, size, board)) {
                printf("Invalid move! Please try again.\n");
               continue;
            }
        } 

        board[row * size + col] = players[turn];
        logMove(logFile, board, size);

        if (checkWin(board, size, players[turn])) {
            displayBoard(board, size);
            printf("Player %c wins!\n", players[turn]);
            break;
        }
        if (checkDraw(board, size)) {
            displayBoard(board, size);
            printf("It's a draw!\n");
            break;
        }
        
            turn = 1 - turn;
        }
    

    fclose(logFile);
    free(board);
    return 0;
}
#include <stdio.h>
// ---------------------- FUNCTION DEFINITIONS ----------------------
char *initBoard(int size) {
    char *board = (char *)malloc(size * size * sizeof(char));
    if (board != NULL) {
        for (int i = 0; i < size * size; i++) {
            board[i] = ' ';
        }
    }
    return board;
}

// Display the board with row and column indices (matching PDF format)
void displayBoard(char *board, int size) {
    printf("\n    ");
    for (int j = 0; j < size; j++) {
        printf("  %d   ", j);
    }
    printf("\n");

    // Print top border
    printf("    ");
    for (int j = 0; j < size; j++) {
        printf("------");
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf(" %d |", i);
        for (int j = 0; j < size; j++) {
            printf("  %c  |", board[i * size + j]);
        }
        printf("\n");

        printf("    ");
        for (int j = 0; j < size; j++) {
            printf("------");
        }
        printf("\n");
    }
    printf("\n");
}

void getUserInput(int *row, int *col, int size, char player) {
    printf("Player %c, enter row and column (0-%d): ", player, size - 1);
    scanf("%d %d", row, col);
}

int isValidMove(int row, int col, int size, char *board) {
    if (row < 0 || col < 0 || row >= size || col >= size)
        return 0;
    if (board[row * size + col] != ' ')
        return 0;
    return 1;
}

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

int checkDraw(char *board, int size) {
    for (int i = 0; i < size * size; i++)
        if (board[i] == ' ')
            return 0;
    return 1;
}

// Log board state with same formatting as display
void logMove(FILE *log, char *board, int size) {
    fprintf(log, "\n    ");
    for (int j = 0; j < size; j++) {
        fprintf(log, "  %d   ", j);
    }
    fprintf(log, "\n");

    fprintf(log, "    ");
    for (int j = 0; j < size; j++) {
        fprintf(log, "------");
    }
    fprintf(log, "\n");

    for (int i = 0; i < size; i++) {
        fprintf(log, " %d |", i);
        for (int j = 0; j < size; j++) {
            fprintf(log, "  %c  |", board[i * size + j]);
        }
        fprintf(log, "\n");

        fprintf(log, "    ");
        for (int j = 0; j < size; j++) {
            fprintf(log, "------");
        }
        fprintf(log, "\n");
    }
    fflush(log);
}
