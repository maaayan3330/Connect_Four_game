#include "ex_4.h"
#include <string.h>

int countMoves(char board[ROWS][COLS],int rows, int columns);
int tooManyChar(char board[ROWS][COLS],int rows, int columns,int players);
int firstLine(char board[ROWS][COLS],int rows, int columns);
int isRow(char board[ROWS][COLS], int rows, int columns,int connect);
int isColumns(char board[ROWS][COLS], int rows, int columns,int connect);
int isSlantRight(char board[ROWS][COLS], int rows, int columns,int connect);
int isSlantLeft(char board[ROWS][COLS], int rows, int columns,int connect);
char winRow(char board[ROWS][COLS], int rows, int columns,int connect);
char winColumns(char board[ROWS][COLS], int rows, int columns,int connect);
char winSlantRight(char board[ROWS][COLS], int rows, int columns,int connect);
char winSlantLeft(char board[ROWS][COLS], int rows, int columns,int connect);
char findWinner(char board[ROWS][COLS], int rows, int columns,int connect);
int numWinRow(char board[ROWS][COLS], int rows, int columns,int connect);
int numWinColumns(char board[ROWS][COLS], int rows, int columns,int connect);
int numWinSlantRight(char board[ROWS][COLS], int rows, int columns,int connect);
int numWinSlantLeft(char board[ROWS][COLS], int rows, int columns,int connect);
int flyChar(char board[ROWS][COLS], int rows, int columns);
int checkChar(char board[ROWS][COLS], int rows, int columns,int players);

/**
 * The function initBoard is for initialize the board.
 * The function The function is an array of arrays that goes row by row using the columns and initializes to ' '.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The number of columns.
 */
void initBoard(char board[ROWS][COLS], int rows, int columns) {
    //Run all over the array
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //Initialize the array to ' '
            board[i][j] = ' ';
        }
    }
}

/**
 * This function is for print the board of the game.
 * The function print line of ~ in the first & last line & in the middle '| ' as the num of the rows & columns.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The number of columns.
 */
void printBoard(char board[ROWS][COLS], int rows, int columns) {
    //This will print the first line that made of ~
    for (int i = 0 ; i < 2 * columns + 1 ; ++i) {
        printf("~");
    }
    printf("\n");
    //This will print the middle
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            printf("|%c",board[i][j]);
        }
        //For end of every line
        printf("|");
        printf("\n");
    }
    //This will print the last line that made of ~
    for (int i = 0 ; i < 2 * columns + 1 ; ++i) {
        printf("~");
    }
    printf("\n");
}

/**
 * The function Update the board to be the resulting board after the given player has selected the given column.
 * The function check if the player choose an invalid num , and will put it in the board if it is legal.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The number of columns.
 * @param players The number of players.
 * @param player The char of a specific player.
 * @param column The num of the column the player choose.
 *
 * @return 1 if the act is possible & 0 if the act is not possible.
 */
int makeMove(char board[ROWS][COLS], int rows, int columns, int players, char player, int column) {
    //Check if the player choose an invalid num
    if ( column >= columns || column < 0) {
        return 0;
    }
    //Check if the player name is a valid uppercase letter
    if (player < 'A' || player > ('A' + players - 1)) {
        return 0;
    }
    //Check in which row the player choose his move and if it is possible
    for ( rows = rows ; rows > 0 ; --rows) {
        //Go through all the rows in the specific column from bottom to top to find out the position of the move
        if ( board[rows][column] != ' ' ) {
            continue;
        } else {
            //Keep the move in an array
            board[rows][column] = player;
            //Return 1 the move is valid
            return 1;
        }
    }
    //If he got till here it's mean the column is all taken & the move is un valid
    return 0;
}

/**
 * The function will update the board to be the board after canceling an operation in the same column.
 * Checks by going over the entire column what was the last move if it exists and cancels it.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The number of columns.
 * @param column The num of the column the player choose.
 *
 * @return 1 if the act is possible & 0 if the act is not possible.
 */
int undoMove(char board[ROWS][COLS], int rows, int columns, int column) {
    //Check if the selected column is valid
    if ( column < 0 || column >= columns) {
        return 0;
    }
    //Check if there was any move in this column
    for ( rows = 0 ; rows < ROWS ; ++rows) {
        if ( board[rows][column] == ' ') {
            continue;
        } else {
            //Check what was the last move and cancel it
            board[rows][column] = ' ';
            return 1;
        }
    }
    //If he got till here it's mean the entire column is free and there is no move to cancel
    return 0;
}

