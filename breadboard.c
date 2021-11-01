#include <stdlib.h>
#include <stdio.h>
#include "breadboard.h"


int add_resistor(resistor_node **head, int c1, int c2, int r1){
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
    resistor_node *current = *head;
    if (point.y == current->row && (point.x >= current->col1 && point.x <= current->col2)){
        *head = (*head)->next;
        (*head)->previous = NULL;
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
            } else printf("|");


        }
        printf("\n");

    }
}

void print_resistor(resistor_node *node){
    const char dummy[] = "-------------------";
    printf("X%.*sX", (node->col2 - node->col1)-1, dummy);
}
