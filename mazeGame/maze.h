#pragma once
#include "essentials.h"
class maze
{
public:
	maze(vector<vector<char>> layout);
	vector<RectangleShape> getShapes();
	bool checkCollisions(RectangleShape player);
	bool isKeyCollected();
	void checkKey(RectangleShape player);
	Vector2f getPlayerStart();
	float squareSize;
	void resetKey();
	bool checkExit(RectangleShape player);
private:
	vector<RectangleShape> squares;
	Vector2f playerPos;
	RectangleShape key;
	RectangleShape exit;
	bool keyCollected;
};