/**
 * The function check if there is a win in row/column/slant or a draw or the game still one.
 * There are 3 functions that check different win than check if the board is full for a tie & finally if game continue.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The number of columns.
 * @param players The number of players.
 * @param connect The streak for a win.
 *
 * @return 1 For a win , 0 for a tie , -1 for the gams still one.
 */
int getStatus(char board[ROWS][COLS], int rows, int columns,__attribute__((__unused__))int players, int connect) {
    //Call the function to check a win in a row
    if (isRow(board, rows, columns, connect) == 1) {
        //Exit getStatus if there is a win in a row
        return 1;
    }
    //Call the function to check a win in a column
    if (isColumns(board, rows, columns, connect) == 1) {
        //Exit getStatus if there is a win in a column
        return 1;
    }
    //Call the function to check a win in a slant right
    if (isSlantRight(board, rows, columns, connect) == 1) {
        //Exit getStatus if there is a win in a slant right
        return 1;
    }
    //Call the function to check a win in a slant left
    if (isSlantLeft(board, rows, columns, connect) == 1) {
        // Exit getStatus if there is a win in a slant left
        return 1;
    }
    //If the code got till here there is no a win so will check tie/the game still one
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //Check if there is move in the array
            if ( board[i][j] != ' ') {
                continue;
            } else {
                //The board isn't full,there are more invalid moves to do
                return -1;
            }
        }
    }
    return 0;
}

/**
 * This function check if there is a winner & who is he.
 * The function call 2 function, first one for check if there is a win and the second one is to know who is the winner.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The number of columns.
 * @param players The number of players.
 * @param connect The streak for a win.
 *
 * @return The char of the winner or -1 for no win.
 */
char getWinner(char board[ROWS][COLS], int rows, int columns, int players, int connect) {
    int result;
    char winner;
    //Get if there is a win or not
    result = getStatus(board,rows,columns,players,connect);
    if ( result == 1 ) {
        //Check who is the winner
        winner = findWinner(board,rows,columns,connect);
        return winner;
    } else {
        //If the game still ongoing or a tie so no win
        return -1;
    }
}

/**
 * The function will receive a board and decide whether it may be a valid board received at the beginning,middle or end.
 * She goes through all possible bad cases and checks if they occur , with the help of more functions.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The number of columns.
 * @param players The number of players.
 * @param connect The streak for a win.
 *
 * @return 1 If the board is valid and 0 if not.
 */
int isValidBoard(char board[ROWS][COLS], int rows, int columns, int players, int connect) {
    int flag = 1;
    //Check first un valid option for board - more than 1 victory
    if ( (numWinRow(board,rows,columns,connect) + numWinColumns(board,rows,columns,connect) +
          numWinSlantLeft(board,rows,columns,connect) + numWinSlantRight(board,rows,columns,connect)) > 1) {
        return 0;
        //Check if there is un valid char - meaning a player
    } else if ( checkChar(board,rows,columns,players) == 0 ) {
        return 0;
        //Check if there is a "flying" char
    } else if ( flyChar(board,rows,columns) == 0 ) {
        return 0;
        //Check if there is a all line without A
    } else if(firstLine(board,rows,columns) == 0) {
        return 0;
        //Check if there are to many chars from on player
    } else if ( flag == 1 ) {
        int sumMove = tooManyChar(board,rows,columns,players);
        for (int i = 1 ; i < players ; ++i) {
            if ( sumMove == tooManyChar(board,rows,columns,i) || sumMove + 1 == tooManyChar(board,rows,columns,i)) {
                continue;
            } else {
                return 0;
            }
        }
    } else {
        return 1;
    }
}

/**
 * The function is check if she got a board that have un valid char.
 * The function run all over the matrix and compare every char to all the valid options.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param players The num of players.
 *
 * @return 1 If all the chars are valid , or 0 for un valid player.
 */
int checkChar(char board[ROWS][COLS], int rows, int columns,int players) {
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            if ( board[i][j] != ' ') {
                if (board[i][j] > 'A' + players - 1 || board[i][j] < 'A')
                    return 0;
            }
        }
    }
    return 1;
}

/**
 * The function check is there is a "flying" char.
 * She run all over the array and check when she find a char if there isn't char below it Unless it's the first line.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 *
 * @return 1 If there isn't a "flying" char , & 0 if there is.
 */
