#include "Player.h"

Player::Player(sf::Vector2u vec, sf::Vector2i pos, sf::Vector2i shape_size, unsigned int scale_divider, unsigned int move_divider, float shape_in_square_divider) : window_size(vec) {
	if (vec.x == 0 || vec.y == 0 || pos.x == 0 || pos.y == 0 || shape_size.x == 0 || shape_size.y == 0 || scale_divider == 0 || move_divider == 0 || shape_in_square_divider == 0)
	{
		throw ZeroOccuredException();
	}
	if (pos.x < 0 || pos.y < 0)
	{
		throw InvalidPositionException();
	}
	this->shape_size = shape_size;
	this->scale_divider = scale_divider;
	this->move_divider = move_divider;
	this->pos = pos;
	this->shape_in_square_divider = shape_in_square_divider;
	this->initTexture();
	this->initSprite();
	this->movement_x = this->shape.getLocalBounds().width * this->shape.getScale().x / this->move_divider;
	this->movement_y = this->shape.getLocalBounds().height * this->shape.getScale().y / this->move_divider;
	this->shape.setPosition(sf::Vector2f(this->shape.getLocalBounds().width * this->scale_x * this->pos.x, this->shape.getLocalBounds().height * this->scale_y * this->pos.y));
}

void Player::initSprite()
{
	this->shape.setTexture(texture);
	unsigned int x = this->window_size.x / this->scale_divider;
	unsigned int y = this->window_size.y / this->scale_divider;
	this->scale_x = float(x) / float(this->shape_size.x);
	this->scale_y = float(y) / float(this->shape_size.y);
	this->currentFrame = sf::IntRect(0, 0, this->shape_size.x, this->shape_size.y);
	this->shape.setTextureRect(sf::IntRect(0, 0, this->shape_size.x, this->shape_size.y));
	float temp_scale_x = this->shape_in_square_divider * this->scale_x;
	float temp_scale_y = this->shape_in_square_divider * this->scale_y;
	this->shape.setScale(temp_scale_x, temp_scale_y);

}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("images/walk_leftm.png"))
	{
		throw TextureNotLoadedException();
	}
}

float Player::get_movement_x() const
{
	return this->movement_x;
}

float Player::get_movement_y() const
{
	return this->movement_y;
}

sf::Sprite& Player::get_sprite_ref()
{
	return this->shape;
}

sf::Vector2f Player::updateMovement() {
	this->moving = false;
	sf::Vector2f to_return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		{
			if (this->movement_y > 0)
				this->movement_y = -this->movement_y;
			this->shape.move(0.f, this->movement_y);
			this->moving = true;
			this->updateAnimations();
			to_return = sf::Vector2f(0.f, -this->shape.getLocalBounds().height * this->shape.getScale().y / this->move_divider);
			direction = 0;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		{
			if (this->movement_x < 0)
				this->movement_x = -this->movement_x;
			texture.loadFromFile("images/walk_rightm.png");
			this->shape.move(this->movement_x, 0.f);
			this->moving = true;
			this->updateAnimations();
			to_return = sf::Vector2f(this->shape.getLocalBounds().width * this->shape.getScale().x / this->move_divider, 0.f);
			direction = 3;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		{
			if (this->movement_y < 0)
				this->movement_y = -this->movement_y;
			this->shape.move(0.f, this->movement_y);
			this->moving = true;
			this->updateAnimations();
			to_return = sf::Vector2f(0.f, this->shape.getLocalBounds().height * this->shape.getScale().y / this->move_divider);
			direction = 2;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		{
			if (this->movement_x > 0)
				this->movement_x = -this->movement_x;
			texture.loadFromFile("images/walk_leftm.png");
			this->shape.move(this->movement_x, 0.f);
			this->moving = true;
			this->updateAnimations();
			to_return = sf::Vector2f(-this->shape.getLocalBounds().width * this->shape.getScale().x / this->move_divider, 0.f);
			direction = 1;
		}
	}
	this->updateAnimations();
	return to_return;
}

sf::Sprite Player::get_sprite() const
{
	return this->shape;
}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->shape);
}

void Player::updateAnimations()
{
	if (this->moving == false) {
		this->initSprite();
	}
	else if (this->moving == true) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			if (this->currentFrame.left >= 504) {
				this->currentFrame.left = 0;
			}
			this->currentFrame.left += 72;
			this->shape.setTextureRect(this->currentFrame);
			this->animationTimer.restart();
		}
	}


}

sf::Texture Player::get_Texture() const
{
	return this->texture;
}

sf::Vector2u Player::get_window_size() const
{
	return this->window_size;
}

unsigned int Player::get_scale_divider() const
{
	return this->scale_divider;
}

sf::Vector2i Player::get_shape_size() const
{
	return this->shape_size;
}

float Player::get_scale_x() const
{
	return this->scale_x;
}

float Player::get_scale_y() const
{
	return this->scale_y;
}

float Player::get_in_square_divider() const
{
	return this->shape_in_square_divider;
}
int Player::get_dir()
{
	return direction;
}
