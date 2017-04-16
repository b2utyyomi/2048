
///效果不太好 能明显看出清屏的过程 因为我是使用空格代替要删掉的内容 它比system("cls");慢了好多
///但是我又不想把菜单清掉，
#include <stdio.h>
#include<windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
void menu();
void init(void);      /// 初始化数组跟赋值第一个随机二维数组元素
void draw(void);      /// 绘制4 * 4方格图
void play(void);      /// 控制移动方向
void to_up(void);     /// 向上移动
void to_down(void);  /// 像下移动
void to_left(void);   /// 向左移动
void to_right(void);  /// 向右移动
void add_number(void);  /// 加新的数
void gotoxy(HANDLE hOut, int x, int y);///移动光标到指定位置
void Game_Over(char c);///判断游戏是否结束，若结束，则输出最后分数
int a[4][4];
int empty_;
int score = 0;
int main(void) {
    system("color 0D");
    menu();
    init();
    draw();
    while(1)
    {
        play();
        Game_Over('a');
    }
    return 0;
}
void menu()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("*********************\n");
    printf("        2048        \n");
    printf("*********************\n");
    gotoxy(hout, 16+8, 0+5);
    printf("w/W for up, s/S for down\n");
    gotoxy(hout, 16+8, 0+6);
    printf("a/A for left, d/D for right\n");
    gotoxy(hout, 16+8, 0+7);
    printf("press q or Q to quit the game!\n");
    gotoxy(hout, 0, 0+3);
    SetConsoleTextAttribute(hout, FOREGROUND_INTENSITY | FOREGROUND_GREEN);

}
void gotoxy(HANDLE hOut, int x, int y)
{
     COORD pos;
     pos.X = x;  ///横坐标
     pos.Y = y;  ///纵坐标
     SetConsoleCursorPosition(hOut, pos);
}
void Game_Over(char c)
{
    if(empty_ == 0 || c == 'q')
    {
        system("cls");
        HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED);

        printf("Game Over!!!\n");
        printf("Your score is: %d", score);
        exit(0);
    }
}

void init() {
    int i, j;

    for(i = 0; i < 4; ++i)
        for(j = 0; j < 4; ++j)
            a[i][j] = 0;
    srand(time(0));
    i = rand() % 4;
    j = rand() % 4;
    a[i][j] = 2;
    empty_ = 15;
}

void draw() {
    int i, j;
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(hout, 0, 0+3);
    for(i = 0; i < 4; ++i) {          /// 一个方格由三根竖线组成
        for(j = 0; j < 4; ++j)     /// 第一排竖线 每个竖线之间占5个格
            printf("|    ");
        printf("|\n");

        for(j = 0; j < 4; ++j) {   /// 第二排竖线与数字
            if(a[i][j] == 0)
                printf("|    ");
            else
                printf("|%4d", a[i][j]);
        }
        printf("|\n");

        for(j = 0; j < 4; ++j)     /// 第三排竖线加底线
            printf("|____");
        printf("|\n");
    }
}
void cls()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=0; i<12; i++){
        for(int j=0; j<21; j++){
            gotoxy(hout, j, i+3);
            printf(" ");
        }
    }
}
void play() {
    int ch;
    ch = getch();
    switch(ch) {
        case 'w':    /// 向上移动
        case 'W':
            to_up();
            cls();
            add_number();
            draw();
            break;
        case 's':    /// 向下移动
        case 'S':
            to_down();
            cls();
            add_number();
            draw();
            break;
        case 'a':    /// 向左移动
        case 'A':
            to_left();
            cls();
            add_number();
            draw();
            break;
        case 'd':     /// 向右移动
        case 'D':
            to_right();
            cls();
            add_number();
            draw();
            break;
        case 'q':   /// 退出游戏
        case 'Q':
            Game_Over('q');
            break;
        default:
            printf("\nwrong type!!!\n\n");
            printf("please type :\n");
            printf("w/s/a/d or W/S/A/D\n");
            break;
    }
}

