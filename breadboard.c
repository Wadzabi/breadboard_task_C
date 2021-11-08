#include <stdlib.h>
#include <stdio.h>
#include "breadboard.h"

/*
Function: bb_add_resistor.
Adds new resistor_node to doubly linked list using sorted insertion.
Sorted by placement in breadboard going from left to right, top to bottom.
*/
int bb_add_resistor(resistor_node **head, int c1, int c2, int r1){
    int temp;
    if(c1>c2){
        temp = c2;
        c2 = c1;
        c1 = temp;
    }
    
    coordinate point = {c1, r1};

    for(;point.x<=c2; point.x++){                           
        if(bb_is_occupied((*head), point)) return -1;   //Checks if resistor can be added to slot.
    }
    resistor_node *new_node = (resistor_node*)malloc(sizeof(resistor_node));
    new_node->col1 = c1;
    new_node->col2 = c2;
    new_node->row = r1;

    if ((*head) == NULL){
        new_node->next = NULL;
        new_node->previous = NULL;
        (*head) = new_node;
        
        return 0;
    }

    if (new_node->row < (*head)->row || (new_node->col1 < (*head)->col1 && new_node->row == (*head)->row)){
        new_node->next = (*head);
        new_node->previous = NULL;
        (*head)->previous = new_node;
        (*head) = new_node;
        return 0;

    }
    resistor_node *current = (*head);
    while (current->next != NULL){
        if (new_node->row < current->next->row || (new_node->col1 < current->next->col1 && new_node->row == current->next->row)) break;
        current = current->next;   
    }
    new_node->next = current->next;
    new_node->previous = current;
    if(current->next != NULL) current->next->previous = new_node;
    current->next = new_node;
    return 0;

 


}

bool bb_is_occupied(resistor_node *head, coordinate point){
    resistor_node *current = head;
    while (current != NULL){
        if (point.x >= current->col1 && point.x <= current->col2 && point.y == current->row ) return true;
        current = current->next;
    }
    return false;
}

/*
Function: bb_remove_resistor
Removes resistor if it's covering designated coordinate.
*/

bool bb_remove_resistor(resistor_node **head, coordinate point){
    if (*head == NULL) return false;
    resistor_node *current = *head;
    if (point.y == current->row && (point.x >= current->col1 && point.x <= current->col2)){
        *head = (*head)->next;
        if (*head != NULL) (*head)->previous = NULL;
        free(current);
        return true;
    }
    
    
    while (current != NULL){
        if (point.y == current->row && (point.x >= current->col1 && point.x <= current->col2)){
            if (current->next !=NULL) current->next->previous = current->previous;
            current->previous->next = current->next;
            free(current);
            return true;
        }
        current = current->next;
    }
    return false;
}

/*
Function: bb_print_board
Prints character for every slot in breadboard. 
If resistor is encountered it prints the resistor and jumps to resistors end point.
*/

void bb_print_board(resistor_node* head, breadboard board){
    resistor_node *current = head;
    for(int i = 0; i<board.rows; i++){
        for(int j = 0; j<board.columns; j++){
            if (current != NULL && i == current->row && j == current->col1){
                print_resistor(current);
                j = current->col2;
                current = current->next;
            } else printf(" | ");


        }
        printf("\n");

    }
}

void print_resistor(resistor_node *node){
    printf(" <-");
    for(int i = 0; i<(node->col2 - node->col1)-1; i++){
        printf("---");
    }
    printf("-> ");
}

/*
Function: add_connections
Looks for all resistors connected to selected column.
If a resistor is found the other connected column is changed to uncheked if not already found. 
*/
bool add_connections(int *connected_cols, int col_index, resistor_node *head){
    bool col_found = false;
    resistor_node *current = head;
    while(current != NULL ){
        if (current->col1 == col_index && connected_cols[current->col2] == UNCONNECTED){
            connected_cols[current->col2] = UNCHECKED;
            col_found = true;
        }
        else if (current->col2 == col_index && connected_cols[current->col1] == UNCONNECTED) {
            connected_cols[current->col1] = UNCHECKED;
            col_found = true;
        }
        current = current->next;
    }
    connected_cols[col_index] = CHECKED;
    return col_found;
}

/*
Function: bb_check_connection
Itterates over all columns to look for connections.
Keeps doing it until no new column is found or the end_col is connected.  
*/
bool bb_check_connection(resistor_node *head, breadboard board, int start_col, int end_col){
    int *connected_cols = (int*)calloc(board.columns, sizeof(int));
    connected_cols[start_col] = UNCHECKED;
    int cols_found = 1;

    while(cols_found >0){
        cols_found = 0;
        for(int i = 0; i<board.columns; i++){
            if (connected_cols[i] == UNCHECKED){
                cols_found += add_connections(connected_cols, i, head); //Adding to cols_found so later checks dont overwrite earlier results.
                connected_cols[i] = CHECKED;
                
            }
            
        }
        if (connected_cols[end_col] != UNCONNECTED){
            free(connected_cols);
            return true;
            } 
    }
    free(connected_cols);
    return false;

}

void bb_free_list(resistor_node *head){
    resistor_node *temp;

    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}