int flyChar(char board[ROWS][COLS], int rows, int columns) {
    //Run all over the matrix
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            if (board[i][j] != ' ') {
                if ((i != rows - 1) && (board[i + 1][j] == ' ')) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

/**
 * The function will check if there is a win in a row
 * The function goes through each line with the help of arrays and checks if there is a winning streak.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return 1 If there is a win , 0 if there is not.
 */
int isRow(char board[ROWS][COLS], int rows, int columns,int connect) {
    //Run all over the array for a win in a row
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    return 1;
                }
                //For a case there no possibility to have connect in a row
                if ( j + connect - 1 > columns){
                    //Get out to the next row
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i][j+k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp ++;
                }
                if ( temp == connect) {
                    return 1;
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return 0;
}

/**
 *  The function will check if there is a win in a column.
 * The function goes through each column with the help of arrays and checks if there is a winning streak.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return 1 If there is a win , 0 if there is not.
 */
int isColumns(char board[ROWS][COLS], int rows, int columns,int connect) {
    //Run all over the array for a win in a row
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    return 1;
                }
                //For a case there no possibility to have connect in a row
                if ( i + connect - 1 > rows){
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    return 1;
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return 0;
}

/**
 * The function will check if there is a win in a right slant.
 * The function goes through each right slant with the help of arrays and checks if there is a winning streak.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return 1 If there is a win , 0 if there is not.
 */
int isSlantRight(char board[ROWS][COLS], int rows, int columns,int connect) {
    //Run all over the array for a win in a slant
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    return 1;
                }
                //For a case there no possibility to have connect in a slant
                if ( i + connect - 1 > rows) {
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j + k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp ++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    return 1;
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return 0;
}

/**
 * The function will check if there is a win in a left slant.
 * The function goes through each left slant with the help of arrays and checks if there is a winning streak.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return 1 If there is a win , 0 if there is not.
 */
int isSlantLeft(char board[ROWS][COLS], int rows, int columns,int connect) {
    //Run all over the array for a win in a slant
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    return 1;
                }
                //For a case there no possibility to have connect in a slant
                if ( i + connect - 1 > rows) {
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j - k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp ++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    return 1;
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return 0;
}

/**
 * The function check who is the winner from the all players.
 * Goes through row/column/diagonal functions and checks where the victory is and according to that says whose won.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The char of the winner.
 */
char findWinner(char board[ROWS][COLS], int rows, int columns,int connect) {
    //If we get to here there is a winner , row first
    if ( winRow(board,rows,columns,connect) != 0) {
        return winRow(board,rows,columns,connect);
        //Check winner in columns
    } else if ( winColumns(board,rows,columns,connect) != 0) {
        return winColumns(board,rows,columns,connect);
        //Check winner in slant right
    } else if ( winSlantRight(board,rows,columns,connect) != 0) {
        return winSlantRight(board,rows,columns,connect);
        //Else the winner in slant right
    } else {
        return winSlantLeft(board,rows,columns,connect);
    }
}

/**
 * This function will find the char of the player that won.
 * The function goes through each row with the help of arrays and checks what is the char of the winner.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The char of the winner.
 */
char winRow(char board[ROWS][COLS], int rows, int columns,int connect) {
    //Run all over the array for a win in a row
    for (int i = 0 ; i < columns ; ++i) {
        for (int j = 0 ; j < rows ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    return board[i][j];
                }
                //For a case there no possibility to have connect in a row
                if ( j + connect - 1 > columns){
                    //Get out to the next row
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i][j+k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    return board[i][j];
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return 0;
}

/**
 * This function will find the char of the player that won.
 * The function goes through each column with the help of arrays and checks what is the char of the winner.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The char of the winner.
 */
char winColumns(char board[ROWS][COLS], int rows, int columns,int connect) {
    //Run all over the array for a win in a row
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    return board[i][j];
                }
                //For a case there no possibility to have connect in a row
                if ( i + connect - 1 > rows){
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    return board[i][j];
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return 0;
}

/**
 * This function will find the char of the player that won.
 * The function goes through each slant right with the help of arrays and checks what is the char of the winner.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The char of the winner.
 */
char winSlantRight(char board[ROWS][COLS], int rows, int columns,int connect) {
    //Run all over the array for a win in a slant
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    return board[i][j];
                }
                //For a case there no possibility to have connect in a slant
                if ( i + connect - 1 > rows) {
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j + k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    return board[i][j];
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return 0;
}

/**
 * This function will find the char of the player that won.
 * The function goes through each slant left with the help of arrays and checks what is the char of the winner.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The char of the winner.
 */
char winSlantLeft(char board[ROWS][COLS], int rows, int columns,int connect) {
    //Run all over the array for a win in a slant
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    return board[i][j];
                }
                //For a case there no possibility to have connect in a slant
                if ( i + connect - 1 > rows) {
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j - k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    return board[i][j];
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return 0;
}

/**
 * This function will find the num of victories.
 * The function goes through each row with the help of arrays and count all the victories.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The num of victories.
 */
int numWinRow(char board[ROWS][COLS], int rows, int columns,int connect) {
    int victories = 0;
    //Run all over the array for a win in a row
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    //counting how much victories
                    victories ++;
                    continue;
                }
                //For a case there no possibility to have connect in a row
                if ( j + connect - 1 > columns){
                    //Get out to the next row
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i][j+k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    victories++;
                    continue;
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return victories;
}

/**
 * This function will find the num of victories.
 * The function goes through each column with the help of arrays and count all the victories.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The num of victories.
 */
int numWinColumns(char board[ROWS][COLS], int rows, int columns,int connect) {
    int victories = 0;
    //Run all over the array for a win in a row
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    break;
                }
                //For a case there no possibility to have connect in a row
                if ( i + connect - 1 > rows){
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    victories++;
                    continue;
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return victories;
}

/**
 * This function will find the num of victories.
 * The function goes through each slant right with the help of arrays and count all the victories.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The num of victories.
 */
int numWinSlantRight(char board[ROWS][COLS], int rows, int columns,int connect) {
    int victories = 0;
    //Run all over the array for a win in a slant
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    break;
                }
                //For a case there no possibility to have connect in a slant
                if ( i + connect - 1 > rows) {
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j + k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    victories++;
                    continue;
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return victories;
}

/**
 * This function will find the num of victories.
 * The function goes through each slant left with the help of arrays and count all the victories.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 * @param connect The streak for a win.
 *
 * @return The num of victories.
 */
int numWinSlantLeft(char board[ROWS][COLS], int rows, int columns,int connect) {
    int victories = 0;
    //Run all over the array for a win in a slant
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            //If there is no char in the square move to the next square
            if (board[i][j] != ' ') {
                //In a case every single char is a win
                if ( connect == 1 ) {
                    break;
                }
                //For a case there no possibility to have connect in a slant
                if ( i + connect - 1 > rows) {
                    //Get out to the next columns
                    break;
                }
                int temp = 1;
                for (int k = 1 ; k < connect ; ++k) {
                    if ( board[i][j] != board[i + k][j - k]) {
                        //The next move is a different player so move on
                        break;
                    }
                    temp++;
                }
                if ( temp == connect ) {
                    //If it run over till now it's a win
                    victories++;
                    continue;
                }
            } else {
                //There is no move in this square to check
                continue;
            }
        }
    }
    //If it get till here there is no win
    return victories;
}

/**
 * @brief Converts an integer to the corresponding Base64 character.
 * She takes an integer as input and converts it to the corresponding Base64 character based on the specified ranges.
 *
 * @param num The input integer to be converted.
 *
 * @return The Base64 character corresponding to the input integer.
 */
char numToBase64(int num) {
    //Set the value of abc as 26
    int abc = 26;
    // Check if num falls within the range [0, 26)
    if (0 <= num && num < abc) {
        return num + 'A';
    }
    //Check if num falls within the range [26, 52)
    if (abc <= num && num < 2 * abc) {
        return num - abc + 'a';
    }
    //Check if num falls within the range [52, 62)
    if (2 * abc <= num && num < 2 * abc + 10) {
        return num - 2 * abc + '0';
    }
    //Check if num is equal to 62
    if (num == 62)
        return '+';
    //Check if num is equal to 63
    if (num == 63)
        return '/';
    //If none of the above conditions match, return a space character
    return ' ';
}

/**
 * @brief Encodes a 2D character board into a code string using a specific encoding scheme.
 * This function takes a 2D character board and encodes it into a code string using a specific encoding scheme.
 *
 * @param board The 2D character board to be encoded.
 * @param rows The number of rows in the board.
 * @param cols The number of columns in the board.
 * @param code The resulting code string where the encoded board will be stored.
 */
void encode(const char board[ROWS][COLS], int rows, int cols, char *code) {
    int k = 0;
    int counter;
    //Run all over thr array
    for (int i = 0; i < rows; i++) {
        counter = 1;
        for (int j = 1; j < cols; j++) {
            //Check if the chars are the same
            if (board[i][j - 1] == board[i][j]) {
                counter++;
            } else {
                //Store the Base64 representation of the counter
                char c = numToBase64(counter);
                code[k] = c;
                code[k + 1] = board[i][j - 1];
                k += 2;
                counter = 1;
            }
        }
        //Store the Base64 representation of the counter
        code[k] = numToBase64(counter);
        code[k + 1] = board[i][cols - 1];
        //Add a delimiter character between rows
        code[k + 2] = '/';
        k += 3;
    }
    //Null-terminate the code string
    code[k] = '\0';
}

/**
 * @brief Converts a Base64 character to the corresponding integer value.
 * She takes a Base64 character and converts it to the corresponding integer value based on the specified ranges.
 *
 * @param c The Base64 character to be converted.
 *
 * @return The integer value corresponding to the Base64 character,or -1 if the char is not a valid Base64 character.
 */
int base64ToNum(char c) {
    int abc = 26;
    //Check if c is an uppercase letter
    if ('A' <= c && c <= 'Z') {
        //Convert c to the corresponding integer value
        return c - 'A';
    }
    //Check if c is a lowercase letter
    if ('a' <= c && c <= 'z') {
        //Convert c to the corresponding integer value
        return c - 'a' + abc;
    }
    //Check if c is a digit
    if ('0' <= c && c <= '9') {
        //Convert c to the corresponding integer value
        return c - '9' + 2 * abc;
    }
    //Check if c is the Base64 character '+'
    if (c == '+')
        return 62;
    //Check if c is the Base64 character '/'
    if (c == '/')
        return 63;
    //If none of the above conditions match, return -1 to indicate an invalid Base64 character
    return -1;
}

/**
 * @brief Decodes a code string into a 2D character board using a specific decoding scheme.
 *
 * This function takes a code string and decodes it into a 2D character board using a specific decoding scheme.
 *
 * @param code The code string to be decoded.
 * @param board The resulting 2D character board where the decoded values will be stored.
 */
void decode(const char *code, char board[ROWS][COLS]) {
    int row = 0;
    int col = 0;
    for ( unsigned long i = 0 ; i < strlen(code) ; i++) {
        if (code[i] == '/') {
            //Move to the next row
            row += 1;
            col = 0;
            continue;
        }
        //Convert the Base64 character to a count value
        int count = base64ToNum(code[i]);
        //Get the character for the current count
        char c = code[i + 1];
        //Skip the next character since it has been processed
        i += 1;

        for (int j = 0; j < count; j++) {
            //Populate the board with the character 'c' for 'count' times
            board[row][col + j] = c;
        }
        //Move the column index forward by 'count'
        col += count;
    }
}

/**
 * The function check un valid option for a board.
 * She run all over the first line and check if there is no A at all and it's illegal because the order is alphabetical.
 *
 * @param board The of size of the matrix (board).
 * @param rows The number of rows.
 * @param columns The num of the column the player choose.
 *
 * @return 1 If there is A and 0 if there is no A al all.
 */
int firstLine(char board[ROWS][COLS],int rows, int columns) {
    //Run all over the first line.
    for (int i = 0 ; i < columns ; ++i) {
        if ( board[rows-1][i] != 'A') {
            //if there is no A keep check the next move
            continue;
        } else {
            //There is an A
            return 1;
        }
    }
    return 0;
}

int tooManyChar(char board[ROWS][COLS],int rows, int columns,int players){
    int counter = 0 ;
//    //Conditions for exiting the loop
//    if (players == 0) {
//        return 1;
//    }
    //Run all over the array and check how many are there of each char
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            if ( board[i][j] == 'A' + players - 1 ) {
                //Count them
                counter++;
            } else {
                //If it is not the same char keep going
                continue;
            }
        }
    }
    //Call countMove function if the char have normal amount of characters in relation to players
//    if (countMoves(board,rows,columns,players) == counter || countMoves(board,rows,columns,players) == counter + 1) {
//        counter = 0;
//        return tooManyChar(board,rows,columns,players-1);
//    } else {
//        return 0;
//    }
    return counter;
}

int countMoves(char board[ROWS][COLS],int rows, int columns) {

    int counter = 0;
    for (int i = 0 ; i < rows ; ++i) {
        for (int j = 0 ; j < columns ; ++j) {
            if ( board[i][j] != ' ') {
                counter++;
            } else {
                continue;
            }
        }
    }
    return counter/players;
}
