#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <cstdio>
#include <string>
#include <fstream>
#include <windows.h>

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77

using namespace std;

const int height = 21;
const int width = 21;

const int STOP = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4;

void Instruction(ofstream& fout) {
    fout << "This is the instraction of the game!" << endl;
    fout << "1.The map, fruit(F), fence(#), snake(letter) are created." << endl;
    fout << "2.If you eat fruits, your snake will grow and the game score will increase." << endl;
    fout << "3.You don't go to the fence or eat your tail, so you will lose." << endl;
    fout << "4.If your snake fill all size of freeground(where dont situate # or F), you will win!" << endl;
}

void Introdution() {
    cout << "Hello, now you will play in Snake Game!" << endl;
    cout << "But after that you must create personal snake with own characteristics:" << endl;
}

void Colors() {
    cout << "Black" << endl;
    cout << "Blue" << endl;
    cout << "Green" << endl;
    cout << "Cyan" << endl;
    cout << "Red" << endl;
    cout << "Magenta" << endl;
    cout << "Yellow" << endl;
    cout << "White" << endl;
}

int converColorInNumber(string color) {
    for (int i = 0; i < color.size(); i++) {
        if (color[i] >= 65 && color[i] <= 90) {
            color[i] += 32;
            continue;
        }

        if (color[i] < 97 && color[i] > 122) {
            return -1;
        }
    }

    if (color == "black") {
        return 0;
    }

    if (color == "blue") {
        return 1;
    }

    if (color == "green") {
        return 2;
    }

    if (color == "cyan") {
        return 3;
    }

    if (color == "red") {
        return 4;
    }

    if (color == "magenta") {
        return 5;
    }

    if (color == "yellow") {
        return 14;
    }

    if (color == "white") {
        return 15;
    }
    return -1;
}

int getColor() {
    string paint;

    Introdution();
    cout << "All possible colors:" << endl;
    Colors();
    cout << "Color: ";
    cin >> paint;

    while (converColorInNumber(paint) == -1)
    {
        cout << "You enter wrong color, please repeat!" << endl;
        cout << "Color: ";
        cin >> paint;
    }
    return converColorInNumber(paint);
}

int formulaFreeCube() {
    return (height * width) - (2 * width) - (2 * (height - 2));
}

int* tailX = new int[formulaFreeCube()];
int* tailY = new int[formulaFreeCube()];

int fruitX, fruitY;

int score = 0;

class Animal {
public:
    Animal() {
        name = "";
        kind = "";
        form = "";
    }

    void setName(string name) {
        this->name = name;
    }

    void setForm(string form) {
        this->form = form;
    }

    void setKind(string kind) {
        this->kind = kind;
    }

    string getName() {
        return name;
    }

    string getKind() {
        return kind;
    }

    string getForm() {
        return form;
    }

private:
    string name;
    string kind;
    string form;
};

class Snake { //base class
public:
    void setHeadSize(string headSize) {
        this->headSize = headSize;
    }

    string getHeadSize() {
        return headSize;
    }

    int color = 0;

    Snake() {
        headSize = "";
    }
private:
    string headSize;
};

class Tail {
public:
    Tail() {
        x = 0;
        y = 0;
        previousX = 0;
        previousY = 0;
        previous2X = 0;
        previous2Y = 0;
        tailSize = "";
    }

    virtual int getTailX() {
        return x;
    }

    virtual int getTailY() {
        return y;
    }

    int getPreviousX() {
        return previousX;
    }

    int getPreviousY() {
        return previousY;
    }

    int getPrevious2X() {
        return previous2X;
    }

    int getPrevious2Y() {
        return previous2Y;
    }

    int getNTail() {
        return nTail;
    }

    void setPreviousX(int previousX) {
        this->previousX = previousX;
    }

    void setPreviousY(int previousY) {
        this->previousY = previousY;
    }

    void setPrevious2X(int previous2X) {
        this->previous2X = previous2X;
    }

    void setPrevious2Y(int previous2Y) {
        this->previous2Y = previous2Y;
    }

    void setTailX(int x) {
        this->x = x;
    }

    void setTailY(int y) {
        this->y = y;
    }

    void getNTail(int nTail) {
        this->nTail = nTail;
    }

    void setTailSize(string tailSize) {
        this->tailSize = tailSize;
    }

