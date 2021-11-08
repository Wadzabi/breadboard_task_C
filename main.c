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

    if (!(BETWEEN(x1, board.columns-1, 0) && BETWEEN(x2, board.columns-1, 0) && BETWEEN(y, board.rows-1, 0))) {
        printf("\nOne or more of the points was not within the bounds of the breadboard.\nReturning to menu\n");
        return -1;
    }

    if(x1 == x2){
        printf("\nTried to place both resistor legs on same point. Not possible.");
        return -1;
    }
    if(bb_add_resistor(resistors, x1, x2, y) == -1){
        printf("\nResistor could not be added, place is occupied");
        return -1;
    }
    return 0;
    

}

void del_R_from_board(resistor_node **resistors){
    coordinate point;
    printf("Enter coordinates of resistor you want to remove.\nUse format (x, y): ");
    scanf("%d, %d", &point.x, &point.y);
    if(bb_remove_resistor(resistors, point)){
        printf("Resistor was removed!");
    }else{
        printf("No resistor could be removed at the selected point.");
    }
    return;
}


void check_connection(breadboard board, resistor_node *resistors){
    int start_col, end_col;
    printf("\nPoints in columns are connected, check for connection between two columns.\nEnter (first_column, second_colomun): ");
    scanf("%d, %d", &start_col, &end_col);
    if(bb_check_connection(resistors, board, start_col, end_col)){
        printf("\nThe columns are connected!");
    } else{
        printf("The columns are not connected.");
    }
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
    printf("A breadboard has been created. Row and column numbers start at 0. The point 0, 0 is the top left corner.\n");
    printf("Number of rows: %d\nNumber of columns: %d\n", board.rows, board.columns);
    resistor_node *resistors = NULL;
    int menu_option;
    
    while(true){
        printf("\n1. Print board\n2. Add resistor\n3. Remove resistor\n4. Check connection\n5. Exit\n");
        printf("Please choose an option: ");
        scanf("%d", &menu_option);

        switch(menu_option){
            case PRINT_BOARD:
                bb_print_board(resistors, board);
                break;
            case ADD_RES:
                add_R_to_board(board, &resistors);
                break;
            case REMOVE_RES:
                del_R_from_board(&resistors);
                break;
            case CHECK_CONNECTION:
                check_connection(board, resistors);
                break;
            case EXIT:
                printf("\nExiting program");
                bb_free_list(resistors);
                return 0;
            default:
                printf("\nAn Incorrect menu option was selected.");
        }
    }


    return 0;
}
