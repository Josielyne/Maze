#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;
struct position
{
	int x, y;//coordinates stored
};
class Stack//stack used to find exit
{
public:
	int top;//declare variables
	position arr[1000];//array storing coordinates for needed steps to solve

	Stack()//constructor
	{
		top = -1;//initialize variables
		arr[1000] = { 0 };

	}

	bool isFull()//checks if stack is full
	{
		if (top == 1000 - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isEmpty()//checks if stack is empty
	{
		if (top == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	position pop()//removes top element of stack if not empty
	{
		if (!isEmpty())
		{
		
			return arr[--top];
			
		}
		else
		{
			//do nothing
		}
	}

	void push(position p)//adds element to top of stack if not full
	{
		if (!isFull())
		{
			arr[top] = p;
			
			top++;
		}
		else
		{
			//do nothing
		}
	}
};
class Game//class for game functions
{
public:
	//declare variables
	string cursorDisplay;//character display for cursor
	Stack myStack;//copy of stack
	int xmouse, ymouse;//coordinates for pathway of mouse
	int colors[9] = { 9,10,11,12,13,14,15,5,6 };//array to randomize color
	//size of maze
	static const int ROWS = 30;
	static const int COLUMNS = 100;
	//maze design
	int maze[ROWS][COLUMNS] =
	{
		{ 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 0,0,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1 },
		{ 1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,0,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1 },
		{ 1,0,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1 },
		{ 1,0,1,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,0,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1 },
		{ 1,0,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,0,0,1,0,1 },
		{ 1,0,1,1,1,1,0,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,0,1 },
		{ 1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1 },
		{ 1,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,0,1,0,0,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1,0,1 },
		{ 1,1,1,1,1,0,0,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,0,1,0,1,0,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,0,1 },
		{ 1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,0,1 },
		{ 1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,0,1 },
		{ 1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,1,1,1,1,0,1,1,0,1,1,0,1,0,1,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,0,1,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1 },
		{ 1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,1,0,1,1,0,0,0,1,0,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1 },
		{ 1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1 },
		{ 1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,1,0,1,0,1,1,0,1,1,1,0,1,0,1 },
		{ 1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,0,1,0,1,1,0,0,1,1,0,1,1,1 },
		{ 1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,0,0,0,1,1,0,0,1,0,1,0,0,0,1,0,1,1,0,1,0,1,1,1,0,1,1,0,0,0,1 },
		{ 1,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1,0,1,1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,1,1,1,1,0,1 },
		{ 1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,0,1,0,1,0,1,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,0,1,1,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,1,0,1,0,1,1,1,1,1,0,1,1,0,1 },
		{ 1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,3 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3 },

	};

	Game()//constructor
	{
		//initialize variables
		xmouse = 2;//starting position of mouse
		ymouse = 2;
		cursorDisplay = char(175);//sets cursor to display certain character
	

	}

	void gotoxy(int column, int line)//gotoxy function to move to needed coordinates
	{
		COORD coord;
		coord.X = column;
		coord.Y = line;
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			coord
		);
	}

	void displayMaze()//shows maze design with color
	{

		//system("cls");
		for (int row = 0; row < ROWS;row++)//goes through 2D maze and displays it
		{
			//1= wall, 0=empty space, 2 = mine, 3 = exit, 4 = visited space
			for (int col = 0; col < COLUMNS;col++)
			{

				if (maze[row][col] == 0)//prints empty space for 0
				{
					cout << " ";
				}
				else if (maze[row][col] == 1)//wall
				{

					int clr = 0;

					for (int i = 0; i < 8;i++)//randomizes color for the walls of the maze, making it rainbow
					{

						clr = rand() % 9;
					}
					if (clr == 0)//if randomizer gives 0, set the color to default color green 
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					}
					else//else color the walls with color corresponding to randomized number
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
					}
					cout << char(177);//character for walls
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			
				}
				else if (maze[row][col] == 3)//displays the exit with ceratin character
				{
					cout << char(206);
				}
				else if (maze[row][col] == 2)//displays mines with certain character
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//mines are red
					cout << char(237);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				}
				else
				{
					//do nothing
				}
			}
			cout << endl;
		}
	}
	void endFound()//function that executes when mouse gets to end
		{
		//displays message in middle of maze
		gotoxy(38, 14);
		cout << "|------------------------|";
		gotoxy(38, 15);
		cout << "|You Found the Exit!! ^.^|";
		gotoxy(38, 16);
		cout << "|------------------------|";
		gotoxy(0, 31);
		system("pause");//pauses the program
		}
	void bombHit(int hx, int hy)//function that executes when mouse hits a mine
	{
		cursorDisplay = " ";//when the mouse dies, it hides it
		cout << cursorDisplay << endl;
		
		//displays a dismantling effect when the mouse hits the bomb
		gotoxy(hx-1, hy);
		cout << char(212);
		gotoxy(hx, hy + 1);
		cout << char(211);
		gotoxy(hx, hy - 1);
		gotoxy(hx + 1, hy);
		cout << char(187);
		cout << char(210);
		gotoxy(35, 14);
		//displays message in middle of maze
		cout << "|---------------------------|";
		gotoxy(35, 15);
		cout << "|You Hit A Mine :( Game Over|";
		gotoxy(35, 16);
		cout << "|---------------------------|";
		gotoxy(0, 31);
		system("pause");//pauses the program

	}
	void DisplayMouse(bool flag)//displays the cursor
	{
		gotoxy(xmouse, ymouse);//moves cursor to mouse pathway
		if (flag)//display mouse if flag is true
		{
			cout << cursorDisplay << endl;
		}
		else
		{
			cout << " " << endl;//display empty space if false
		}

	}
	
