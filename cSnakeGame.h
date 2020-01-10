class snakeGame
{
public:
	//head and tail of snake
	node *head;
	node *tail;

	//walls of 20x20
	const int width = 30; 
	const int height = 20;

	bool gameOver;

	int pressedKey;

	int fruitX, fruitY,score;
	enum eDirections { STOP = 0,LEFT,RIGHT,UP,DOWN };
	eDirections dir;
	snakeGame();
	//~snakeGame();
	//void addToTail();
	void print();
	void createFruit();
	void onCollision();
	void move();
	void startGame();


	//other
	void setup();
	//void draw();
	void input();
	//void logic();
};