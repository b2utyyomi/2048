
///Ч����̫�� �����Կ��������Ĺ��� ��Ϊ����ʹ�ÿո����Ҫɾ�������� ����system("cls");���˺ö�
///�������ֲ���Ѳ˵������
#include <stdio.h>
#include<windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
void menu();
void init(void);      /// ��ʼ���������ֵ��һ�������ά����Ԫ��
void draw(void);      /// ����4 * 4����ͼ
void play(void);      /// �����ƶ�����
void to_up(void);     /// �����ƶ�
void to_down(void);  /// �����ƶ�
void to_left(void);   /// �����ƶ�
void to_right(void);  /// �����ƶ�
void add_number(void);  /// ���µ���
void gotoxy(HANDLE hOut, int x, int y);///�ƶ���굽ָ��λ��
void Game_Over(char c);///�ж���Ϸ�Ƿ�������������������������
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
     pos.X = x;  ///������
     pos.Y = y;  ///������
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
    for(i = 0; i < 4; ++i) {          /// һ�������������������
        for(j = 0; j < 4; ++j)     /// ��һ������ ÿ������֮��ռ5����
            printf("|    ");
        printf("|\n");

        for(j = 0; j < 4; ++j) {   /// �ڶ�������������
            if(a[i][j] == 0)
                printf("|    ");
            else
                printf("|%4d", a[i][j]);
        }
        printf("|\n");

        for(j = 0; j < 4; ++j)     /// ���������߼ӵ���
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
        case 'w':    /// �����ƶ�
        case 'W':
            to_up();
            cls();
            add_number();
            draw();
            break;
        case 's':    /// �����ƶ�
        case 'S':
            to_down();
            cls();
            add_number();
            draw();
            break;
        case 'a':    /// �����ƶ�
        case 'A':
            to_left();
            cls();
            add_number();
            draw();
            break;
        case 'd':     /// �����ƶ�
        case 'D':
            to_right();
            cls();
            add_number();
            draw();
            break;
        case 'q':   /// �˳���Ϸ
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

    for(y = 0; y < 4; ++y) {     /// �������Ϻϲ���ͬ�ķ���
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

    for(y = 0; y < 4; ++y)    /// �����ƶ�����
        for(x = 0; x < 4; ++x) {
            if(a[x][y] == 0)
                ;
            else {
                for(i = x; (i > 0) && (a[i - 1][y] == 0); --i) {///һ��һ�������ƣ�û����һ�к���һ��Ϊ����ǰ��
                    a[i - 1][y] = a[i][y];///���ֱ���Ƶ������棬 ������Ҫ�ж��������ڵ�һ���Ƿ�Ϊ�գ��ղ�������ȥ
                    a[i][y] = 0;
                }
            }
        }
}

void to_down() {
    int x, y, i;

    for(y = 0; y < 4; ++y)  /// ���ºϲ���ͬ�ķ���
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

    for(y = 0; y < 4; ++y)  /// �����ƶ�����
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

    for(x = 0; x < 4; ++x)   /// ����ϲ���ͬ�ķ���
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

    for(x = 0; x < 4; ++x)  /// �����ƶ�����
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

    for(x = 0; x < 4; ++x)  /// ���Һϲ���ͬ�ķ���
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

    for(x = 0; x < 4; ++x)   /// �����ƶ�����
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

    if(empty_ > 0) {     /// �ҳ��ո�
        srand(time(0));
        do {
            x = rand() % 4;
            y = rand() % 4;
        } while(a[x][y] != 0);

        number = rand();
        temp = number % 2;

        if(temp == 1) {  /// �ж�����������2����������4
            a[x][y] = 2;
            --empty_;
        }
        if(temp == 0) {
            a[x][y] = 4;
            --empty_;
        }
    }

}
