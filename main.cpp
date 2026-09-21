#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;

int speed = 500;             
const int SPEED_STEP = 25;  
const int MIN_SPEED = 100;  
 
char blocks[][4][4] = {
    {{' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}},
    {{' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {'I', 'I', 'I', 'I'}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'T', ' ', ' '}, {'T', 'T', 'T', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'S', 'S', ' '}, {'S', 'S', ' ', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {'Z', 'Z', ' ', ' '}, {' ', 'Z', 'Z', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {'J', ' ', ' ', ' '}, {'J', 'J', 'J', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', ' ', 'L', ' '}, {'L', 'L', 'L', ' '}, {' ', ' ', ' ', ' '}}};
bool canMove(int dx, int dy)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
            {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W - 1 || yt >= H - 1)
                    return false;
                if (board[yt][xt] != ' ')
                    return false;
            }
    return true;
}
void rotate()
{
    char rotated[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            rotated[j][3 - i] = blocks[b][i][j];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (rotated[i][j] != ' ')
            {
                int xt = x + j;
                int yt = y + i;
                if (xt < 1 || xt >= W - 1 || yt < 1 || yt >= H - 1)
                    return;
                if (board[yt][xt] != ' ')
                    return;
            }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            blocks[b][i][j] = rotated[i][j];
}
void block2Board()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = blocks[b][i][j];
}
void boardDelBlock()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = ' ';
}
int removeLine()
{
    int cleared = 0;
 
    for (int i = H - 2; i >= 1; i--)
    {
        bool full = true;
        for (int j = 1; j < W - 1; j++)  
            if (board[i][j] == ' ')
            {
                full = false;
                break;
            }
 
        if (full)
        {
            for (int k = i; k > 1; k--)
                for (int j = 1; j < W - 1; j++)
                    board[k][j] = board[k - 1][j];
 
            for (int j = 1; j < W - 1; j++)
                board[1][j] = ' ';
 
            cleared++;  
            i++;        
        }
    }
    return cleared;
}
void initBoard()
{
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}
void draw()
{
    system("cls");

    for (int i = 0; i < H; i++, cout << endl)
        for (int j = 0; j < W; j++)
            cout << board[i][j];
}

int main()
{
    srand(time(0));
    x = 5;
    y = 0;
    b = rand() % 7;
    initBoard();
    while (1)
    {
        boardDelBlock();
        if (kbhit())
        {
            char c = getch();
            if (c == 'a' && canMove(-1, 0))
                x--;
            if (c == 'd' && canMove(1, 0))
                x++;
            if (c == 'x' && canMove(0, 1))
                y++;
            if (c == 'w')
                rotate();
            if (c == 'q')
                break;
        }
        if (canMove(0, 1))
            y++;
        else
        {
            block2Board();
            if (removeLine() > 0)
            {
                speed -= SPEED_STEP;
                if (speed < MIN_SPEED)
                    speed = MIN_SPEED;
            }
            x = 5;
            y = 0;
            b = rand() % 7;
        }
        block2Board();
        draw();
        _sleep(speed);
    }
    return 0;
}
