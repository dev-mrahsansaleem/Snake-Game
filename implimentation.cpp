#include<iostream>
#include<conio.h>
#include<Windows.h>
#include "cNode.h"
#include "cSnakeGame.h"
using namespace std;
node::node()
{
	this->x = 0;
	this->y = 0;
	this->value = '*';
	this->next = NULL;
	this->prev = NULL;
}
node::node(int x, int y)
{
	this->x = x;
	this->y = y;
	this->value = '*';
	this->next = NULL;
	this->prev = NULL;
}
snakeGame::snakeGame()
{
	//Initialize snake
	this->head = new node();
	this->tail = new node();
	//Initialize fruits on grid
}

void snakeGame::createFruit()
{
	this->fruitX = rand() % (this->width - 2);
	this->fruitY = rand() % (this->height - 2);
}

void snakeGame::setup()
{
	this->gameOver = false;
	this->dir = STOP;
	//center position
	this->head->x = this->width / 2;
	this->head->y = this->height / 2;
	//fruit position 1 for now
	this->createFruit();
	//score
	this->score = 0;
}
void snakeGame::print()
{
	system("CLS");
	for (int i = 0; i < this->width; i++)
		cout << "=";	//top border
	cout << endl;

	for (int i = 0; i <this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (j == 0 || j == this->width - 1)
				cout << "|";
			if (i == this->head->y && j == this->head->x)
				cout << this->head->value;
			else if (i == this->fruitY && j == this->fruitX)
			{
				cout << "@";

			}
			else
				cout << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < this->width; i++)
		cout << "=";	//bellow border
	cout << endl;
}

void snakeGame::input() 
{
	if (_kbhit())
	{
		this->pressedKey = _getch(); // to ignore key press
		this->pressedKey = _getch(); // to catch key release
		if (this->pressedKey == 72)//up key
		{
			this->dir = UP;
		}
		else if (this->pressedKey == 80)//down key
		{
			this->dir = DOWN;
		}
		else if (this->pressedKey == 75)//left key
		{
			this->dir = LEFT;
		}
		else if (this->pressedKey == 77)//right key
		{
			this->dir = RIGHT;
		}
		else
		{
			gameOver = true;
		}
	}
}
void snakeGame::onCollision()
{
	//if touch walls game end
	if (this->head->x<0 || this->head->x>this->width || this->head->y<0 || this->head->y>this->height)
		this->gameOver = true;
	if (this->head->x == this->fruitX && this->head->y == fruitY)
	{
		score += 10;
		//fruit position 1 for now
		this->createFruit();
	}

}
void snakeGame::move() 
{
	if (this->dir == LEFT)
	{
		this->head->x--;
	}
	else if (this->dir == RIGHT)
	{
		this->head->x++;
	}
	else if (this->dir == UP)
	{
		this->head->y--;
	}
	else if (this->dir == DOWN)
	{
		this->head->y++;
	}
	this->onCollision();
}

void snakeGame::startGame()
{
	this->setup();
	while (!gameOver)
	{
		this->print();
		this->input();
		this->move();
		Sleep(10);
		cout << "score: " << this->score << endl;
	}
}