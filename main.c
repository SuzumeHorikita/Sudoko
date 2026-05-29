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

int main(void) {
    int *numbers = random_numbers();
    
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
