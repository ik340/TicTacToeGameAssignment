#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TicTacToe.h"

// Main function to start the game
int main() {
        int size, choice;
        printf("Enter the board size N (3 <= N <= 10): "); // Ask the board size from the user 
        scanf("%d", &size);

        if (size < MIN_SIZE || size > MAX_SIZE) { // Validation of the board size
           printf("Invalid size! \n");
           return 1;
        }

        printf("\nSelect Game mode:\n");     // Ask from the user to select the game mode
        printf("1. Two Players (User vs User)\n");
        printf("2. User vs Computer\n");
        printf("3. Three Players\n");
        printf("Enter choice (1-3): ");
        scanf("%d", &choice);

        switch(choice) {        // Calling for the selected game mode
        case 1:
            twoPlayers(size);
            break;
        case 2:
            userVsComputer(size);
            break;
        case 3:
            threePlayers(size);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
    return 0;
}

char *initBoard(int size) {     // Initializing the board
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


void getUserInput(int *row, int *col, int size, char player) {  // Get the row and coloumn from the user
    printf("Player %c, enter row and column (0-%d): ", player, size - 1);
    scanf("%d %d", row, col);
}


void getComputerMove(int *row, int *col, int size, char *board) {   // Generate computer moves
    do {
        *row = rand() % size;
        *col = rand() % size;
    } while (!isValidMove(*row, *col, size, board));
}
int isValidMove(int row, int col, int size, char *board) {   // Validation of the move
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

int checkDraw(char *board, int size) {   // Check whether the board is a draw
    for (int i = 0; i < size * size; i++)
        if (board[i] == ' ')
            return 0;
    return 1;
}

void logMove(FILE *log, char *board, int size, int row, int col, char symbol) {  //  Write the  move to a log  file
    fprintf(log, "Player %c: (%d, %d)\n", symbol, row, col);
}


// Game modes
// First mode  - Two players (User vs user)
void twoPlayers(int size) {
        char *board = initBoard(size);  // Memory allocation
        if (board == NULL) {
          printf("Memory allocation failed.\n");
           return;
        }

        FILE *logFile = fopen("game_log.txt", "w"); // Open file to log moves
        if (!logFile) {
           printf("Error opening log file.\n");
           free(board);
           return;
        }

        char players[2] = {'X', 'O'};
        int turn = 0;
        int row, col;

    while (1) {
        displayBoard(board, size);  // Show current board
    getUserInput(&row, &col, size, players[turn]); // Get the row and coloumn from the user to check the validation of the move
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
}


// Second mode - User vs Computer
void userVsComputer(int size) {
        char *board = initBoard(size);  // Memory allocation
        if (board == NULL) {
           printf("Memory allocation failed.\n");
           return;
        }

        FILE *logFile = fopen("game_log.txt", "w"); // Open file to log moves
        if (!logFile) {
           printf("Error opening log file.\n");
           free(board);
           return;
        }

        char user = 'X';
        char computer = 'O';
        int row, col;
        int userTurn = 1;       // Always starts by the user
        srand(time(NULL));      // SEt up random seed to computer moves

        while(1) {
                displayBoard(board, size);
                if (userTurn) {
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
                        getComputerMove(&row, &col, size, board); // Computer moves
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
   }


// Third mode - Three Players
void threePlayers(int size) {
    char *board = initBoard(size);    // Memory allocation
    if (board == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
   FILE *logFile = fopen("game_log.txt", "w");  // Open file to log moves
    if (!logFile) {
        printf("Error opening log file.\n");
        free(board);
        return;
    }

    char players[3] = {'X', 'O', 'Z'};   // Symbols of players
    int isComputer[3] = {0, 0, 0};       // 0 - human user, 1 = computer
    srand(time(NULL));

    printf("Player selection - At least one player must be human.\n");  // Selection of players(At least one player must be human)
    for (int i = 0; i < 3; i++) {
        char choice;
        printf("Is Player %c a Human user or Computer? (Enter h or c): ", players[i]);
        scanf(" %c", &choice);
        if (choice == 'c' || choice == 'C')
            isComputer[i] = 1;
        else
            isComputer[i] = 0;
    }

    if (isComputer[0] && isComputer[1] && isComputer[2]) {     // Checking that at least one player is human
        printf("All players were set as computer. Player X is now set as Human.\n");
        isComputer[0] = 0;
    }
   int turn = 0;  // Begins with Player X
    int row, col;
   while (1) {
        displayBoard(board, size);
        printf("Turn: Player %c (%s)\n", players[turn], isComputer[turn] ? "Computer" : "Human");

        if (isComputer[turn]) {
            getComputerMove(&row, &col, size, board);  // Move of computer
            board[row * size + col] = players[turn];
            printf("Computer (%c) played at (%d, %d)\n", players[turn], row, col);
            logMove(logFile, board, size, row, col, players[turn]);
        } else {
            getUserInput(&row, &col, size, players[turn]); // Move of human
            if (!isValidMove(row, col, size, board)) {
                printf("Invalid move! Please try again.\n");
                continue;
            }
            board[row * size + col] = players[turn];    // Updating the board and log move
            logMove(logFile, board, size, row, col, players[turn]);
        }
        

        if (checkWin(board, size, players[turn])) {    // Checking for win
            displayBoard(board, size);
            printf("Player %c (%s) WINS!\n", players[turn], isComputer[turn] ? "Computer" : "Human");
            break;
        }

        if (checkDraw(board, size)) {    // Checking for draw
            displayBoard(board, size);
            printf("Game is a draw!\n");
            break;
        }
       turn = (turn + 1) % 3;   // to get the turns in cyclic order
    }

    fclose(logFile);
    free(board);
}
