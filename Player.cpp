#include "Player.h"

Player::Player() {
	this->initTexture();
	this->initSprite();
	this->shape.setPosition(sf::Vector2f(0, 101));
}

void Player::initSprite()
{
	this->shape.setTexture(texture);
	this->currentFrame = sf::IntRect(0, 0, 48, 48);
	this->shape.setTextureRect(sf::IntRect(0, 0, 48, 48));
	this->shape.setScale(1.0, 1.0);
}

void Player::initTexture()
{
	this->texture.loadFromFile("images/walk_rightm.png");
}


bool Player::check_collision(const std::map<unsigned int, std::map<unsigned int, std::unique_ptr<Game_square>>>& map, float movement_x, float movement_y)
{
	sf::FloatRect player_rect = this->shape.getGlobalBounds();
	sf::FloatRect check = sf::FloatRect(player_rect.left + movement_x, player_rect.top + movement_y, player_rect.width, player_rect.height);
	for (const std::pair<const unsigned int, std::map<unsigned int, std::unique_ptr<Game_square>>>& row : map)
	{
		for (const std::pair<const unsigned int, std::unique_ptr<Game_square>>& column : row.second)
		{
			sf::FloatRect square = column.second->get_Sprite_ref().getGlobalBounds();
			if (square.intersects(check) && column.second->get_is_Accessable() == false)
			{
					return true;
			}
		}
	}
	return false;
}


void Player::updateMovement(const std::map<unsigned int, std::map<unsigned int, std::unique_ptr<Game_square>>>& map) {
	this->moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (!this->check_collision(map, 0.0f, -2.0f))
		{
			this->shape.move(0.f, -2.0f);
			this->moving = true;
			this->updateAnimations();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (!this->check_collision(map, 2.0f, 0.0f))
		{
			texture.loadFromFile("images/walk_rightm.png");
			this->shape.move(2.0f, 0.f);
			this->moving = true;
			this->updateAnimations();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (!this->check_collision(map, 0.0f, 2.0f))
		{
			this->shape.move(0.f, 2.0f);
			this->moving = true;
			this->updateAnimations();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (!this->check_collision(map, -2.0f, 0.0f))
		{
			texture.loadFromFile("images/walk_leftm.png");
			this->shape.move(-2.0f, 0.f);
			this->moving = true;
			this->updateAnimations();
		}
	}
	this->updateAnimations();
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
			if (this->currentFrame.left >= 336.f) {
				this->currentFrame.left = 0;
			}
			this->currentFrame.left += 48.f;
			this->shape.setTextureRect(this->currentFrame);
			this->animationTimer.restart();
		}
	}


}