	void MoveMouse()//function that moves mouse through maze
	{
		

		//R
		if (maze[ymouse][xmouse + 1] == 0 && maze[ymouse][xmouse+1] !=3 && maze[ymouse][xmouse+1] !=2)//if the space to the right is empty, not the exit, and not a mine then move there
		{
			position p;//push mouse's coordinates to stack
			p.x = xmouse;
			p.y = ymouse;
			myStack.push(p);
			xmouse++; //move the mouse to the right
			maze[ymouse][xmouse - 1] = 4;//mark the previous location as visited 
		
		}
		//D
		else if (maze[ymouse+1][xmouse] == 0 && maze[ymouse+1][xmouse] !=3 && maze[ymouse+1][xmouse] !=2 )//if space below is empty, not the exit, and not a mine then move there
		{
			
			position p;//push mouse's coordinates to stack
			p.x = xmouse;
			p.y = ymouse;
			myStack.push(p);
			ymouse++;//move mouse down
			maze[ymouse - 1][xmouse] = 4;//mark the previous location as visited
		}

		//L
		else if (maze[ymouse][xmouse - 1] == 0 && maze[ymouse][xmouse-1] != 3 && maze[ymouse][xmouse-1]!=2)//if space to the left is empty, not the exit, and not a mine then move there
		{
			position p;//push the mouse's coordinates to stack
			p.x = xmouse;
			p.y = ymouse;
			myStack.push(p);
			xmouse--;//move mouse left
			maze[ymouse][xmouse + 1] = 4;//mark the previous location as visited
	
		}
		//U
		else if (maze[ymouse - 1][xmouse] == 0 && maze[ymouse-1][xmouse]!=3 && maze[ymouse-1][xmouse] !=2)//if space above is empty, not the exit, and not a mine then move there
		{
		
			position p;//push the mouse's coordinates to stack
			p.x = xmouse;
			p.y = ymouse;
			myStack.push(p);
			ymouse--;//move mouse up
			maze[ymouse + 1][xmouse] == 4;//mark the previous location as visited
		}
		
		else if (maze[ymouse][xmouse+1] == 3 || maze[ymouse][xmouse - 1] == 3 || maze[ymouse - 1][xmouse] == 3 || maze[ymouse + 1][xmouse] == 3)
		{
			//if mouse hits the end of maze, call on the end function
			endFound();
		}
		else if (maze[ymouse][xmouse + 1] == 2 || maze[ymouse][xmouse - 1] == 2 || maze[ymouse - 1][xmouse] == 2 || maze[ymouse + 1][xmouse] == 2)
		{
			//if mouse hits a mine, send its coordinates to hit function and call on it
			int currCoordx = xmouse;
			int currCoordy = ymouse;
			bombHit(currCoordx,currCoordy);
		}
		
		else //mouse gets to a dead end
		{
			maze[ymouse][xmouse] = 1;//turn current position to a wall so mouse won't go back and mouse moves to another space
			position p;//pop position from stack
			p = myStack.pop();
			xmouse = p.x;
			ymouse = p.y;

		}
		
		

	}
};

int main()//driver of class
{
	system("color 0A");//changes default color to green
	Game t;//creates object of class Game
	t.displayMaze();//displays the maze
	bool flag = false;//initiates flag that signals whether cursor should be displayed 

	while (1)//while loop to keep the mouse going until exit is found
	{

		t.DisplayMouse(true);//show cursor
		Sleep(150);//speed of mouse
		t.DisplayMouse(false);//hide cursor from previous location
		t.MoveMouse();//move the mouse

	}



	return 0;
}