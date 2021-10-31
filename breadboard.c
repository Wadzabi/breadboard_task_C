#include <stdlib.h>
#include <stdio.h>
#include "breadboard.h"


int add_resistor(resistor_node* head, breadboard board){
    
    if (head == NULL){
        head = malloc(sizeof(resistor_node));
    }

}

bool is_occupied(resistor_node* head, coordinate point);

bool remove_resistor(resistor_node* head, coordinate point);

void print_board(resistor_node* head, breadboard board);