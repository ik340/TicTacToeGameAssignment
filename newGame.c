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
void logMove(FILE *log, char *board, int size, int row, int col, char symbol);

int main() {
	int size;
        printf("Enter the board size N (3 <= N <= 10): ", MIN_SIZE, MAX_SIZE); // Ask the board size from the user
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
        displayBoard(board, size);  // Show current board
        
        	
         
         getUserInput(&row, &col, size, players[turn]); // Get the row and colomn from the user to check the validation of the move
            if (!isValidMove(row, col, size, board)) {
                printf("Invalid move! Please try again.\n");
		continue;
	    }	
          

        board[row * size + col] = players[turn];  // Update the board and log move
        logMove(logFile, board, size, row, col, players[turn]);

        if (checkWin(board, size, players[turn])) {   // Checking for win
            displayBoard(board, size);
            printf("Player %c wins!\n", players[turn]);
            break;
        }
        if (checkDraw(board, size)) { // Checking for draw
            displayBoard(board, size);
            printf("Game is a draw!\n");
            break;
        }
      
            turn = 1 - turn; // Switch the turn
    }
    

    fclose(logFile);
    free(board);
    return 0;
}

char *initBoard(int size) {
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

void getUserInput(int *row, int *col, int size, char player) {  // Get the row and colomn from the user
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

int checkWin(char *board, int size, char symbol) {   // Check if the player has won
    int win;						    
    for (int i = 0; i < size; i++) {   // Check for the rows
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


    win = 1;  // Check for the main diagonal
    for (int i = 0; i < size; i++) 
        if (board[i * size + i] != symbol) win = 0;
    if (win) return 1;


    win = 1;  // Check for the anti-diagonal
    for (int i = 0; i < size; i++)	      
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

void logMove(FILE *log, char *board, int size, int row, int col, char symbol) {  //   Write the  move to file
    fprintf(log, "Player %c: (%d, %d)\n", symbol, row, col);
}
