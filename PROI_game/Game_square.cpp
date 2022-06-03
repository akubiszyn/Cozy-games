#include "Game_square.h"


sf::Sprite& Game_square::get_sprite()
{
	return this->square_sprite;
}

sf::Texture& Game_square::get_Texture() 
{
	return this->square_texture;
}

sf::Vector2f Game_square::get_position() const
{
	return this->position;
}

bool Game_square::get_is_Accessable() const
{
	return this->isAccessable;
}


Game_square::Game_square(std::string texture, float x, float y, bool accessed)
{
	if (!this->set_Sprite(texture))
	{
		return;
	}
	this->position = sf::Vector2f(x, y);
	this->square_sprite.setPosition(this->position);
	this->isAccessable = accessed;

}

bool Game_square::set_Sprite(std::string texture)
{
	this->set_Texture(texture);
	this->square_sprite.setTexture(this->square_texture);
	this->square_sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
	return true;
}

void Game_square::set_is_Accessable(bool is_accessable)
{
	this->isAccessable = is_accessable;
}

void Game_square::set_position(float x, float y)
{
	this->position = sf::Vector2f(x, y);
}

void Game_square::set_Texture(std::string texture)
{
	if (!this->square_texture.loadFromFile(texture))
	{
		return;
	}
	this->square_texture.setSmooth(true);
}