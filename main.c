#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

int numbers[9] = {
        1,2,3,4,5,6,7,8,9
    };

static const unsigned int elements = sizeof(numbers) / sizeof(numbers[0]);

int* swap();
void box();

int main(void) {
    box();
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

void box() {
    int *(*ptr[9])();

    for (int i = 0; i < elements; i++) {
        *ptr[i] = swap;
    }
}
