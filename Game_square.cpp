#include "Game_square.h"


sf::Sprite Game_square::get_Sprite() const
{
	return this->square_sprite;
}

sf::Texture Game_square::get_Texture() const
{
	return this->square_texture;
}

sf::Sprite& Game_square::get_Sprite_ref()
{
	return this->square_sprite;
}

sf::Texture& Game_square::get_Texture_ref()
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

Game_square::Game_square()
{
	this->set_Sprite("images/trawa.png");
	this->set_position(0, 0);
	this->square_sprite.setPosition(this->position);
	this->isAccessable = true;
}

Game_square::Game_square(std::string texture, float x, float y, bool accessed)
{
	this->set_Sprite(texture);
	this->set_position(x, y);
	this->square_sprite.setPosition(this->position);
	this->isAccessable = accessed;

}

bool Game_square::set_Sprite(std::string texture)
{
	this->set_Texture(texture);
	this->square_sprite.setTexture(this->square_texture);
	this->square_sprite.setTextureRect(sf::IntRect(0, 0, 120, 62));
	return true;
}

void Game_square::set_is_Accessable(bool is_accessable)
{
	this->isAccessable = is_accessable;
}

void Game_square::set_position(float x, float y)
{
	if (x < 0 || y < 0)
	{
		throw InvalidPositionException();
	}
	this->position = sf::Vector2f(x, y);
}

void Game_square::set_Texture(std::string texture)
{
	if (!this->square_texture.loadFromFile(texture))
	{
		throw TextureNotLoadedException();
	}
	this->square_texture.setSmooth(true);
}
/*
void Game_square::check_square_texture(std::string texture)
{
	try
	{
		this->set_Texture(texture);
	}
	catch (TextureNotLoadedException& e)
	{
		std::cerr << "TextureNotLoadedException " << e.what() << std::endl;
		std::exit(-1);
	}

}
*/
/*
void Game_square::check_position(float x, float y)
{
	try
	{
		this->set_position(x, y);
	}
	catch (InvalidPositionException& e)
	{
		std::cerr << "InvalidPositionException " << e.what() << std::endl;
		std::exit(-2);
	}

}
*/