    string getTailSize() {
        return tailSize;
    }
private:
    int x, y;
    int previousX, previousY;
    int previous2X, previous2Y;
    int nTail = 1;
    string tailSize;
};

class MySnake : public Animal, public Snake, public Tail {
public:
    virtual int getSnakeX() {
        return x;
    }

    virtual int getSnakeY() {
        return y;
    }

    char getHeadLetter() {
        return headLetter;
    }

    char getTailLetter() {
        return tailLetter;
    }

    void setSnakeX(int x) {
        this->x = x;
    }

    void setSnakeY(int y) {
        this->y = y;
    }

    void setHeadLetter(char headLetter) {
        this->headLetter = headLetter;
    }

    void setTailLetter(char tailLetter) {
        this->tailLetter = tailLetter;
    }

    MySnake() {
        x = 0;
        y = 0;
    }
private:
    int x, y;
    char headLetter;
    char tailLetter;
};

MySnake ms;

char headSnake, tailSnake;

void createHeadSnake() {
    if (ms.getHeadSize() == "big")
    {
        if (headSnake >= 97 && headSnake <= 122)
        {
            headSnake -= 32;
        }
    }

    if (ms.getHeadSize() == "small")
    {
        if (headSnake >= 65 && headSnake <= 90)
        {
            headSnake += 32;
        }
    }
}

void createTailSnake() {
    if (ms.getTailSize() == "big")
    {
        if (tailSnake >= 97 && tailSnake <= 122)
        {
            tailSnake -= 32;
        }
    }

    if (ms.getTailSize() == "small")
    {
        if (tailSnake >= 65 && tailSnake <= 90)
        {
            tailSnake += 32;
        }
    }
}

void paintHeadAndTail() {
    char headLetter, tailLetter;
    string sizeSnakeHead, sizeSnakeTail;

    cout << "Enter a letter wich will be a head of snake: ";
    cin >> headLetter;

    if ((headLetter >= 65 && headLetter <= 90) || (headLetter >= 97 && headLetter <= 122))
    {
        cout << "Enter a size(big or small) of snake's head: ";
        cin >> sizeSnakeHead;

        while (sizeSnakeHead != "small" && sizeSnakeHead != "big")
        {
            cout << "Enter big or small, please: ";
            cin >> sizeSnakeHead;
        }
        ms.setHeadSize(sizeSnakeHead);
    }
    ms.setHeadLetter(headLetter);

    cout << "Enter a letter wich will be a tail of snake: ";
    cin >> tailLetter;

    if ((headLetter >= 65 && headLetter <= 90) || (headLetter >= 97 && headLetter <= 122))
    {
        cout << "Enter a size(big or small) of snake's tail: ";
        cin >> sizeSnakeTail;

        while (sizeSnakeTail != "small" && sizeSnakeTail != "big")
        {
            cout << "Enter big or small, please: ";
            cin >> sizeSnakeTail;
        }

        ms.setTailSize(sizeSnakeTail);
    }
    ms.setTailLetter(tailLetter);

    headSnake = ms.getHeadLetter();
    tailSnake = ms.getTailLetter();

    createHeadSnake();
    createTailSnake();
}

void fillProfile() {
    string name, kind, form;

    cout << "Enter a name of your snake: ";
    cin >> name;
    ms.setName(name);

    cout << "Enter a kind of your snake: ";
    cin >> kind;
    ms.setKind(kind);

    cout << "Enter a form of your snake: ";
    cin >> form;
    ms.setForm(form);
}

int movement;
bool gameOver;

void buildTail() {
    ms.setPreviousX(tailX[0]);
    ms.setPreviousY(tailY[0]);
    tailX[0] = ms.getSnakeX();
    tailY[0] = ms.getSnakeY();
    for (int i = 0; i < ms.getNTail(); i++)
    {
        ms.setPrevious2X(tailX[i]);
        ms.setPrevious2Y(tailY[i]);
        tailX[i] = ms.getPreviousX();
        tailY[i] = ms.getPreviousY();
        ms.setPreviousX(ms.getPrevious2X());
        ms.setPreviousY(ms.getPrevious2Y());
    }
}

bool isEatTail() {
    for (int i = 0; i < ms.getNTail(); i++)
    {
        if (tailX[i] == ms.getSnakeX() && tailY[i] == ms.getSnakeY())
            return true;
    }
    return false;
}

