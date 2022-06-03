#include "Player.h"
#include "stdafx.h"

Player::Player() {
	this->initTexture();
	this->initSprite();
}

void Player::initSprite()
{
	this->shape.setTexture(texture);
	this->currentFrame = IntRect(0, 0, 32, 32);
	this->shape.setTextureRect(IntRect(0, 0, 32, 32));
	this->shape.setScale(3.0, 3.0);
}

void Player::initTexture()
{
	this->texture.loadFromFile("Textures/char free/walk_right.png");
}




void Player::updateMovement() {
	this->moving = false;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->shape.move(0.f, -2.0f);
		this->moving = true;
		this->updateAnimations();
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		texture.loadFromFile("Textures/char free/walk_right.png");
		this->shape.move(2.0f, 0.f);
		this->moving = true;
		this->updateAnimations();
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->shape.move(0.f, 2.0f);
		this->moving = true;
		this->updateAnimations();
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		texture.loadFromFile("Textures/char free/walk_left.png");
		this->shape.move(-2.0f, 0.f);
		this->moving = true;
		this->updateAnimations();
	}
	this->updateAnimations();
}


void Player::render(RenderTarget& target){
	target.draw(this->shape);
}

void Player::updateAnimations()
{
	if (this->moving == false){
		this->initSprite();
	}
	else if (this->moving == true) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			if (this->currentFrame.left >= 224.f) {
				this->currentFrame.left = 0;
			}
			this->currentFrame.left += 32.f;
			this->shape.setTextureRect(this->currentFrame);
			this->animationTimer.restart();
		}
	}


}
