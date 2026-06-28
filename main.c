#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int MAX_NUMS = 9;
int numbers[9] = {
    1,2,3,4,5,6,7,8,9
};
int grid[9][9] = {0};

void random_numbers_firstrow();
void solver();
bool check_row(int a_num);
bool check_cloumn(int a_num);
bool check_3x3_grid(int a_num);

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
    srand(time(NULL));
    int num[9] = {
        1,2,3,4,5,6,7,8,9
    };
    int rand_index = (int) rand() % 9;

    // Check the row
    check_row(num[rand_index]);
    // Check the 3 X 3 Board
    check_3x3_grid(num[rand_index]);
    // Check the column 
    check_cloumn(num[rand_index]);   
    
    for (int i = 0; i < MAX_NUMS; i++) {
        for (int j = 0; j < MAX_NUMS; j++) {
            printf(" %d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool check_row(int a_num) {
    return true;
}

bool check_column(int a_num) {
    return true;
}
bool check_3x3_grid(int a_num) {
    return true;
}
