#include "Player.h"

Player::Player() {
	this->initTexture();
	this->initSprite();
	this->shape.setPosition(sf::Vector2f(1680, 497));
}

void Player::initSprite()
{
	this->shape.setTexture(texture);
	this->currentFrame = sf::IntRect(0, 0, 72, 50);
	this->shape.setTextureRect(sf::IntRect(0, 0, 72, 50));
	this->shape.setScale(1.0, 1.0);
}

void Player::initTexture()
{
	this->texture.loadFromFile("images/walk_leftm.png");
}


bool Player::check_collision(Game_map & map, float movement_x, float movement_y)
{
	sf::FloatRect player_rect = this->shape.getGlobalBounds();
	sf::FloatRect check = sf::FloatRect(player_rect.left + movement_x, player_rect.top + movement_y, player_rect.width, player_rect.height);
	for (const std::pair<const unsigned int, std::map<unsigned int, Game_square>>& row : map.get_squares_first())
	{
		for (const std::pair<const unsigned int, Game_square>& column : row.second)
		{
			sf::FloatRect square = column.second.get_Sprite().getGlobalBounds();
			if (square.intersects(check) && column.second.get_is_Accessable() == false)
			{
					return true;
			}
		}
	}
	for (const std::pair<const unsigned int, std::map<unsigned int, Game_square>>& row : map.get_squares_second())
	{
		for (const std::pair<const unsigned int, Game_square>& column : row.second)
		{
			sf::FloatRect square = column.second.get_Sprite().getGlobalBounds();
			if (square.intersects(check) && column.second.get_is_Accessable() == false)
			{
				return true;
			}
		}
	}
	for (const std::unique_ptr<Chicken>& animal_ptr : map.get_animals())
	{
		if (animal_ptr->get_Sprite().getGlobalBounds().intersects(check))
		{
			animal_ptr->stop_now(true);
			map.set_music_path(animal_ptr->get_music_path());
			map.set_play_music(true);
		}
	}
	for (const std::unique_ptr<NPC>& npc_ptr : map.get_npcs())
	{
		if (npc_ptr->get_Sprite().getGlobalBounds().intersects(check))
		{
			npc_ptr->startGame = true;
			auto it = find(map.get_npcs().begin(), map.get_npcs().end(), npc_ptr);
			int index = it - map.get_npcs().begin();
			npc_ptr->talk(index);
		}
	}
	return false;
}


void Player::updateMovement(Game_map& map) {
	bool cont = false;
	this->moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (!this->check_collision(map,0.0f, -2.0f))
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
	for (const std::unique_ptr<Chicken>& animal_ptr : map.get_animals())
	{
		if (!animal_ptr->get_Sprite().getGlobalBounds().intersects(this->shape.getGlobalBounds()))
		{
			animal_ptr->stop_now(false);
		}
		else
		{
			cont = true;
		}
	}
	if (!cont)
	{
		map.set_play_music(false);
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
			if (this->currentFrame.left >= 504) {
				this->currentFrame.left = 0;
			}
			this->currentFrame.left += 72;
			this->shape.setTextureRect(this->currentFrame);
			this->animationTimer.restart();
		}
	}


}
