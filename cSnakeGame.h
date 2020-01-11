#include<iostream>
#include<conio.h>
#include<utility>
#include<Windows.h>
using namespace std;
template<class T,class C>
class node
{
public:
	T x;
	T y;
	C value;
	node<T,C>* next;
	node<T,C>* prev;

	node(T x, T y, C value, node* next = nullptr, node* prev = nullptr)
	{
		this->x = x;
		this->y = y;
		this->value = value;
		this->next = next;
		this->prev = prev;
	}
};
template<class T, class C>
class snakeGame
{
public:
	//head and tail of snake
	node<T,C> *head;
	node<T,C> *tail;

	//walls of 20x20
	const int width = 30; 
	const int height = 20;

	bool gameOver;
	int pressedKey;
	int fruitX[3], fruitY[3],score;
	bool eat[3] = { false, false, false };
	enum eDirections { STOP = 0,LEFT,RIGHT,UP,DOWN };
	eDirections dir;
	snakeGame()
	{
		head = nullptr;
		tail = nullptr;
	}
	~snakeGame()
	{
		node<T,C>* temp = head;
		while (temp)
		{
			temp = temp->next;
			delete head;
			head = temp;
		}
	}
	void addToTail(T x,T y,C value='*')
	{
		node<T,C>* newNode = new node<T,C>(x,y,value);
		if (isEmpty())
		{
			head = newNode;
		}
		else
		{
			node<T,C>* temp = head;
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = newNode;
			newNode->prev = temp;
			newNode->next = nullptr;
		}
	}
	int getLength()
	{
		int count = 0;
		node<T,C>* temp = head;
		while (temp->next)
		{
			count++;
			temp = temp->next;
		}
		return count;
	}
	void print()
	{
		system("CLS");
/*
		for (int i = 0; i < this->width; i++)
			cout << "=";	//top border
		cout << endl;
*/
		for (int i = 0; i < this->height; i++)
		{
			for (int j = 0; j < this->width; j++)
			{
				//if (j == 0 || j == this->width - 1)
				//	cout << "|";
				if (i == this->head->y && j == this->head->x)
					cout << this->head->value;
				else if ((i == this->fruitY[0] && j == this->fruitX[0]) ||(i == this->fruitY[1] && j == this->fruitX[1]) ||(i == this->fruitY[2] && j == this->fruitX[2]))
					cout << "@";
				else
				{
					bool print = false;
					for (int k = 0; k < this->getLength(); k++)
					{
						if (this->getNode(k)->x == j && this->getNode(k)->y == i)
						{
							cout << this->getNode(k)->value;//tail segmebt
							print = true;
						}
					}
					if(!print)
						cout << " ";
				}
			}
			cout << endl;
		}
/*
		for (int i = 0; i < this->width; i++)
			cout << "=";	//bellow border
		cout << endl;
*/
	}
	void createFruit(int eati)
	{
		this->fruitX[eati] = rand() % (this->width - 2);
		this->fruitY[eati] = rand() % (this->height - 2);
	}
	void onCollision()
	{
		//if touch walls game end
		//if (this->head->x<0 || this->head->x>this->width || this->head->y<0 || this->head->y>this->height)
		//	this->gameOver = true;

		//if go out of the boundry
		if (this->head->x < 0)
			this->head->x = width;
		if (this->head->x > this->width)
			this->head->x = 0;

		if (this->head->y < 0)
			this->head->y =this->height;
		if (this->head->y > this->height)
			this->head->y = 0;


		if (this->head->x == this->fruitX[0] && this->head->y == fruitY[0])
		{
			score += 10;
			//fruit position 1 for now
			this->addToTail(fruitX[0], fruitY[0]);
			this->createFruit(0);

			//coloring
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			WORD wOldColorAttrs;
			CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
			GetConsoleScreenBufferInfo(h, &csbiInfo);
			wOldColorAttrs = csbiInfo.wAttributes;
			SetConsoleTextAttribute(h, wOldColorAttrs % 14 + 1);

		}
		if (this->head->x == this->fruitX[1] && this->head->y == fruitY[1])
		{
			score += 10;
			//fruit position 1 for now
			this->addToTail(fruitX[1], fruitY[1]);
			this->createFruit(1);

			//coloring
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			WORD wOldColorAttrs;
			CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
			GetConsoleScreenBufferInfo(h, &csbiInfo);
			wOldColorAttrs = csbiInfo.wAttributes;
			SetConsoleTextAttribute(h, wOldColorAttrs % 14 + 1);

		}if (this->head->x == this->fruitX[2] && this->head->y == fruitY[2])
		{
			score += 10;
			//fruit position 1 for now
			this->addToTail(fruitX[2], fruitY[2]);
			this->createFruit(2);

			//coloring
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			WORD wOldColorAttrs;
			CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
			GetConsoleScreenBufferInfo(h, &csbiInfo);
			wOldColorAttrs = csbiInfo.wAttributes;
			SetConsoleTextAttribute(h, wOldColorAttrs % 14 + 1);

		}
	}
	node<T,C>* getNode(int n)
	{
		node<T,C>* temp = head;
		int count = getLength();

		int no = 0;
		while (temp->next)
		{
			no++;
			if (no == n)
			{
				return temp;
			}
			temp = temp->next;
		}
		return temp;
	}
	void move()
	{
		int prevX = this->head->x;
		int prevY = this->head->y;
		int prev2X, prev2Y;
		this->getNode(0)->x = this->head->x;
		this->getNode(0)->y = this->head->y;
		for (int i = 1; i < this->getLength(); i++)
		{
			prev2X = this->getNode(i)->x;
			prev2Y = this->getNode(i)->y;
			this->getNode(i)->x = prevX;
			this->getNode(i)->y = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}

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
	void startGame()
	{
		this->setup();
		while (!gameOver)
		{
			this->print();
			this->input();
			this->move();
			Sleep(50);
			cout << "score: " << this->score << endl;
		}
	}

	bool isEmpty()
	{
		return head == nullptr;
	}
	//other
	void setup()
	{
		this->gameOver = false;
		this->dir = STOP;
		//center position
		this->head = new node<int, char>(this->width / 2, this->height / 2, 153);
		this->addToTail(this->head->x - 1, this->head->y);
		this->addToTail(this->head->x - 2, this->head->y);
		this->addToTail(this->head->x - 3, this->head->y);
		//fruit position 1 for now
		this->createFruit(0);
		this->createFruit(1);
		this->createFruit(2);
		//score
		this->score = 0;
	}
	//void draw();
	void input()
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
	//void logic();
};