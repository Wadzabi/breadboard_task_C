#include <stdlib.h>
#include <stdio.h>
#include "breadboard.h"


int add_resistor(resistor_node *head, int col1, int col2, int row){
    printf("Enter row ");

    if (head == NULL){
        head = malloc(sizeof(resistor_node));
    }

}

bool is_occupied(resistor_node *head, coordinate point){
    resistor_node *current = head;
    while (current != NULL){
        if (point.x >= current->col1 && point.x <= current->col2 && point.y == current->row ){
            return true;
        }
        current = current->next;
    }
    return false;
}

bool remove_resistor(resistor_node* head, coordinate point);

void print_board(resistor_node* head, breadboard board);