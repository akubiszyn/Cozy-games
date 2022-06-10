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
	//this->wholeFrame.loadFromFile("images/trawa.png");
	//this->wholeSprite.setTexture(this->wholeFrame);
	//this->currentFrame = sf::IntRect(0, 0, 120, 62);
	this->set_Sprite("images/trawa.png", 120, 62);
	this->set_position(0, 0);
	this->square_sprite.setPosition(this->position);
	this->isAccessable = true;
}

Game_square::Game_square(std::string texture, unsigned int square_width, unsigned int square_height, bool accessed, int width_multiply, int height_multiply)
{
	if (square_width == 0 || square_height == 0)
	{
		throw ZeroOccuredException();
	}
	if (width_multiply < 0 || height_multiply < 0)
	{
		throw InvalidPositionException();
	}
	//this->wholeFrame.loadFromFile(texture);
	//his->wholeSprite.setTexture(this->wholeFrame);
	//this->currentFrame = sf::IntRect(0, 0, square_width, square_height);
	this->set_Sprite(texture, square_width, square_height);
	this->set_position(this->get_Sprite().getLocalBounds().width * this->get_scale_x() * width_multiply, this->get_Sprite().getLocalBounds().height * this->get_scale_y() * height_multiply);
	this->square_sprite.setPosition(this->position);
	this->isAccessable = accessed;

}

Game_square::Game_square(const Game_square& game_square)
{
	this->isAccessable = game_square.isAccessable;
	this->position = game_square.position;
	//this->animationTimer = game_square.animationTimer;
	//this->currentFrame = game_square.currentFrame;
	this->scale_x = game_square.scale_x;
	this->scale_x = game_square.scale_y;
	this->square_sprite = game_square.square_sprite;
	this->square_texture = game_square.square_texture;
	this->square_sprite.setTexture(this->square_texture);
	//this->wholeFrame = game_square.wholeFrame;
	//this->wholeSprite = game_square.wholeSprite;
	//this->wholeSprite.setTexture(this->wholeFrame);
}

Game_square& Game_square::operator=(const Game_square& game_square)
{
	this->isAccessable = game_square.isAccessable;
	this->position = game_square.position;
	//this->animationTimer = game_square.animationTimer;
	//this->currentFrame = game_square.currentFrame;
	this->scale_x = game_square.scale_x;
	this->scale_x = game_square.scale_y;
	this->square_sprite = game_square.square_sprite;
	this->square_texture = game_square.square_texture;
	this->square_sprite.setTexture(this->square_texture);
	//this->wholeFrame = game_square.wholeFrame;
	//this->wholeSprite = game_square.wholeSprite;
	//this->wholeSprite.setTexture(this->wholeFrame);
	return *this;
}

Game_square::Game_square(Game_square&& game_square) noexcept(true)
{
	this->isAccessable = bool();
	this->position = sf::Vector2f();
	//this->animationTimer = sf::Clock();
	//this->currentFrame = sf::IntRect();
	this->scale_x = float();
	this->scale_x = float();
	this->square_sprite = sf::Sprite();
	this->square_texture = sf::Texture();
//	this->wholeFrame = sf::Texture();
//	this->wholeSprite = sf::Sprite();
	this->isAccessable = game_square.isAccessable;
	this->position = game_square.position;
	//this->animationTimer = game_square.animationTimer;
	//this->currentFrame = game_square.currentFrame;
	this->scale_x = game_square.scale_x;
	this->scale_x = game_square.scale_y;
	this->square_sprite = game_square.square_sprite;
	this->square_texture = game_square.square_texture;
	this->square_sprite.setTexture(this->square_texture);
	//this->wholeFrame = game_square.wholeFrame;
	//this->wholeSprite = game_square.wholeSprite;
	//this->wholeSprite.setTexture(this->wholeFrame);
	game_square.isAccessable = bool();
	game_square.position = sf::Vector2f();
	//game_square.animationTimer = sf::Clock();
	//game_square.currentFrame = sf::IntRect();
	game_square.scale_x = float();
	game_square.scale_x = float();
	game_square.square_sprite = sf::Sprite();
	game_square.square_texture = sf::Texture();
	//game_square.wholeFrame = sf::Texture();
	//game_square.wholeSprite = sf::Sprite();
}
Game_square& Game_square::operator=(Game_square&& game_square) noexcept(true)
{
	if (this != &game_square)
	{
		this->isAccessable = bool();
		this->position = sf::Vector2f();
		//this->animationTimer = sf::Clock();
		//this->currentFrame = sf::IntRect();
		this->scale_x = float();
		this->scale_x = float();
		this->square_sprite = sf::Sprite();
		this->square_texture = sf::Texture();
		//this->wholeFrame = sf::Texture();
		//this->wholeSprite = sf::Sprite();
		this->isAccessable = game_square.isAccessable;
		this->position = game_square.position;
		//this->animationTimer = game_square.animationTimer;
		//this->currentFrame = game_square.currentFrame;
		this->scale_x = game_square.scale_x;
		this->scale_x = game_square.scale_y;
		this->square_sprite = game_square.square_sprite;
		this->square_texture = game_square.square_texture;
		this->square_sprite.setTexture(this->square_texture);
		//this->wholeFrame = game_square.wholeFrame;
		//this->wholeSprite = game_square.wholeSprite;
		//this->wholeSprite.setTexture(this->wholeFrame);
		game_square.isAccessable = bool();
		game_square.position = sf::Vector2f();
		//game_square.animationTimer = sf::Clock();
		//game_square.currentFrame = sf::IntRect();
		game_square.scale_x = float();
		game_square.scale_x = float();
		game_square.square_sprite = sf::Sprite();
		game_square.square_texture = sf::Texture();
		//game_square.wholeFrame = sf::Texture();
		//game_square.wholeSprite = sf::Sprite();
	}
	return *this;
}
/*
void Game_square::change_animation()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
		if (this->currentFrame.left >= this->wholeSprite.getLocalBounds().width - this->square_sprite.getLocalBounds().width) {
			this->currentFrame.left = 0 - this->currentFrame.width;;
		}
		if (!this->currentFrame.left < 0)
		{
			this->currentFrame.left += this->currentFrame.width;
			this->square_sprite.setTextureRect(this->currentFrame);
		}
		this->animationTimer.restart();
	}
}
*/
bool Game_square::set_Sprite(std::string texture, unsigned int width, unsigned int height)
{
	this->set_Texture(texture);
	//float width_temp = this->wholeSprite.getLocalBounds().width;
	//float height_temp = this->wholeSprite.getLocalBounds().height;
	this->square_sprite.setTexture(this->square_texture);
	//this->square_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	float x = float(width) / float(this->square_sprite.getLocalBounds().width);
	float y = float(height) / float(this->square_sprite.getLocalBounds().height);
	this->scale_x = x;
	this->scale_y = y;
	this->square_sprite.setScale(x, y);

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

float Game_square::get_scale_x() const
{
	return this->scale_x;
}

float Game_square::get_scale_y() const
{
	return this->scale_y;
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