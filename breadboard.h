#include <stdbool.h>

typedef struct resistor_node{
    int resistance;
    int col1, col2, row;
    struct resistor_node* next;
    struct resistor_node* previous;

} resistor_node;

typedef struct coordinate{
    int x;
    int y;
} coordinate;

typedef struct breadboard{
    int rows;
    int columns;
} breadboard;

enum column_state{UNCONNECTED, UNCHECKED, CHECKED};

int bb_add_resistor(resistor_node **head, int col1, int col2, int row);

bool bb_is_occupied(resistor_node *head, coordinate point);

bool bb_remove_resistor(resistor_node **head, coordinate point);

void bb_print_board(resistor_node *head, breadboard board);

void print_resistor(resistor_node *node);

bool bb_check_connection(resistor_node *head, breadboard board, int start_col, int end_col);

void bb_free_list(resistor_node *head);





