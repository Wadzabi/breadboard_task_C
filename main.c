#include "breadboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum menu_options{PRINT_BOARD = 1, ADD_RES, REMOVE_RES, CHECK_CONNECTION, EXIT};

int main(int argc, char const *argv[])
{
    if (argc != 3){
        printf("Expected 2 arguments, number of columns and rows. Got %d arguments.", argc-1);
        return -1;
    }

    breadboard board;
    board.rows = atoi(argv[1]);
    board.columns = atoi(argv[2]);

    if(board.rows <=1 || board.columns <= 1){
        printf("Row or column value incorrect. Number of rows and colums has to be a number which is 2 or higher.");
        return -1;
    }

    resistor_node *resistors = NULL;
    int menu_option;
    
    while(true){
        printf("1. Print board\n2. Add resistor\n3. Remove resistor\n4. Check connection\n5. Exit\n");
        printf("Please choose an option: ");
        scanf("%d", &menu_option);

        switch(menu_option){
            case PRINT_BOARD:
                printf("board will be printed");
                break;
            case ADD_RES:
                printf("resistor will be added");
                break;
            case REMOVE_RES:
                printf("resistor will be removed");
                break;
            case CHECK_CONNECTION:
                printf("connection will be checked");
                break;
            case EXIT:
                printf("exiting program");
                return 0;
            default:
                printf("An Incorrect menu option was selected.");
        }
    }


    return 0;
}
