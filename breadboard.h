#include <stdbool.h>

typedef struct resistor_node{
    int resistance;
    int col1, col2, row;
    resistor_node* next;
    resistor_node* previous;

} resistor_node;

typedef struct coordinate{
    int x;
    int y;
} coordinate;

typedef struct breadboard{
    int rows;
    int columns;
} breadboard;

int add_resistor(resistor_node* head, breadboard board);

bool is_occupied(resistor_node* head, coordinate point);

bool remove_resistor(resistor_node* head, coordinate point);

void print_board(resistor_node* head, breadboard board);





