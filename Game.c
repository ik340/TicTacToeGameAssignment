#include <stdio.h>
#include <stdlib.h>

// Initialize the game board with empty spaces
void setup_board(char **board, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board[i][j] = '-';  // Using dash for empty spots
        }
    }
}

void show_board(char **board, int size) {
    printf("\n   Current Board:\n");
    for (int i = 0; i < size; i++) {
        printf("   ");
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");  // Add separators because it looks nicer
        }
        printf("\n");
        if (i < size - 1) {
            printf("   ");
            for (int k = 0; k < size * 4 - 1; k++) printf("-");
            printf("\n");
        }
    }
    printf("\n");
}

// Check if the move is legal
int is_move_valid(char **board, int row, int col, int board_size) {
    // Make sure we're within bounds and the spot is empty
    if (row >= 0 && row < board_size && col >= 0 && col < board_size) {
        if (board[row][col] == '-') {
            return 1;  // Valid move
        }
    }
    return 0;  // Invalid
}


