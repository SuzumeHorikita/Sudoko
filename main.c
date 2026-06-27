#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAX_NUMS = 9;
int numbers[9] = {
    1,2,3,4,5,6,7,8,9
};
int grid[9][9] = {0};

void random_numbers();
void solver();

int main(void) {
    solver();
    return 0;
}

void random_numbers() {
    srand(time(NULL));

    for (int i = 0; i < MAX_NUMS; i++) {
        int index = (int) rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[index];
        numbers[index] = temp;
    }
}

void solver() {
    
    random_numbers();
    for (int i = 0; i < MAX_NUMS; i++) {
        grid[0][i] = numbers[i];
    }

    for (int i = 0; i < MAX_NUMS; i++) {
        for (int j = 0; j < MAX_NUMS; j++) {
            printf(" %d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
