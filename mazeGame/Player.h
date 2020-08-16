#pragma once
#include "essentials.h"
#include "maze.h"
class Player
{
public:
	Player(int size);
	RectangleShape getShape();
	void checkInput();
	void setPos(Vector2f newPos);
	void changeSize(float size);

private:
	void update();
	RectangleShape rect;
	Vector2f pos;
	float speed;
	bool canExit;
	bool movingUp;
	bool movingDown;
	bool movingLeft;
	bool movingRight;
};

