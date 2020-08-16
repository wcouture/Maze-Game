#include "Player.h"

Player::Player(int size) {
	this->rect.setFillColor(Color::Red);
	this->rect.setSize(Vector2f(size,size));
	this->speed = .3;
	this->canExit = false;
}

void Player::setPos(Vector2f newPos) {
	pos = newPos;
	update();
}

void Player::checkInput() {
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		movingUp = true;
	}
	else {
		movingUp = false;
	}

	

	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
		movingDown = true;
	}
	else {
		movingDown = false;
	}

	

	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		movingLeft = true;
	}
	else {
		movingLeft = false;
	}

	

	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
		movingRight = true;
	}
	else {
		movingRight = false;
	}
	
	update();
}

void Player::update() {
	if (movingUp && pos.y > 0) {
		pos.y -= speed;
	}

	if (movingDown && pos.y < (500-rect.getSize().y)) {
		pos.y += speed;
	}

	if (movingLeft && pos.x > 0) {
		pos.x -= speed;
	}

	if (movingRight && pos.x < (500-rect.getSize().x)) {
		pos.x += speed;
	}

	this->rect.setPosition(pos);
}

RectangleShape Player::getShape() {
	return this->rect;
}

void Player::changeSize(float size) {
	this->rect.setSize(Vector2f(size, size));
}


