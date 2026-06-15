#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numbers[9] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9
};

static const unsigned int elements = sizeof(numbers) / sizeof(numbers[0]);

int grid[9][9] = {0};

int *swap(); // just swap the numbers[9]
int (*box())[9]; // fill the grid[9][9] with numbers
void final_swap(int box[9][9]); // here is the problem

int main(void)
{
    final_swap(box());
   
    return 0;
}

int *swap()
{
    srand(time(NULL)); // seed the rand()

    for (int i = 0; i < elements; i++)
    {
        int index = (int)rand() % elements;
        int temp = numbers[i];
        numbers[i] = numbers[index];
        numbers[index] = temp;
    }

    return numbers;
}

int (*box())[9]
{
    int *(*list_ptr[9])(); // array of pointer -> all point to a swap() function -> gives an swap number array

    for (int i = 0; i < elements; i++)
    {
        list_ptr[i] = swap;
    }

    for (int i = 0; i < elements; i++)
    {
        int *arr = list_ptr[i]();
        for (int j = 0; j < elements; j++)
        {
            grid[i][j] = arr[j];
        }
    }

    return grid;
}

void final_swap(int box[9][9]) { 

    for (int i = 0; i < elements; i++)
    {
        for (int j = 0; j < elements; j++)
        {
            printf(" %d ", box[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
