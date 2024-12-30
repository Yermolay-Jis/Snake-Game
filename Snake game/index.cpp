#include <iostream>
#include <windows.h>
using namespace std;

// Create a map
char map[] =
    "##########################\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "#                        #\n"
    "##########################\n";

// Create a size for snake
const int WIDTH = 27;
const int HEIGHT = 13;
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT - 2);

// Creating a snake and food look and score
char food = '*';
char snake = 'O';
int score = 1;

// Coordinates for snake and food
int food_x = 1 + (rand() % (WIDTH - 3));
int food_y = 1 + (rand() % (HEIGHT - 2));
int snake_x[MAX_LEN_SNAKE] = {0};
int snake_y[MAX_LEN_SNAKE] = {0};
int snake_len = 1;

// The direction of mavement
const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;

int snake_dir = UP;
bool snake_is_running = true;

// A function  that brings the entire interface to a single point
void gotoxy(short int x, short int y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

int main()
{

    snake_x[0] = WIDTH / 2;
    snake_y[0] = HEIGHT / 2;
    double time = clock();

    // Start a game
    while (snake_is_running)
    {
        if (snake_x[0] == food_x && snake_y[0] == food_y)
        {
            snake_len++;
            cout << "\n\nScore: " << score++ << "\nSnake lenght: " << snake_len;
            food_x = 1 + (rand() % (WIDTH - 3));
            food_y = 1 + (rand() % (HEIGHT - 2));
        }

        // Snake control
        if (GetKeyState('W') & 0x8000)
        {
            if (snake_dir != DOWN)
            {
                snake_dir = UP;
            }
        }
        if (GetKeyState('S') & 0x8000)
        {
            if (snake_dir != UP)
            {
                snake_dir = DOWN;
            }
        }
        if (GetKeyState('D') & 0x8000)
        {
            if (snake_dir != LEFT)
            {
                snake_dir = RIGHT;
            }
        }
        if (GetKeyState('A') & 0x8000)
        {
            if (snake_dir != RIGHT)
            {
                snake_dir = LEFT;
            }
        }

        // Setting fps
        if ((clock() - time) / CLOCKS_PER_SEC >= 0.5)
        {
            time = clock();
            for (int i = snake_len - 1; i >= 0; i--)
            {
                snake_x[i + 1] = snake_x[i];
                snake_y[i + 1] = snake_y[i];
            }

            if (snake_dir == UP)
            {
                snake_y[0]--;
            }
            if (snake_dir == DOWN)
            {
                snake_y[0]++;
            }
            if (snake_dir == RIGHT)
            {
                snake_x[0]++;
            }
            if (snake_dir == LEFT)
            {
                snake_x[0]--;
            }

            // Conditions under which the game stops
            if (snake_x[0] == 0 || snake_x[0] == WIDTH - 2 || snake_y[0] == 0 || snake_y[0] == HEIGHT - 1)
            {
                if (snake_dir == UP)
                {
                    snake_y[0] = HEIGHT - 2;
                }
                if (snake_dir == DOWN)
                {
                    snake_y[0] = 1;
                }
                if (snake_dir == RIGHT)
                {
                    snake_x[0] = 1;
                }
                if (snake_dir == LEFT)
                {
                    snake_x[0] = WIDTH - 3;
                }
            }

            for (int i = 1; i < snake_len; i++)
            {
                if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
                {
                    snake_is_running = false;
                }
            }

            // Creating a food on the map and starting function gotoxy()
            map[food_y * WIDTH + food_x] = food;
            gotoxy(0, 0);

            // Creating a snake on the map
            for (int i = 0; i < snake_len; i++)
            {
                map[snake_y[i] * WIDTH + snake_x[i]] = snake;
            }
            cout << map;

            for (int i = 0; i < snake_len; i++)
            {
                map[snake_y[i] * WIDTH + snake_x[i]] = ' ';
            }
        }
    }
    gotoxy(8, HEIGHT / 2);
    cout << "Game over";
    gotoxy(WIDTH, HEIGHT);
}