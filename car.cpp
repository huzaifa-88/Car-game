#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <accctrl.h>
#include <sstream>
#include <string>
#include <string.h>
#include <fstream>
#include <ctime>
#include <time.h>
#include <cmath>
using namespace std;

//Global Variables & Arrays
char maze[17][47];
int CarX = 15;
int CarY = 21;
int score = 0;
int lives = 3;
bool gravity = true;
bool value;
string temp;
bool game_start;
int orbitrary = 1;
char previousItem = ' ';
char car = 178;
int count_Energy = 0;

// Functions Prototypes
void gotoxy(int x, int y);
void load();
void Maze();
void Instructions();
void calculateScore();
void printScore();
void calculateLives();
void print_lives();
void gravityStatus(bool value);
void time_Tick(int times);
void RoadShow();
int createRandom();
void Energy_Remover();
void Score_counter();
void moveCarRight();
void moveCarLeft();
void moveCarUp();
void moveCarDown();
void Game_Over();




void load()
{
    fstream file;
    file.open("CarBoard.txt", ios::in);
    string line;
    for (int i = 0; i < 17; i++)
    {
        getline(file, line);
        for (int j = 0; j < 47; j++)
        {
            maze[i][j] = line[j];
        }
    }
    file.close();
}

void Maze()
{

    for (int x = 0; x < 17; x++)
    {
        for (int y = 0; y < 47; y++)
        {
            cout << maze[x][y];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = y;
    coordinates.Y = x;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void Instructions()
{
    gotoxy(1, 60);
    cout << "Instructions For The Player!!!:";
    gotoxy(4, 60);
    cout << "@,$ and & are enemies!";
    gotoxy(8, 60);
    cout << "<<<(E) boost  your  life by one point>>>" << endl;
}

void calculateScore()
{
    score = score + 1;
}

void printScore()
{
    gotoxy(18, 15);
    cout << "Score: " << score << endl;
}

void calculateLives()
{
    lives = lives + 1;
}

void print_lives()
{
    gotoxy(18, 1);
    cout << "Lives: " << lives << endl;
}

void gravityStatus(bool value)
{
    value = true;
}

void RoadShow()
{
    for (int x = 1; x < 16; x++)
    {
        for (int y = 13; y < 33; y++)
        {
            gotoxy(x, y);
            cout << maze[x][y];
        }
    }
}

void time_Tick(int times)
{
    int count = 0, iterCOunt = 0;
    if (game_start)
    {
        while (count < times)
        {
            for (int row = 15; row > 0; row--)
            {
                for (int col = 13; col < 33; col++)
                {
                    if (maze[row][col] == '$')
                    {

                        maze[row + 1][col] = '$';
                    }

                    if (maze[row][col] == 'E')
                    {
                        maze[row + 1][col] = 'E';
                    }

                    if (maze[row][col] == '&')
                    {
                        maze[row + 1][col] = '&';
                    }

                    if (maze[row][col] == ' ')
                    {
                        maze[row + 1][col] = ' ';
                    }

                    if (maze[row][col] == '@')
                    {
                        maze[row + 1][col] = '@';
                    }
                    if (maze[CarX][CarY] != ' ' && maze[CarX][CarY] != 'E')
                    {
                        lives--;
                        score--;
                        CarX = 15;
                        CarY = 21;
                    }
                }
            }
            count++;
        }
    }
}

void Move_array()
{
    for (int row = 15, col = 13; col < 33; col++)
    {
        if (maze[row][col] == 'E')
            maze[row][col] = ' ';

        temp = temp + maze[row][col];
    }
}

void show_array()
{
    for (int row = 1, col = 13; col < 33; col++)
    {
        maze[row][col] = temp[col - 13];
    }
}

int createRandom()
{
    int result;
    srand(time(0));
    result = ((rand() + orbitrary) % 6) + 1;
    orbitrary = orbitrary + 3;
    return result;
}

void Random()
{
    int x = createRandom();
    if (score % 30 == 0)
    {
        if (x == 1)
        {
            gotoxy(1, 14);
            maze[1][14] = 'E';
        }

        else if (x == 2)
        {
            gotoxy(1, 20);
            maze[1][20] = 'E';
        }

        else if (x == 3)
        {
            gotoxy(1, 29);
            maze[1][29] = 'E';
        }

        else if (x == 4)
        {
            gotoxy(1, 23);
            maze[1][23] = 'E';
        }

        else if (x == 5)
        {
            gotoxy(1, 16);
            maze[1][16] = 'E';
        }

        else if (x == 6)
        {
            gotoxy(1, 32);
            maze[1][32] = 'E';
        }
    }
}

void moveCarRight()
{
    if (maze[CarX][CarY + 1] == ' ' || maze[CarX][CarY + 1] == 'E' || maze[CarX][CarY + 1] == '@' || maze[CarX][CarY + 1] == '$' || maze[CarX][CarY + 1] == '&')
    {

        gotoxy(CarX, CarY);
        cout << previousItem;
        CarY = CarY + 1;
        // previousItem = maze[CarX][CarY];

        if (maze[CarX][CarY] == 'E')
        {
            maze[CarX][CarY] = ' ';
            calculateLives();
        }

        if (maze[CarX][CarY] == '$' || maze[CarX][CarY] == '@' || maze[CarX][CarY] == '&')
        {
            lives--;
            score--;
            CarX = 15;
            CarY = 21;
        }

        gotoxy(CarX, CarY);
        cout << car;
    }
}

void moveCarLeft()
{
    if (maze[CarX][CarY - 1] == ' ' || maze[CarX][CarY - 1] == 'E' || maze[CarX][CarY - 1] == '@' || maze[CarX][CarY - 1] == '$' || maze[CarX][CarY - 1] == '&')
    {

        gotoxy(CarX, CarY);
        cout << previousItem;
        CarY = CarY - 1;
        // previousItem = maze[CarX][CarY];

        if (maze[CarX][CarY] == 'E')
        {
            maze[CarX][CarY] = ' ';
            calculateLives();
        }

        if (maze[CarX][CarY] == '$' || maze[CarX][CarY] == '@' || maze[CarX][CarY] == '&')
        {
            lives--;
            score--;
            CarX = 15;
            CarY = 21;
        }

        gotoxy(CarX, CarY);
        cout << car;
    }
}

void moveCarUp()
{
    if (maze[CarX - 1][CarY] == ' ' || maze[CarX - 1][CarY] == 'E' || maze[CarX - 1][CarY] == '$' || maze[CarX - 1][CarY] == '@' || maze[CarX - 1][CarY] == '&')
    {

        gotoxy(CarX, CarY);
        cout << previousItem;
        CarX = CarX - 1;
        // previousItem = maze[CarX][CarY];

        gotoxy(CarX, CarY);
        cout << car;
        if (maze[CarX][CarY] == 'E')
        {
            maze[CarX][CarY] = ' ';
            calculateLives();
        }

        if (maze[CarX][CarY] == '$' || maze[CarX][CarY] == '@' || maze[CarX][CarY] == '&')
        {
            lives--;
            score--;
            CarX = 15;
            CarY = 21;
        }
    }
}

void moveCarDown()
{
    if (CarX != 15)
    {
        if (maze[CarX + 1][CarY] == ' ' || maze[CarX + 1][CarY] == 'E' || maze[CarX + 1][CarY] == '@' || maze[CarX + 1][CarY] == '$' || maze[CarX + 1][CarY] == '&')
        {

            gotoxy(CarX, CarY);
            cout << previousItem;
            CarX = CarX + 1;
            // previousItem = maze[CarX][CarY];

            if (maze[CarX][CarY] == 'E')
            {
                maze[CarX][CarY] = ' ';
                calculateLives();
            }

            if (maze[CarX][CarY] == '$' || maze[CarX][CarY] == '@' || maze[CarX][CarY] == '&')
            {
                lives--;
                score--;
                CarX = 15;
                CarY = 21;
            }

            gotoxy(CarX, CarY);
            cout << car;
        }
    }
}

void Score_counter()
{
    for (int x = 1; x < 16; x++)
    {
        if (CarX == x)
        {
            for (int i = x, j = 13; j < 33; j++)
            {
                if (maze[i][j] == '$' || maze[i][j] == '&' || maze[i][j] == '@')
                    calculateScore();
            }
        }
    }
}

void Energy_Remover()
{
    for (int b = 13; b < 33; b++)
    {
        if (maze[1][b] == 'E')
        {
            for (int c = 13; c < 33; c++)
            {
                if (maze[2][c] == 'E')
                    maze[1][b] = ' ';

                if (maze[2][c] == ' ' || maze[3][c] == ' ')
                    maze[1][b] = ' ';

                if (maze[2][c] == ' ' || maze[4][c] == ' ')
                    maze[1][b] = ' ';
            }
        }
    }
}

void Game_Over()
{
    system("CLS");

    gotoxy(13, 20);
    cout << " Game Over" << endl;
    
}

int main()
{
    system("CLS");
    // system("Color 0C");

    load();
    Maze();
      getch();
      Instructions();
    int speed = 100;
    game_start = true;
    while (game_start)
    {
        gotoxy(CarX, CarY);
        cout << car;
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO cursorInfo;

        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        Sleep(speed);

        RoadShow();
        gravityStatus(value);
        Move_array();
        time_Tick(1);
        Score_counter();
        show_array();
        Random();
        Energy_Remover();
        RoadShow();
        temp = "";
        count_Energy = 0;

        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveCarRight(); // Function call to move Car towards right
        }

        if (GetAsyncKeyState(VK_LEFT))
        {
            moveCarLeft(); // Function call to move Car towards right
        }

        if (GetAsyncKeyState(VK_UP))
        {
            moveCarUp(); // Function call to move Car towards right
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            moveCarDown(); // Function call to move Car towards right
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            game_start = false; // Stop the game
        }

        if (score % 50 == 0)
        {
            if (speed >= 100)
                speed = speed + 50;
        }

        printScore();
        print_lives();
        gotoxy(18, 30);
        // cout << "Speed = " << speed;

        if (lives < 1)
        {
            game_start = false;
            system("CLS");
            Game_Over();
        }
    }
    return 0;
}