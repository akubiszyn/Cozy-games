#include "Animal.h"


void Chicken::set_Texture(std::string texture)
{
	if (!this->texture.loadFromFile(texture))
	{
		return;
	}
}

bool Chicken::set_Sprite(std::string texture)
{
	this->set_Texture(texture);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 29, 48));
	return true;
}

Chicken::Chicken(std::string texture, int move_up_down, int move_left_right, unsigned int x, unsigned int y): stop(false), moving_up_down(move_up_down), moving_left_right(move_left_right), distance(0)
{
	if (!this->set_Sprite(texture))
	{
		return;
	}
	this->currentFrame = sf::IntRect(0, 0, 29, 48);
	this->sprite.setPosition(x, y);
	this->music_path = "music/chicken.ogg";
}


void Chicken::move()
{
	if (!stop)
	{
		if (this->distance > 20)
		{
			this->moving_left_right = -this->moving_left_right;
			this->moving_up_down = -this->moving_up_down;
			this->distance = 0;
			if (this->moving_left_right < 0)
			{
				this->texture.loadFromFile("images/chicken_walk_left.png");
			}
			else
			{
				this->texture.loadFromFile("images/chicken_walk_right.png");
			}
		}
		this->sprite.move(this->moving_left_right, this->moving_up_down);
		this->distance += 1;
		this->change_animation();
	}
	else
	{
		this->sprite.setTexture(this->texture);
	}
}

void Chicken::change_animation()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
		if (this->currentFrame.left >= 87) {
			this->currentFrame.left = 0;
		}
		this->currentFrame.left += 29;
		this->sprite.setTextureRect(this->currentFrame);
		this->animationTimer.restart();
	}
}

void Chicken::display(sf::RenderTarget& window) const
{
	window.draw(this->sprite);
}

sf::Sprite& Chicken::get_Sprite()
{
	return this->sprite;
}

sf::Texture& Chicken::get_Texture()
{
	return this->texture;
}

void Chicken::stop_now(bool stop)
{
	this->stop = stop;
}

std::string Chicken::get_music_path() const
{
	return  this->music_path;
}

Chicken::~Chicken()
{
}