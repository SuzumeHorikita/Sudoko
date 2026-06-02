#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numbers[9] = {
        1,2,3,4,5,6,7,8,9
    };

static const unsigned int elements = sizeof(numbers) / sizeof(numbers[0]);

int grid[9][9] = {0}; 

int* swap();
int (*box())[9];

int main(void) {
    int (*ptr)[9] = box();
    for (int i = 0; i < elements; i++) {
        for (int j = 0; j < elements; j++) {
            printf(" %d ", ptr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int* swap() {
    srand(time(NULL));
        
    for (int i = 0; i < elements; i++) {
        int index = (int)rand() % elements;
        int temp = numbers[i];
        numbers[i] = numbers[index];
        numbers[index] = temp;
    }

    return numbers;
}

int (*box())[9] {
    int *(*list_ptr[9])();

    for (int i = 0; i < elements; i++) {
        list_ptr[i] = swap;
    }

    for (int i = 0; i < elements; i++) {
        int *arr = list_ptr[i]();
        for (int j = 0; j < elements; j++) {
            grid[i][j] = arr[j];
        }
    }

    return grid;
}
