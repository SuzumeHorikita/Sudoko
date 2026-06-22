#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 9

int boxes[MAX][MAX] = {0};

void solver(); // Just solve the sudoku
int num(int x); // return a individual number

int main(void) {
    solver();
    return 0;
}

void solver() {
    boxes[0][0] = num(0);
    boxes[8][8] = num(0);

    for (int i = 0;i < MAX ;i++ ) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ",boxes[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int num(int x) {
    int numbers[MAX] = {
        1,2,3,4,5,6,7,8,9
    };

    again:
        srand(time(NULL));
        int index = (int) rand() % 9;
        if (x == numbers[index]) {
            goto again;
        }

    return numbers[index];
}

// Next task check row and check column
/*
Working Process:
check the row,
check the column,
check the box
 */
