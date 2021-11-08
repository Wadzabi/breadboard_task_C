#include "breadboard.h"
#include <stdio.h>
#include <stdlib.h>

#define BETWEEN(value, max, min) (value <= max && value >= min)


enum menu_options{PRINT_BOARD = 1, ADD_RES, REMOVE_RES, CHECK_CONNECTION, EXIT};

int add_R_to_board(breadboard board, resistor_node **resistors){
    int x1, x2, y;
    printf("\nEnter x and y coordinates of the point where you want to place a resistor.\nUse x, y format): ");
    scanf("%d, %d", &x1, &y);
    printf("\nEnter second x coordinate for resistor: ");
    scanf("%d", &x2);

    printf("test print x1 = %d   x2 = %d   y = %d", x1, x2, y);
    printf("rows and column values, %d and %d", board.rows, board.columns);

    if (!(BETWEEN(x1, board.columns-1, 0) && BETWEEN(x2, board.columns-1, 0) && BETWEEN(y, board.rows-1, 0))) {
        printf("\nOne or more of the points was not within the bounds of the breadboard.\nReturning to menu\n");
        return -1;
    }

    if(x1 == x2){
        printf("\nTried to place both resistor legs on same point. Not possible.");
        return -1;
    }
    if(add_resistor(resistors, x1, x2, y) == -1){
        printf("\nResistor could not be added, place is occupied");
        return -1;
    }
    return 0;
    

}

void del_R_from_board(resistor_node **resistors){
    coordinate point;
    printf("Enter coordinates of resistor you want to remove.\nUse format (x, y): ");
    scanf("%d, %d", &point.x, &point.y);
    remove_resistor(resistors, point);
    return;
}


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
        printf("\n1. Print board\n2. Add resistor\n3. Remove resistor\n4. Check connection\n5. Exit\n");
        printf("Please choose an option: ");
        scanf("%d", &menu_option);

        switch(menu_option){
            case PRINT_BOARD:
                printf("board will be printed\n");
                print_board(resistors, board);
                break;
            case ADD_RES:
                printf("\nresistor will be added");
                add_R_to_board(board, &resistors);
                break;
            case REMOVE_RES:
                printf("\nresistor will be removed");
                del_R_from_board(&resistors);
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
