#include <linux/limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Node {
    int num;
    struct Node *next;
};

const int MAX_NUMS = 9;
int numbers[9] = {
    1,2,3,4,5,6,7,8,9
};
int grid[9][9] = {0};

void random_numbers_firstrow();
void solver();
bool check_row(int a_num, int row_index);
bool check_column(int a_num, int column_index);
bool check_3x3_grid(int a_num, int row_index, int column_index);
void other_option(int a_num, int row, int column);
void backup_option(); // i dont know what the hell i am doing

int main(void) {
    random_numbers_firstrow();
    solver();
    return 0;
}

void random_numbers_firstrow() {
    srand(time(NULL));

    for (int i = 0; i < MAX_NUMS; i++) {
        int index = (int) rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[index];
        numbers[index] = temp;
    }

    for (int i = 0; i < MAX_NUMS; i++) {
        grid[0][i] = numbers[i];
    }
}

void solver() {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    
    srand(time(NULL));
    int num[9] = {
        1,2,3,4,5,6,7,8,9
    };
    
    for (int i = 1; i < MAX_NUMS; i++) { // why use i = 1 because in grid[0][0..8] is all read filled
        for (int j = 0; j < MAX_NUMS; j++) {
            int row = i; // just for simplicity
            int column = j; // just for simplicity

            int rand_index = (int) rand() % 9;
            
            if (check_row(num[rand_index], row) == true && check_column(num[rand_index], column) == true && check_3x3_grid(num[rand_index], row, column) == true) {
                grid[row][column] = num[rand_index];
            }
            else {
                other_option(num[rand_index], row, column);
            }
        }
    }
// How it works
// it first check if she find 0
// if yes subtract 1 in column and if column < 0
// then simpily subtract 1 in row and set column = 8 back
// and she assign to node->num = grid[i][j] which is a linked list
// it she pass it to other_options
// she she add a another number to node 
// while (true) {
    struct Node *node = malloc(sizeof(*node));
    int count = 0;
        for (int i = 0; i < MAX_NUMS; i++) {
            for (int j = 0; j < MAX_NUMS; j++) {
                if (grid[i][j] == 0) {
                      j -= 1;
                      if (j < 0) {
                          i -= 1;
                          j = 8;
                      }
                        
                      if(node == NULL) {
                          printf("Memory full\n");
                          return;
                      }
                      node->next = NULL;
                      update:
                      node->num = grid[i][j];
                      if (head == NULL) {
                          head = node;
                          tail = node;
                      } else {
                          tail->next = node;
                          tail = node;
                      }
                      other_option(grid[i][j], i, j);
                      for (int k = 1; k < MAX_NUMS; k++) {
                          count += 1;
                          goto update;
                      }
                }
            }
        }
//    }
    
    for (int i = 0; i < MAX_NUMS; i++) {
        for (int j = 0; j < MAX_NUMS; j++) {
            printf(" %d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool check_row(int a_num, int row) { // because column changes not the row
    for (int i = 0; i < MAX_NUMS; i++) {
        if (grid[row][i] == a_num) {
            return false;
        }
    }
    return true;
}

bool check_column(int a_num, int column) {
    for (int i = 0; i < MAX_NUMS; i++) {
        if (grid[i][column] == a_num) {
            return false;
        }
    }
    return true;
}
bool check_3x3_grid(int a_num, int row, int column) { 
    int start_row = (int) (row / 3) * 3;
    int start_column = (int) (column / 3) * 3;

    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (grid[i + start_row][j + start_column] == a_num) {
                return false;
            }
        }
    }
    return true;
}


void other_option(int a_num, int row, int column) {
    for (int i = 0; i < MAX_NUMS; i++) {
        if (numbers[i] == a_num) {
            continue;
        }
        else if (check_row(numbers[i], row) == true && check_column(numbers[i], column) == true && check_3x3_grid(numbers[i], row, column) == true) {
            grid[row][column] = numbers[i];
            break;
        }
    }
}
// in this code there is a flow that we put the number and never check
// that this number is valid in future because the reason is this the number
// we put had a problem ultimetly there is a point where there is no number valid
// so the result there is some places zero are there
void backup_option() {
    for (int i = 0; i < MAX_NUMS; i++) {
        for (int j = 0; j < MAX_NUMS; j++) {
            if (grid[i][j] == 0) {
                j -= 1;
                if (j < 0) {
                    i -= 1;
                    j = 8;
                    if (i == 0) {
                        backup_option();
                    }
                }
                int a_num = grid[i][j];
                other_option(a_num, i, j);
                backup_option();
            }
            else {
                break;
            }
        }
    }
}
