#include<iostream>
#include "cSnakeGame.h"
using namespace std;
int main()
{
	snakeGame<int,char> myGame;
	myGame.startGame();
	system("pause");
}