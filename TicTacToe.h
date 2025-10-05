#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>

#define MIN_SIZE 3
#define MAX_SIZE 10

// Function prototypes for the board
char *initBoard(int size);
void displayBoard(char *board, int size);
void getUserInput(int *row, int *col, int size, char player);
void getComputerMove(int *row, int *col, int size, char *board);
int isValidMove(int row, int col, int size, char *board);
int checkWin(char *board, int size, char symbol);
int checkDraw(char *board, int size);
void logMove(FILE *log, char *board, int size, int row, int col, char symbol);

// Function prototypes for to select the game mode
void twoPlayers(int size);  // User vs User
void userVsComputer(int size);  // user vs computer
void threePlayers(int size);   // three players

#endif


