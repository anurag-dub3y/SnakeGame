#include <iostream>
#include <windows.h>
using namespace std;


//Checking OS and include necessary libraries
#ifdef _WIN32
    //code for Windows (32-bit and 64-bit, this part is common)
    #include <conio.h>
    #define CLEARSCREEN system("cls")
    #define CHECKKEY _kbhit()
    #define NBGETCHAR getch()

#elif __APPLE__
    //code for mac
    #define CLEARSCREEN system("clear")
    #define CHECKKEY 
    #define NBGETCHAR 

#elif __linux__
    //code for linux
    #define CLEARSCREEN system("clear")
    #define CHECKKEY 
    #define NBGETCHAR 

#else
#   error "Unknown compiler"
#endif


// Global Variables
bool endgame;
const int wid = 20;
const int len = 20;
int x, y, X, Y, points;
int tailX[100], tailY[100];
int nTail;
enum directions { STOP = 0, LEFT, RIGHT, UP, DOWN};
directions dir;

// DIRECTION KEYS
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77



void initialize()
{
	endgame = false;
	dir = STOP;
	x = wid / 2;
	y = len / 2;
	X = rand() % wid;
	Y = rand() % len;
	points = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < wid+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < wid; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == Y && j == X)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
				

			if (j == wid - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < wid+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << points << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case KEY_LEFT:
			dir = LEFT;
			break;
		case KEY_RIGHT:
			dir = RIGHT;
			break;
		case KEY_UP:
			dir = UP;
			break;
		case KEY_DOWN:
			dir = DOWN;
			break;
		case 'x':
			endgame = true;
			break;
		}
	}
}

void idea()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
        swap(prevX,tailX[i]);
        swap(prevY,tailY[i]);
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > wid || x < 0 || y > len || y < 0)
	//	endgame = true;
	if (x >= wid) x = 0; else if (x < 0) x = wid - 1;
	if (y >= len) y = 0; else if (y < 0) y = len - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			endgame = true;

	if (x == X && y == Y)
	{
		points += 10;
		X = rand() % wid;
		Y = rand() % len;
		nTail++;
	}
}
int main()
{
	initialize();
	while (!endgame)
	{
		Draw();
		Input();
		idea();
		Sleep(10); //sleep(10);
	}
	return 0;
}