void to_up() {
    int x, y, i;

    for(y = 0; y < 4; ++y) {     /// 从下向上合并相同的方块
        for(x = 0; x < 4; ++x) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = x + 1; i < 4; ++i) {
                    if(a[i][y] == 0)
                        ;
                    else if(a[x][y] == a[i][y]) {
                        score += 10;
                        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
                        gotoxy(hout, 16+8, 0+8);
                        printf("score: %d", score);
                        a[x][y] += a[i][y];
                        a[i][y] = 0;
                        ++empty_;
                        x = i;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }

    for(y = 0; y < 4; ++y)    /// 向上移动箱子
        for(x = 0; x < 4; ++x) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = x; (i > 0) && (a[i - 1][y] == 0); --i) {///一行一行往上移，没到第一行和上一行为空是前提
                    a[i - 1][y] = a[i][y];///想过直接移到最上面， 但是需要判断上面相邻的一行是否为空，空才能移上去
                    a[i][y] = 0;
                }
            }
        }
}

void to_down() {
    int x, y, i;

    for(y = 0; y < 4; ++y)  /// 向下合并相同的方格
        for(x = 3; x >= 0; --x) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = x - 1; i >= 0; --i) {
                    if(a[i][y] == 0)
                        ;
                    else if(a[x][y] == a[i][y]) {
                        score += 10;
                        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
                        gotoxy(hout, 16+8, 0+8);
                        printf("score: %d", score);
                        a[x][y] += a[i][y];
                        a[i][y] = 0;
                        ++empty_;
                        x = i;
                        break;
                    }
                    else
                        break;
                }
            }
        }

    for(y = 0; y < 4; ++y)  /// 向下移动方格
        for(x = 3; x >= 0; --x) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = x; (i < 3) && (a[i + 1][y] == 0); ++i) {
                    a[i + 1][y] = a[i][y];
                    a[i][y] = 0;
                }
            }
        }
}

void to_left() {
    int x, y, i;

    for(x = 0; x < 4; ++x)   /// 向左合并相同的方格
        for(y = 0; y < 4; ++y) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = y + 1; i < 4; ++i) {
                    if(a[x][i] == 0)
                        ;
                    else if(a[x][y] == a[x][i]) {
                        score += 10;
                        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
                        gotoxy(hout, 16+8, 0+8);
                        printf("score: %d", score);
                        a[x][y] += a[x][i];
                        a[x][i] = 0;
                        ++empty_;
                        y = i;
                        break;
                    }
                    else
                        break;
                }
            }
        }

    for(x = 0; x < 4; ++x)  /// 向左移动方格
        for(y = 0; y < 4; ++y) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = y; (i > 0) && (a[x][i - 1] == 0); --i) {
                    a[x][i - 1] = a[x][i];
                    a[x][i] = 0;
                }
            }
        }
}

void to_right() {
    int x, y, i;

    for(x = 0; x < 4; ++x)  /// 向右合并相同的方格
        for(y = 3; y >= 0; --y) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = y - 1; i >= 0; --i) {
                    if(a[x][i] == 0)
                        ;
                    else if(a[x][y] == a[x][i]) {
                        score += 10;
                        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
                        gotoxy(hout, 16+8, 0+8);
                        printf("score: %d", score);
                        a[x][y] += a[x][i];
                        a[x][i] = 0;
                        ++empty_;
                        y = i;
                        break;
                    }
                    else
                        break;
                }
            }
        }

    for(x = 0; x < 4; ++x)   /// 向右移动方格
        for(y = 3; y >= 0; --y) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = y; (i < 3) && (a[x][i + 1] == 0); ++i) {
                    a[x][i + 1] = a[x][i];
                    a[x][i] = 0;
                }
            }
        }
}

void add_number() {
    int temp, number;
    int x, y;

    if(empty_ > 0) {     /// 找出空格
        srand(time(0));
        do {
            x = rand() % 4;
            y = rand() % 4;
        } while(a[x][y] != 0);

        number = rand();
        temp = number % 2;

        if(temp == 1) {  /// 判断是生成数字2，还是数字4
            a[x][y] = 2;
            --empty_;
        }
        if(temp == 0) {
            a[x][y] = 4;
            --empty_;
        }
    }

}
