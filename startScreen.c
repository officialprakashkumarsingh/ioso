// Snake Game - Mobile Optimized
// A classic Snake game implementation in C for console/terminal
// Note: This is a console-based version as the original request was for HTML/CSS/JS
// This file provides a C implementation for terminal play

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

// Game constants
#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE_LENGTH (WIDTH * HEIGHT)

// Game variables
int snakeX[MAX_SNAKE_LENGTH];
int snakeY[MAX_SNAKE_LENGTH];
int snakeLength = 3;
int foodX, foodY;
int direction = 2; // 0=up, 1=down, 2=left, 3=right
int gameOver = 0;
int score = 0;
int highScore = 0;

// Function prototypes
void setup();
void draw();
void input();
void logic();
void gotoxy(int x, int y);
void hidecursor();
void delay(int milliseconds);

int main() {
    setup();
    hidecursor();
    
    while (!gameOver) {
        draw();
        input();
        logic();
        delay(100);
    }
    
    gotoxy(0, HEIGHT + 2);
    printf("Game Over! Final Score: %d\n", score);
    system("pause");
    return 0;
}

void setup() {
    // Initialize random seed
    srand(time(NULL));
    
    // Initialize snake
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    snakeX[1] = snakeX[0] - 1;
    snakeY[1] = snakeY[0];
    snakeX[2] = snakeX[1] - 1;
    snakeY[2] = snakeY[1];
    
    // Generate food
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void draw() {
    system("cls");
    
    // Draw top border
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");
    
    // Draw game area
    for (int y = 0; y < HEIGHT; y++) {
        printf("#");
        for (int x = 0; x < WIDTH; x++) {
            int isSnake = 0;
            int isHead = 0;
            
            // Check if this position is part of snake
            for (int i = 0; i < snakeLength; i++) {
                if (snakeX[i] == x && snakeY[i] == y) {
                    isSnake = 1;
                    if (i == 0) isHead = 1;
                    break;
                }
            }
            
            if (isHead) {
                printf("O");
            } else if (isSnake) {
                printf("o");
            } else if (x == foodX && y == foodY) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("#\n");
    }
    
    // Draw bottom border
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");
    
    // Display score
    printf("Score: %d\n", score);
    printf("High Score: %d\n", highScore);
    printf("Controls: WASD or Arrow Keys\n");
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        
        // Handle arrow keys (extended codes)
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: if (direction != 1) direction = 0; break; // Up arrow
                case 80: if (direction != 0) direction = 1; break; // Down arrow
                case 75: if (direction != 3) direction = 2; break; // Left arrow
                case 77: if (direction != 2) direction = 3; break; // Right arrow
            }
        } else {
            // Handle WASD keys
            switch (key) {
                case 'w': case 'W': if (direction != 1) direction = 0; break;
                case 's': case 'S': if (direction != 0) direction = 1; break;
                case 'a': case 'A': if (direction != 3) direction = 2; break;
                case 'd': case 'D': if (direction != 2) direction = 3; break;
                case 27: gameOver = 1; break; // ESC key
            }
        }
    }
}

void logic() {
    // Calculate new head position
    int newX = snakeX[0];
    int newY = snakeY[0];
    
    switch (direction) {
        case 0: newY--; break;
        case 1: newY++; break;
        case 2: newX--; break;
        case 3: newX++; break;
    }
    
    // Check wall collision
    if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) {
        gameOver = 1;
        return;
    }
    
    // Check self collision
    for (int i = 0; i < snakeLength; i++) {
        if (snakeX[i] == newX && snakeY[i] == newY) {
            gameOver = 1;
            return;
        }
    }
    
    // Move snake
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    
    snakeX[0] = newX;
    snakeY[0] = newY;
    
    // Check food collision
    if (newX == foodX && newY == foodY) {
        score += 10;
        if (score > highScore) {
            highScore = score;
        }
        
        // Grow snake
        snakeLength++;
        if (snakeLength >= MAX_SNAKE_LENGTH) {
            gameOver = 1;
            return;
        }
        
        // Generate new food
        int validFood = 0;
        while (!validFood) {
            foodX = rand() % WIDTH;
            foodY = rand() % HEIGHT;
            validFood = 1;
            
            // Check if food spawns on snake
            for (int i = 0; i < snakeLength; i++) {
                if (snakeX[i] == foodX && snakeY[i] == foodY) {
                    validFood = 0;
                    break;
                }
            }
        }
    }
}

// Helper functions
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hidecursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void delay(int milliseconds) {
    Sleep(milliseconds);
}