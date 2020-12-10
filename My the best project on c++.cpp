#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

#define SPACE 32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77



struct Field {
    int x;
    int y;
    char show=' ';
};
struct Fruit {
    int x;
    int y;
    char show='$';
};

struct Snake {
    int x;
    int y;
    char show='0';
};

struct Tail {
    int x;
    int y;
    char show = 'o';
};

struct MyGame {
    Field* field;
    Fruit* fruit;
    Snake* snake;
    Tail* tail;
};

//struct Switcher {
//    int x;
//    int y;
//    char show='%';
//};

//struct MENU {
//    Field* ForMenu;
//    Switcher* switcher;
//};

bool Checker;
int Turn;
int Counter;
int TailLen;

MyGame*Create() {
    srand(time(NULL));

    MyGame* Game = new MyGame;
    Game->field = new Field;
    Game->fruit = new Fruit;
    Game->snake = new Snake;
    Game->tail = new Tail[30];

    Game->field->x = 40;
    Game->field->y = 20;

    Game->snake->x = Game->field->x / 2-1;
    Game->snake->y = Game->field->y / 2-1;

    Game->fruit->x = rand() % Game->field->x + 1;
    Game->fruit->y = rand() % Game->field->y + 1;

    return Game;
}

void score() {

}

void Show(MyGame* Game) {
    system("cls");
            
    for (int i = 0; i <= Game->field->x; i++)
        cout << "#";
    cout << endl;
    for (int j = 0; j < Game->field->y; j++) {
        for (int i = 0; i < Game->field->x; i++) {
            if (i == 0 or i == Game->field->x - 1)
                cout << "#";
            if (i == Game->snake->x and j == Game->snake->y)
                cout << Game->snake->show;
            else if (i == Game->fruit->x and j == Game->fruit->y)
                cout << Game->fruit->show;
            else {
                bool TailChecker = false;
                for (int k = 0; k < TailLen; k++) {
                    if (i == Game->tail[k].x and j == Game->tail[k].y) {
                        cout << Game->tail->show;
                        TailChecker = true;
                    }

                }
                if(!TailChecker)
                cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i <= Game->field->x; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << Counter;

}

void LogicTail(MyGame* Game);

void Move() {
    if (_kbhit()) {
        switch (_getch()) {

        case SPACE:
            Checker = true;
            break;

        case UP:
            Turn = 1;
            break;

        case DOWN:

            Turn = 2;
            break;

        case RIGHT:

            Turn = 3;
            break;

        case LEFT:

            Turn = 4;
            break;
        }
    }
}

void Logic(MyGame*Game) {
    Move();
    if (Game->snake->x == Game->fruit->x and Game->snake->y == Game->fruit->y) {
        Counter += 10;
        Game->fruit->x = rand() % 37 + 1;
        Game->fruit->y = rand() % 18 + 1;
        TailLen++;
    }
    if (Game->snake->x == -1 or Game->snake->y == -1 or Game->snake->x == Game->field->x-1 or Game->snake->y == Game->field->y)
        Checker = true;
    for (int i = 0; i < TailLen; i++) {
        if (Game->tail[i].x == Game->snake->x and Game->tail[i].y == Game->snake->y) {
            Checker = true;
        }
    }
    LogicTail(Game);
    

}

void LogicTail(MyGame* Game) {
    int Tailx, Taily, tmpy, tmpx;
    Tailx = Game->tail[0].x;
    Taily = Game->tail[0].y;
    Game->tail[0].x = Game->snake->x;
    Game->tail[0].y = Game->snake->y;
    for (int i = 1; i < TailLen; i++) {
        tmpx = Game->tail[i].x;
        tmpy = Game->tail[i].y;
        Game->tail[i].x = Tailx;
        Game->tail[i].y = Taily;
        Tailx = tmpx;
        Taily = tmpy;
    }
}

void Automove(MyGame*Game) {
    if (Turn == 1)
        Game->snake->y--;
    if (Turn == 2)
        Game->snake->y++;
    if (Turn == 3)
        Game->snake->x++;
    if (Turn == 4)
        Game->snake->x--;
}

//MENU*Setup(){
//     MENU* Menu = new MENU;
//     Menu->ForMenu = new Field;
//
//     Menu->ForMenu->x = 10;
//     Menu->ForMenu->y = 10;
//
//     Menu->switcher->x = 1;
//     Menu->switcher->y = 1;
//
//     for (int j = 0; j < Menu->ForMenu->y; j++) {
//         for (int i = 0; i < Menu->ForMenu->x; i++) {
//             if (i == Menu->switcher->x and j == Menu->switcher->y)
//                 cout << Menu->switcher->show;
//             if (i == 2 and j == 1)
//                 cout << "New Game";
//             if (i == 2 and j == 2)
//                 cout << "Exit";
//         }
//     }
//}



int main()
{

    MyGame* Game = Create();
    while (!Checker) {
        Show(Game);
        Logic(Game);
        Automove(Game);
    }
    system("cls");
}
