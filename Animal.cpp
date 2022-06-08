#include "Animal.h"

void Creature::set_Texture(std::string texture)
{
	if (!this->texture.loadFromFile(texture))
	{
		throw TextureNotLoadedException();
	}
	this->currentFrame = sf::IntRect(0, 0, this->width, this->height);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	this->sprite.setScale(1.0, 1.0);
}

void NPC::set_Sprite(std::string texture)
{
	this->set_Texture(texture);
	this->get_Sprite().setTexture(this->texture);
	this->get_Sprite().setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	this->sprite.setPosition(sf::Vector2f(0, 0));
	unsigned int x = this->window.getSize().x / 16;
	unsigned int y = this->window.getSize().y / 16;
	float scale_x = float(x) / float(this->sprite.getLocalBounds().width);
	float scale_y = float(y) / float(this->sprite.getLocalBounds().height);
	scale_x = 0.6 * scale_x;
	scale_y = 0.6 * scale_y;
	this->sprite.setScale(scale_x, scale_y);
}

void Chicken::set_Sprite(std::string texture)
{
	this->set_Texture(texture);
	this->get_Sprite().setTexture(this->texture);
	this->get_Sprite().setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	this->sprite.setPosition(sf::Vector2f(0, 0));
	unsigned int x = this->window.getSize().x / 16;
	unsigned int y = this->window.getSize().y / 16;
	float scale_x = float(x) / float(this->sprite.getLocalBounds().width);
	float scale_y = float(y) / float(this->sprite.getLocalBounds().height);
	scale_x = 0.6 * scale_x;
	scale_y = 0.6 * scale_y;
	this->sprite.setScale(scale_x, scale_y);

}


void Chicken::set_position(float x, float y)
{
	if (x < 0 || y < 0)
	{
		throw InvalidPositionException();
	}
	unsigned int x_w = this->window.getSize().x / 16;
	unsigned int y_w = this->window.getSize().y / 16;
	float scale_x = float(x_w) / this->sprite.getLocalBounds().width;
	float scale_y = float(y_w) / this->sprite.getLocalBounds().height;
	this->position = sf::Vector2f(sf::Vector2f(this->sprite.getLocalBounds().width * scale_x * x, this->sprite.getLocalBounds().height * scale_y * y));
}

void NPC::set_position(float x, float y)
{
	if (x < 0 || y < 0)
	{
		throw InvalidPositionException();
	}
	unsigned int x_w = this->window.getSize().x / 16;
	unsigned int y_w = this->window.getSize().y / 16;
	float scale_x = float(x_w) / this->sprite.getLocalBounds().width;
	float scale_y = float(y_w) / this->sprite.getLocalBounds().height;
	this->position = sf::Vector2f(sf::Vector2f(this->sprite.getLocalBounds().width * scale_x * x, this->sprite.getLocalBounds().height * scale_y * y));

}

sf::Sprite& Creature::get_Sprite()
{
	return this->sprite;
}

sf::Texture& Creature::get_Texture()
{
	return this->texture;
}

void Creature::display(sf::RenderTarget& window) const
{
	window.draw(this->sprite);
}


NPC::NPC(std::string texture, float xPos, float yPos, sf::RenderWindow& window) : window(window) {
	this->width = 72;
	this->height = 50;
	this->set_Sprite(texture);
	//this->texture.loadFromFile("images/walk_leftm.png");
	//this->sprite.setTexture(this->texture);
	//this->currentFrame = sf::IntRect(0, 0, 72, 50);
	//this->sprite.setTextureRect(sf::IntRect(0, 0, 72, 50));
	this->set_position(xPos, yPos);
	this->sprite.setPosition(this->position);
	this->startGame = false;
}

void NPC::talk(int index) {
	sf::Event event;
	sf::RenderWindow talkWindow(sf::VideoMode(400, 300), "Let's play!");
	sf::Sprite talkBackground;
	sf::Texture talkTexture;
	talkTexture.loadFromFile("images/talk" + std::to_string(index) + ".png");
	talkBackground.setTexture(talkTexture);
	while (talkWindow.isOpen()) {
		while (talkWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				talkWindow.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			this->startGame = false;
			talkWindow.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			this->startGame = true;
			talkWindow.close();
		}

		talkWindow.draw(talkBackground);
		talkWindow.display();
	}

}

Chicken::Chicken(std::string texture, int move_up_down, int move_left_right, int x, int y, sf::RenderWindow& window) : stop(false), moving_up_down(move_up_down), moving_left_right(move_left_right), distance(0), window(window) {
	this->width = 29;
	this->height = 48;
	this->set_Sprite(texture);
	this->set_position(x, y);
	this->sprite.setPosition(this->position);
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
			if ((this->moving_left_right < 0 && this->moving_up_down == 0) || (this->moving_up_down < 0 && this->moving_left_right == 0))
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

sf::Vector2f Chicken::get_position() const
{
	return this->position;
}

void Chicken::change_animation()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
		if (this->currentFrame.left >= this->width * 3) {
			this->currentFrame.left = 0;
		}
		this->currentFrame.left += this->width;
		this->sprite.setTextureRect(this->currentFrame);
		this->animationTimer.restart();
	}
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