bool isTail(int x, int y) {
    for (int i = 0; i < ms.getNTail(); i++)
    {
        if (x == tailX[i] && y == tailY[i])
            return true;
    }
    return false;
}

void Setup() {
    gameOver = false;
    movement = STOP;
}

void Draw(int color) {
    system("cls");
    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hwnd, color | FOREGROUND_INTENSITY);

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            if (i == 1 || i == height || j == 1 || j == width)
                cout << "#";
            else if (i == ms.getSnakeY() && j == ms.getSnakeX())
                cout << headSnake;
            else if (j == fruitX && i == fruitY)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < ms.getNTail(); k++)
                {
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        cout << tailSnake;
                    }
                }

                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    cout << "Score is: " << score << endl;
}

void Input() {
    int KeyStroke = _getch();

    if (KeyStroke == 224)
    {
        KeyStroke = _getch();
        switch (KeyStroke)
        {
        case UP_ARROW: movement = UP;
            break;
        case DOWN_ARROW: movement = DOWN;
            break;
        case LEFT_ARROW: movement = LEFT;
            break;
        case RIGHT_ARROW: movement = RIGHT;
            break;
        }
    }

    else
    {
        switch (KeyStroke)
        {
        case 'w': movement = UP;
            break;
        case 's': movement = DOWN;
            break;
        case 'a': movement = LEFT;
            break;
        case 'd': movement = RIGHT;
            break;
        case 'x': gameOver = true;
            break;
        }
    }
}

void Logic() {
    buildTail();
    int number;
    switch (movement)
    {
    case UP: number = ms.getSnakeY() - 1;
        ms.setSnakeY(number);
        break;
    case DOWN: number = ms.getSnakeY() + 1;
        ms.setSnakeY(number);
        break;
    case LEFT: number = ms.getSnakeX() - 1;
        ms.setSnakeX(number);
        break;
    case RIGHT: number = ms.getSnakeX() + 1;
        ms.setSnakeX(number);
        break;
    }

    if (ms.getSnakeX() == 1 || ms.getSnakeX() == width || ms.getSnakeY() == 1 || ms.getSnakeY() == height)
        gameOver = true;

    if (isEatTail())
        gameOver = true;

    if (ms.getSnakeX() == fruitX && ms.getSnakeY() == fruitY)
    {
        ms.getNTail(ms.getNTail() + 1);
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;

        while (fruitX == 1 || fruitX == width || fruitX == 0)
            fruitX = rand() % width;
        while (fruitY == 1 || fruitY == height || fruitY == 0)
            fruitY = rand() % width;
        while (isTail(fruitX, fruitY) || (fruitX == ms.getSnakeX() && fruitY == ms.getSnakeY()))
        {
            fruitX = rand() % width;
            fruitY = rand() % height;
            while (fruitX == 1 || fruitX == width || fruitX == 0)
                fruitX = rand() % width;
            while (fruitY == 1 || fruitY == height || fruitY == 0)
                fruitY = rand() % width;
        }
    }
}

int main()
{
    ofstream fout;
    string path = "instruction.txt";

    int color;

    fout.open(path);

    Instruction(fout);
    color = getColor();

    paintHeadAndTail();

    fillProfile();

    srand(time(0));
    fruitX = rand() % width;
    fruitY = rand() % height;

    while (fruitX == 1 || fruitX == width || fruitX == 0)
        fruitX = rand() % width;
    while (fruitY == 1 || fruitY == height || fruitY == 0)
        fruitY = rand() % width;

    ms.setSnakeX(width / 2 + 1);
    ms.setSnakeY(height / 2 + 1);

    while (!gameOver)
    {
        Setup();
        Draw(color);
        Input();
        Logic();
    }

    cout << "The name is - " << ms.getName() << endl;
    cout << "The form is - " << ms.getForm() << endl;
    cout << "The kind is - " << ms.getKind() << endl;

    if (score == formulaFreeCube())
    {
        cout << "You win!" << endl;
        int u = 0;
        while (u < 3)
        {
            cout << ".";
            u++;
            Sleep(500);
        }
        cout << endl;
    }

    else
    {
        cout << "You lose!" << endl;
    }

    fout.close();
    return 0;
}
