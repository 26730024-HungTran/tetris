#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
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
void removeLine()
{
    // duyệt từ đáy lên, bỏ qua viền trên (hàng 0) và viền dưới (hàng H-1)
    for (int i = H - 2; i >= 1; i--)
    {
        bool full = true;
        for (int j = 1; j < W - 1; j++)  // bỏ 2 viền trái/phải
            if (board[i][j] == ' ')
            {
                full = false;
                break;
            }

        if (full)
        {
            // dồn tất cả các hàng phía trên xuống 1 dòng
            for (int k = i; k > 1; k--)
                for (int j = 1; j < W - 1; j++)
                    board[k][j] = board[k - 1][j];

            // hàng trên cùng (hàng 1) thành trống
            for (int j = 1; j < W - 1; j++)
                board[1][j] = ' ';

            i++;  // kiểm tra lại chính hàng i, vì nó vừa nhận nội dung của hàng trên
        }
    }
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

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            char c = board[i][j];

            if (c == '#')
            {
                SetConsoleTextAttribute(hConsole, 15);
                cout << "##";
            }
            else if (c == 'I')
            {
                SetConsoleTextAttribute(hConsole, 11);
                cout << "██";
            }
            else if (c == 'O')
            {
                SetConsoleTextAttribute(hConsole, 14);
                cout << "██";
            }
            else if (c == 'T')
            {
                SetConsoleTextAttribute(hConsole, 13);
                cout << "██";
            }
            else if (c == 'S')
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << "██";
            }
            else if (c == 'Z')
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "██";
            }
            else if (c == 'J')
            {
                SetConsoleTextAttribute(hConsole, 9);
                cout << "██";
            }
            else if (c == 'L')
            {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "██";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 0);
                cout << "  ";
            }
        }

        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 7);
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
            removeLine();
            x = 5;
            y = 0;
            b = rand() % 7;
        }
        block2Board();
        draw();
        _sleep(500);
    }
    return 0;
}
