#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <sys/types.h>

int numbers[9] = {
    1,2,3,4,5,6,7,8,9
};

const unsigned int elements = sizeof(numbers) / sizeof(numbers[0]); 

int* random_numbers();
void sudo_gen(int *arr);

int main(void) {
    sudo_gen(random_numbers());
    
}

int* random_numbers() {
    srand(time(NULL));

    // the working is quite simple we are just swaping it after all
    for (int i = 0; i < elements; i++) {
        int index = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[index];
        numbers[index] = temp;
    }

    return numbers; 
}

void sudo_gen(int *arr) {
    int grid[9][9] = {0};

    for (int i = 0; i < elements; i++) {
        grid[0][i] = arr[i];
    }

    // list of 9 pointers -> function -> array
    int* (*list[9])();
    
    again:
    for (int i = 0; i < elements; i++) {
        list[i] = random_numbers;
    }

    for (int i = 0; i < elements; i++) {
        int* var = list[i]();
        if (arr[i] != *(var + i) ) {
            goto again;
        }
    }

    for (int i = 0; i < elements; i++) {
        for (int j = 0; j < elements; j++) {
            int *var = list[i]();
            grid[i][j] = var[j];
        }
    }
    
     

//----------------------------------------------------
    for (int i = 0; i < elements; i++) {
        for (int j = 0; j < elements; j++) {
            printf(" %d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
//-----------------------------------------------------
}
