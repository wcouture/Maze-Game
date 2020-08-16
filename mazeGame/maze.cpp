#include "maze.h"

maze::maze(vector<vector<char>> layout) {
	vector<vector<char>> grid = layout;

	keyCollected = false;

	int sidelen = grid.size();
	squareSize = 500 / sidelen;

	for (int x = 0; x < grid.size(); x++) {
		for (int y = 0; y < grid.size(); y++) {
			if (grid[y][x] == 'o') {
				RectangleShape temp;
				
				temp.setSize(Vector2f(squareSize, squareSize));
				
				float xPos = squareSize * x;
				float yPos = squareSize * y;

				temp.setPosition(Vector2f(xPos, yPos));

				temp.setFillColor(Color::Black);

				this -> squares.push_back(temp);
			}
			else if (grid[y][x] == 'p') {
				this->playerPos.x = (squareSize * x) + (squareSize / 4);
				this->playerPos.y = (squareSize * y) + (squareSize / 4);
			}
			else if (grid[y][x] == 'k') {
				key.setFillColor(Color::Yellow);
				key.setSize(Vector2f(squareSize/2, squareSize/2));

				float posX = (squareSize * x) + (squareSize / 4);
				float posY = (squareSize * y) + (squareSize / 4);

				key.setPosition(Vector2f(posX,posY));
			}
			else if (grid[y][x] == 'e') {
				this->exit.setFillColor(Color::Red);
				this->exit.setSize(Vector2f(squareSize,squareSize));

				float xPos = squareSize * x;
				float yPos = squareSize * y;

				this->exit.setPosition(Vector2f(xPos,yPos));
			}
		}
	}
}

bool maze::checkExit(RectangleShape player) {
	return player.getGlobalBounds().intersects(this->exit.getGlobalBounds()) && keyCollected;
}

void maze::resetKey() {
	key.setSize(Vector2f(squareSize/2,squareSize/2));
	this->keyCollected = false;
	this->exit.setFillColor(Color::Red);
}

Vector2f maze::getPlayerStart() {
	return this->playerPos;
}

vector<RectangleShape> maze::getShapes() {
	vector<RectangleShape> temp = this->squares;
	temp.push_back(key);
	temp.push_back(exit);
	return temp;
}

bool maze::isKeyCollected() {
	return keyCollected;
}

bool maze::checkCollisions(RectangleShape player) {
	for(RectangleShape rs: this->squares) {
		if (player.getGlobalBounds().intersects(rs.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

void maze::checkKey(RectangleShape player) {
	if (player.getGlobalBounds().intersects(this->key.getGlobalBounds())) {
		key.setSize(Vector2f(0,0));
		keyCollected = true;
		this->exit.setFillColor(Color::Green);
	}
}
