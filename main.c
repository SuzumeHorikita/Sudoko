#include <linux/limits.h>
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// gcc main.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
// maximum blanks 64 to min blanks 41
 struct Node_nums {
     int number;
     struct Node *next;
 };

const int MAX_NUMS = 9;
int numbers[9] = {
    1,2,3,4,5,6,7,8,9
};
int grid[9][9] = {0};

void random_numbers_firstrow();
bool solver(int row, int column);
bool check_row(int a_num, int row_index);
bool check_column(int a_num, int column_index);
bool check_3x3_grid(int a_num, int row_index, int column_index);
void create_blanks(); // create the blanks boxes

int main(void) {

    const int screenWidth = 800;
    const int screenHight = 450;

    InitWindow(screenWidth, screenHight, "Sudoko");

    SetTargetFPS(60);
    
    random_numbers_firstrow();
    bool isBoardGenerated = solver(1,0);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            if (isBoardGenerated) {
                DrawText("It generated", 190, 200, 20, BLACK);
            }
            else {
                DrawText("It failed", 190, 200, 20, BLACK);
            }
        EndDrawing();
    }
    CloseWindow();
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

bool solver(int row, int column) {
    if (column == 9) {
        row++;
        column = 0;
    }

    if(row == 9) {
        for (int i = 0; i < MAX_NUMS; i++) {
            for (int j = 0; j < MAX_NUMS; j++) {
                printf(" %d ", grid[i][j]);
            }
            printf("\n");
        }
        return true;
    }

    for (int num = 1; num <= 9 ; num++) {
        if (check_row(num, row) && check_column(num, column) && check_3x3_grid(num, row, column)) {
            grid[row][column] = num;
            if (solver(row, column + 1) == true) {
                return true;
            }
            grid[row][column] = 0;
        }
    }
    return false;
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

void create_blanks() {
    struct Node_nums *head = NULL;
    struct Node_nums *tail = NULL;
}
