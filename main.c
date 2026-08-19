#include <linux/limits.h>
#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

// gcc main.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
 struct Node {
     int number;
     struct Node *next;
 };

 struct CopyBlank {
     short i;
     short j;
     struct CopyBlank *next;
 };

const unsigned int MAX_NUMS = 9;
const unsigned int TITLE_SIZE = 45; 

int numbers[9] = {
    1,2,3,4,5,6,7,8,9
};
int grid[9][9] = {0};

void random_numbers_firstrow();
bool solver(int row, int column);
bool check_row(int a_num, int row_index);
bool check_column(int a_num, int column_index);
bool check_3x3_grid(int a_num, int row_index, int column_index);
struct Node * create_blanks(); // create the blanks boxes and return pointer 
void fill_blank(int row, int col, int keypressed);
bool edit_previous(struct CopyBlank *head, int row, int column);
struct CopyBlank * create_copy_of_blank();
bool final_end_game(struct Node *head);

int main(void) {
    
    const int screenWidth = 800;
    const int screenHight = 450;

    InitWindow(screenWidth, screenHight, "Sudoko");

    SetTargetFPS(60);

    // this is for the center the board
    float grid_width = MAX_NUMS * TITLE_SIZE;
    float grid_height = MAX_NUMS * TITLE_SIZE;
    Vector2 grid_center = (Vector2){
        (GetScreenWidth() - grid_width) / 2,
        (GetScreenHeight() - grid_height) / 2
    };
    
    // this is for the board background color
    Color lightLime = {190, 253, 115, 255};
    Color box_colors[9] = {
        lightLime, WHITE, lightLime, WHITE, lightLime, WHITE, lightLime, WHITE, lightLime 
    };
    
    // Generate of board and make a copy of it
    random_numbers_firstrow();
    bool isBoardGenerated = solver(1,0);

    // ---------------------------------------------------------------------------
    for (int i = 0; i < MAX_NUMS; i++) {
        for (int j = 0; j < MAX_NUMS; j++) {
            printf(" %d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // ----------------------------------------------------------------------------
    struct Node *final_check = create_blanks();
    struct CopyBlank *blank_position = create_copy_of_blank();

    bool game_over = false, player_win = false;

    while (!WindowShouldClose()) {
        // mouse interaction with the blank
        Vector2 mousePosition = GetMousePosition();
        int select_row, select_col;
        if (mousePosition.x >= grid_center.x && mousePosition.x <= grid_center.x + (9 * TITLE_SIZE) && mousePosition.y >= grid_center.y && mousePosition.y <= grid_center.y + (9 * TITLE_SIZE)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int mouse_col = (mousePosition.x - grid_center.x) / TITLE_SIZE;
                int mouse_row = (mousePosition.y - grid_center.y) / TITLE_SIZE;
                if (grid[mouse_row][mouse_col] == 0) {
                    select_row = mouse_col;
                    select_col = mouse_row;
                }
                if (edit_previous(blank_position, mouse_row, mouse_col)) {
                    select_row = mouse_col;
                    select_col = mouse_row;
                }
            }
        }

        // keyboard interaction with the blank 
        int keypress = GetKeyPressed();
        if (keypress >= KEY_ONE && keypress <= KEY_NINE) {
            if (select_row != -1 && select_col != -1) {
                fill_blank(select_col, select_row, keypress);
            }
        }
        

        // Game over condition 
        if (keypress == KEY_ENTER) {
            if (final_end_game(final_check)) {
                game_over = true;
                player_win = true;
            }
            else {
                game_over = true;
                player_win = false;
            } 
        } 
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // game end condition
            if (game_over) {
                if (player_win) {
                    DrawRectangle(0, 0, screenWidth, screenHight, BLACK);
                    DrawText("YOU WIN", 190, 200, 50, GREEN);
                }
                else {  
                    DrawRectangle(0, 0, screenWidth, screenHight, BLACK);
                    DrawText("YOU LOSE!", 190, 200, 50, RED);
                }
            } else {
            // just center the grid and make a board 
            for (int x = 0; x < MAX_NUMS; x++) {
                for (int y = 0; y < MAX_NUMS; y++) {
                    int box_row = (int)x / 3;
                    int box_col = (int)y / 3;
                    int box_index = box_row * 3 + box_col;
                    
                    DrawRectangle(grid_center.x + (y * TITLE_SIZE), grid_center.y + (x * TITLE_SIZE), TITLE_SIZE, TITLE_SIZE, box_colors[box_index]);
                    if (grid[x][y] == 0)
                        continue;
                    DrawText( TextFormat(" %d ", grid[x][y]), grid_center.x + (y * TITLE_SIZE), grid_center.y + (x * TITLE_SIZE), 25, RED);
                }
            }

            // drawing of boaders and the interaction with the mouse
            for (int x = 0; x < MAX_NUMS; x++) {
                for (int y = 0; y < MAX_NUMS; y++) {
                    if (x == select_row && y == select_col) 
                        DrawRectangleLines(grid_center.x + (x * TITLE_SIZE), grid_center.y + (y * TITLE_SIZE), TITLE_SIZE, TITLE_SIZE, WHITE);
                    else 
                        DrawRectangleLines(grid_center.x + (x * TITLE_SIZE), grid_center.y + (y * TITLE_SIZE), TITLE_SIZE, TITLE_SIZE, BLACK);
                }
            }
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

    if(row == 9) 
        return true;

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

bool check_row(int a_num, int row) {
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

struct Node * create_blanks() {
    // making a linked list to store the grid[i][j] 
    struct Node *head = NULL;
    struct Node *tail = NULL;

    for (int i = 0; i < MAX_NUMS; i++) {
        for (int j = 0; j < MAX_NUMS; j++) {
            struct Node *node = malloc(sizeof(*node));
            if (node == NULL) {
                printf("memory err\n");
                return NULL;
            }
            node->next = NULL;
            node->number = grid[i][j];
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
    }
    
    // removing the random numbers from grid
    srand(time(NULL));
    int max = 65;
    int min = 41;
    int rand_blank = rand() % (max - min) + min;

    int *flat_grid = (int *) grid; // acess grid as a flat 1d array

    int *pool = calloc(81, sizeof(int));
    for (int i = 0; i < 81;i++)
        pool[i] = i;
    
    for (int i = 0; i < rand_blank; i++) {
        int index = rand() % 81;
        if (pool[index] == -1)
            i -= 1;
        else {
            flat_grid[index] = 0;
            pool[index] = -1;
        }
    }

    // freeing the pool
    free(pool);
    pool = NULL;

    // return the head because to make the final condition
    return head;
}
// Note: remember to free the list also
void fill_blank(int row, int col, int keypressed) {
    unsigned short num;
    num = keypressed - KEY_ONE + 1;
    grid[row][col] = num;
}

struct CopyBlank * create_copy_of_blank() {
    struct CopyBlank *head = NULL;
    struct CopyBlank *tail = NULL;

    for (int i = 0; i < MAX_NUMS; i++) {
        for (int j = 0; j < MAX_NUMS; j++) {
            if (grid[i][j] == 0) {
                struct CopyBlank *node = malloc(sizeof(*node));
                if (node == NULL) {
                    printf("memory err\n");
                    return NULL;
                }
                node->next = NULL;
                node->i = i;
                node->j = j;

                if (head == NULL) {
                    head = node;
                    tail = node;
                } else {
                    tail->next = node;
                    tail = node;
                }
            }
        }
    }
    return head;
} 

bool edit_previous(struct CopyBlank *head, int row, int column) {
    struct CopyBlank *index = head;
    while (index != NULL) {
        if (index->i == row && index->j == column)
            return true;
        index = index->next;
    }
    return false;
}

bool final_end_game(struct Node *head) {
    struct Node *ptr = head;
    int i = 0 , j = 0;
    while (ptr != NULL) {
        if (ptr->number != grid[i][j]) {
            while (head != NULL) {
                ptr = head;
                head = head->next;
                free(ptr);
            }
            return false;
        }
        j++;
        if (j == 9) {
            j = 0;
            i++;
        }
        ptr = ptr->next;
    }

    // when you win it get freed
    while (head != NULL) {
        ptr = head;
        head = head->next;
        free(ptr);
    }
    return true;
}
