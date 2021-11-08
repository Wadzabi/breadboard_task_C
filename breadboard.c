#include <stdlib.h>
#include <stdio.h>
#include "breadboard.h"


int add_resistor(resistor_node **head, int c1, int c2, int r1){
    int temp;
    if(c1>c2){
        temp = c2;
        c2 = c1;
        c1 = temp;
    }
    
    coordinate point = {c1, r1};

    for(;point.x<=c2; point.x++){
        if(is_occupied((*head), point)) return -1;
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

bool is_occupied(resistor_node *head, coordinate point){
    resistor_node *current = head;
    while (current != NULL){
        if (point.x >= current->col1 && point.x <= current->col2 && point.y == current->row ) return true;
        current = current->next;
    }
    return false;
}

bool remove_resistor(resistor_node **head, coordinate point){
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

void print_board(resistor_node* head, breadboard board){
    resistor_node *current = head;
    for(int i = 0; i<board.rows; i++){
        for(int j = 0; j<board.columns; j++){
            if (current != NULL && i == current->row && j == current->col1){
                print_resistor(current);
                j = current->col2;
                current = current->next;
            } else printf(" O ");


        }
        printf("\n");

    }
}

void print_resistor(resistor_node *node){
    printf(" X-");
    for(int i = 0; i<(node->col2 - node->col1)-1; i++){
        printf("---");
    }
    printf("-X ");
}
bool add_connections(int *columns, int col_index, resistor_node *head){
    bool col_found = false;
    resistor_node *current = head;
    while(current != NULL ){
        if (current->col1 == col_index && columns[current->col2] == UNCONNECTED){
            columns[current->col2] = UNCHECKED;
            col_found = true;
        }
        else if (current->col2 == col_index && columns[current->col1] == UNCONNECTED) {
            columns[current->col1] = UNCHECKED;
            col_found = true;
        }
        current = current->next;
    }
    columns[col_index] = CHECKED;
    return col_found;
}


bool check_connection(resistor_node *head, breadboard board, int start_col, int end_col){
    int *columns = (int*)calloc(board.columns, sizeof(int));
    columns[start_col] = UNCHECKED;
    int cols_found = 1;

    while(cols_found >0){
        cols_found = 0;
        for(int i = 0; i<board.columns; i++){
            if (columns[i] == UNCHECKED){
                cols_found += add_connections(columns, i, head);
                columns[i] = CHECKED;
                
            }
            
        }
        if (columns[end_col] != UNCONNECTED){
            free(columns);
            return true;
            } 
    }
    free(columns);
    return false;

}

void free_list(resistor_node *head){
    resistor_node *temp;

    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}



