#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int numbers[9] = {
    1,2,3,4,5,6,7,8,9
};
int numbers_of_elements = sizeof(numbers) / sizeof(numbers[0]);

int *rand_list();

int main(void) 
{
    int *list1 = rand_list();
    int *list2 = rand_list();

// -------------------------------------------------------
    for (int i = 0; i < numbers_of_elements; i++) 
    {
        printf(" %d ", list1[i]);
    }
    printf("\n");
    for (int i = 0; i < numbers_of_elements; i++) 
    {
        printf(" %d ", list2[i]);
    }
    printf("\n");
// -----------------------------------------------------------
}

int *rand_list()
{
    enum Target{
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9
    };

    int *rand_num = calloc(numbers_of_elements, sizeof(int)); // makes a contiguous memory allocation and set 0 to it
    
    /*
    this do_it_again: actually work like this
    1. generate bad data
    2. test it 
    3. retry it again
    */
    do_it_again:
        ; // this ; is for the compiler problem
        int list_count[9] = {0}; // set all elements to 0

        for (int i = 0; i < numbers_of_elements; i++) 
        {
            int random_index = (int) (rand() % 9);   // gives index from 0 to 8
            rand_num[i] = numbers[random_index];            
        }

        for (int i = 0; i < numbers_of_elements; i++) {
            switch (rand_num[i]) 
            {
                case ONE: {
                    list_count[0] += 1;
                    break;
                }
                case TWO: {
                    list_count[1] += 1;
                    break;
                }
                case THREE: {
                    list_count[2] += 1;
                    break;
                }
                case FOUR: {
                    list_count[3] += 1;
                    break;
                }
                case FIVE: {
                    list_count[4] += 1;
                    break;
                }
                case SIX: {
                    list_count[5] += 1;
                    break;
                }
                case SEVEN: {
                    list_count[6] += 1;
                    break;
                }
                case EIGHT: {
                    list_count[7] += 1;
                    break;
                }
                case NINE: {
                    list_count[8] += 1;
                    break;
                }
            }
        }

    for (int i = 0; i < numbers_of_elements; i++) {
        if (list_count[i] > 1) {
            goto do_it_again;
        }
    }

    return rand_num;
}