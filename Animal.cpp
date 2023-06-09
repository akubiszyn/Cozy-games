#include "Animal.h"

Ianimal::~Ianimal() {}

void Creature::set_Texture(std::string texture)
{
	if (!this->texture.loadFromFile(texture))
	{
		throw TextureNotLoadedException();
	}
	//this->currentFrame = sf::IntRect(0, 0, this->width, this->height);
	//this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	//this->sprite.setScale(1.0, 1.0);
	this->texture.setSmooth(true);
}

void Creature::set_Sprite(std::string texture, unsigned int width, unsigned int height)
{
	this->set_Texture(texture);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->rect_x, this->rect_y));
	//this->sprite.setPosition(sf::Vector2f(0, 0));
	//unsigned int x = this->window_size.x / width;
	//unsigned int y = this->window_size.y / height;
	float scale_x_temp = float(width) / float(this->sprite.getLocalBounds().width);
	float scale_y_temp = float(height) / float(this->sprite.getLocalBounds().height);
	this->scale_x = scale_x_temp;
	this->scale_y = scale_y_temp;
	this->sprite.setScale(this->in_square_scale_x * scale_x_temp , this->in_square_scale_y * scale_y_temp);
}

Creature::Creature(std::string texture, unsigned int width, unsigned int height,  float in_square_scale_x, float in_square_scale_y, sf::Vector2i pos, unsigned int rect_x, unsigned int rect_y)
{
	if (width == 0 || height == 0 || in_square_scale_x == 0 || in_square_scale_y == 0 || rect_x == 0 || rect_y == 0)
	{
		throw ZeroOccuredException();
	}
	if (pos.x < 0 || pos.y < 0)
	{
		throw InvalidPositionException();
	}
	this->rect_x = rect_x;
	this->rect_y = rect_y;
	this->in_square_scale_x = in_square_scale_x;
	this->in_square_scale_y = in_square_scale_y;
	this->set_Sprite(texture, width, height);
	this->set_position(pos.x, pos.y);
	this->sprite.setPosition(this->position.x, this->position.y);

}
Creature::Creature()
{
	this->in_square_scale_x = 0.5;
	this->in_square_scale_y = 0.5;
	this->set_Sprite("images/chicken_walk_left.png", sf::VideoMode::getFullscreenModes()[0].width / 16, sf::VideoMode::getFullscreenModes()[0].height / 16);
	this->set_position(0, 0);
	this->sprite.setPosition(this->position.x, this->position.y);
}

Creature::Creature(const Creature& creature)
{
	this->in_square_scale_x = creature.in_square_scale_x;
	this->in_square_scale_y = creature.in_square_scale_y;
	this->scale_x = creature.scale_x;
	this->scale_y = creature.scale_y;
	this->set_position(creature.position.x, creature.position.y);
	this->texture = creature.texture;
	this->sprite = creature.sprite;
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(this->scale_x * this->in_square_scale_x, this->scale_y * this->in_square_scale_y);
}

Creature& Creature::operator=(const Creature& creature)
{
	this->in_square_scale_x = creature.in_square_scale_x;
	this->in_square_scale_y = creature.in_square_scale_y;
	this->scale_x = creature.scale_x;
	this->scale_y = creature.scale_y;
	this->set_position(creature.position.x, creature.position.y);
	this->texture = creature.texture;
	this->sprite = creature.sprite;
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(this->scale_x * this->in_square_scale_x, this->scale_y * this->in_square_scale_y);
	return *this;
}

Creature::Creature(Creature&& creature) noexcept(true)
{
	this->in_square_scale_x = 0;
	this->in_square_scale_y = 0;
	this->scale_x = 0;
	this->scale_y = 0;
	this->texture = sf::Texture();
	this->sprite = sf::Sprite();
	this->position = sf::Vector2f();
	this->in_square_scale_x = creature.in_square_scale_x;
	this->in_square_scale_y = creature.in_square_scale_y;
	this->scale_x = creature.scale_x;
	this->scale_y = creature.scale_y;
	this->set_position(creature.position.x, creature.position.y);
	this->texture = creature.texture;
	this->sprite = creature.sprite;
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(this->scale_x * this->in_square_scale_x, this->scale_y * this->in_square_scale_y);
	creature.in_square_scale_x = 0;
	creature.in_square_scale_y = 0;
	creature.scale_x = 0;
	creature.scale_y = 0;
	creature.texture = sf::Texture();
	creature.sprite = sf::Sprite();
	creature.position = sf::Vector2f();
}

Creature& Creature::operator=(Creature&& creature) noexcept(true)
{
	if (this != &creature)
	{
		this->in_square_scale_x = 0;
		this->in_square_scale_y = 0;
		this->scale_x = 0;
		this->scale_y = 0;
		this->texture = sf::Texture();
		this->sprite = sf::Sprite();
		this->position = sf::Vector2f();
		this->in_square_scale_x = creature.in_square_scale_x;
		this->in_square_scale_y = creature.in_square_scale_y;
		this->scale_x = creature.scale_x;
		this->scale_y = creature.scale_y;
		this->set_position(creature.position.x, creature.position.y);
		this->texture = creature.texture;
		this->sprite = creature.sprite;
		this->texture.setSmooth(true);
		this->sprite.setTexture(this->texture);
		this->sprite.setScale(this->scale_x * this->in_square_scale_x, this->scale_y * this->in_square_scale_y);
		creature.in_square_scale_x = 0;
		creature.in_square_scale_y = 0;
		creature.scale_x = 0;
		creature.scale_y = 0;
		creature.texture = sf::Texture();
		creature.sprite = sf::Sprite();
		creature.position = sf::Vector2f();
	}
	return *this;
}

float Creature::get_in_square_scale_x() const
{
	return this->in_square_scale_x;
}

float Creature::get_in_square_scale_y() const
{
	return this->in_square_scale_y;
}

float Creature::get_scale_x() const
{
	return this->scale_x;
}
float Creature::get_scale_y() const
{
	return this->scale_y;
}

unsigned int Creature::get_rect_x() const
{
	return this->rect_x;
}

unsigned int Creature::get_rect_y() const
{
	return this->rect_y;
}

void Creature::set_position(float x, float y)
{
	if (x < 0 || y < 0)
	{
		throw InvalidPositionException();
	}
	//unsigned int x_w = this->window_size.x / 16;
	//unsigned int y_w = this->window_size.y / 16;
	//float scale_x = float(x_w) / this->sprite.getLocalBounds().width;
	//float scale_y = float(y_w) / this->sprite.getLocalBounds().height;
	this->position = sf::Vector2f(sf::Vector2f(this->sprite.getLocalBounds().width * this->scale_x * x, this->sprite.getLocalBounds().height * this->scale_y * y));
}

sf::Vector2f Creature::get_position() const
{
	return this->position;
}

sf::Sprite& Creature::get_Sprite_ref()
{
	return this->sprite;
}

sf::Texture& Creature::get_Texture_ref()
{
	return this->texture;
}

void Creature::display(sf::RenderTarget& window) const
{
	window.draw(this->sprite);
}

sf::Sprite Creature::get_Sprite() const
{
	return this->sprite;
}

sf::Texture Creature::get_Texture() const
{
	return this->texture;
}


/*
void NPC::set_Sprite(std::string texture)
{
	this->set_Texture(texture);
	this->get_Sprite().setTexture(this->texture);
	this->get_Sprite().setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	this->sprite.setPosition(sf::Vector2f(0, 0));
	unsigned int x = this->window_size.x / 16;
	unsigned int y = this->window_size.y / 16;
	float scale_x = float(x) / float(this->sprite.getLocalBounds().width);
	float scale_y = float(y) / float(this->sprite.getLocalBounds().height);
	scale_x = 0.6 * scale_x;
	scale_y = 0.6 * scale_y;
	this->sprite.setScale(scale_x, scale_y);
}
*/
/*
void Chicken::set_Sprite(std::string texture)
{
	this->set_Texture(texture);
	this->get_Sprite().setTexture(this->texture);
	this->get_Sprite().setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	this->sprite.setPosition(sf::Vector2f(0, 0));
	unsigned int x = this->window_size.x / 16;
	unsigned int y = this->window_size.y / 16;
	float scale_x = float(x) / float(this->sprite.getLocalBounds().width);
	float scale_y = float(y) / float(this->sprite.getLocalBounds().height);
	scale_x = 0.6 * scale_x;
	scale_y = 0.6 * scale_y;
	this->sprite.setScale(scale_x, scale_y);

}
*/

/*
void Chicken::set_position(float x, float y)
{
	if (x < 0 || y < 0)
	{
		throw InvalidPositionException();
	}
	unsigned int x_w = this->window_size.x / 16;
	unsigned int y_w = this->window_size.y / 16;
	float scale_x = float(x_w) / this->sprite.getLocalBounds().width;
	float scale_y = float(y_w) / this->sprite.getLocalBounds().height;
	this->position = sf::Vector2f(sf::Vector2f(this->sprite.getLocalBounds().width * scale_x * x, this->sprite.getLocalBounds().height * scale_y * y));
}
*/
/*
void NPC::set_position(float x, float y)
{
	if (x < 0 || y < 0)
	{
		throw InvalidPositionException();
	}
	unsigned int x_w = this->window_size.x / 16;
	unsigned int y_w = this->window_size.y / 16;
	float scale_x = float(x_w) / this->sprite.getLocalBounds().width;
	float scale_y = float(y_w) / this->sprite.getLocalBounds().height;
	this->position = sf::Vector2f(sf::Vector2f(this->sprite.getLocalBounds().width * scale_x * x, this->sprite.getLocalBounds().height * scale_y * y));

}
*/

NPC::NPC(std::string texture, unsigned int width, unsigned int height, float in_square_scale_x, float in_square_scale_y, sf::Vector2i pos, unsigned int rect_x, unsigned int rect_y) : Creature(texture, width, height, in_square_scale_x, in_square_scale_y, pos, rect_x, rect_y)
{
	//this->width = 72;
	//this->height = 50;
	//this->set_Sprite(texture);
	//this->texture.loadFromFile("images/walk_leftm.png");
	//this->sprite.setTexture(this->texture);
	//this->currentFrame = sf::IntRect(0, 0, 72, 50);
	//this->sprite.setTextureRect(sf::IntRect(0, 0, 72, 50));
	//this->set_position(xPos, yPos);
	//this->sprite.setPosition(this->position);
	this->startGame = false;
}

NPC::NPC() : Creature()
{
	this->set_Texture("images/walk_leftm.png");
	this->startGame = false;
}

NPC::NPC(const NPC& npc) : Creature(npc)
{
	this->startGame = npc.startGame;
	this->talkTexture = npc.talkTexture;
}

NPC::NPC(NPC&& npc) noexcept(true) : Creature(std::move(npc))
{
	this->talkTexture = sf::Texture();
	this->startGame = bool();
	this->talkTexture = npc.talkTexture;
	this->startGame = npc.startGame;
	npc.talkTexture = sf::Texture();
	npc.startGame = bool();
}

NPC& NPC::operator=(const NPC& npc)
{
	Creature::operator=(npc);
	this->startGame = npc.startGame;
	this->talkTexture = npc.talkTexture;
	return *this;
}

NPC& NPC::operator=(NPC&& npc) noexcept(true)
{
	Creature::operator=(std::move(npc));
	if (this != &npc)
	{
		this->startGame = bool();
		this->talkTexture = npc.talkTexture;
		this->startGame = npc.startGame;
		npc.talkTexture = sf::Texture();
		npc.startGame = bool();
	}
	return *this;
}

bool NPC::getStartGame() {
	return this->startGame;
}

void NPC::talk(int index) {
	sf::Event event;
	sf::RenderWindow talkWindow(sf::VideoMode::getFullscreenModes()[0], "Let's play!", sf::Style::Fullscreen);
	sf::Sprite talkBackground;
	sf::Texture talkTexture;
	talkTexture.loadFromFile("images/talk" + std::to_string(index) + ".png");
	talkBackground.setTexture(talkTexture);
	float scale_x_temp = float(talkWindow.getSize().x) / float(talkBackground.getLocalBounds().width);
	float scale_y_temp = float(talkWindow.getSize().y) / float(talkBackground.getLocalBounds().height);
	talkBackground.setScale(scale_x_temp, scale_y_temp);
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

Chicken::Chicken(std::string texture, unsigned int width, unsigned int height, float in_square_scale_x, float in_square_scale_y, sf::Vector2i pos, unsigned int rect_x, unsigned int rect_y, int move_up_down, int move_left_right, unsigned int distance_max) : Creature(texture, width, height, in_square_scale_x, in_square_scale_y, pos, rect_x, rect_y) {
	//this->width = 29;
	//this->height = 48;
	//this->set_Sprite(texture);
	//this->set_position(x, y);
	//this->sprite.setPosition(this->position);
	//this->moving_left_right = move_left_right;
	//this->moving_up_down = move_up_down;
	this->wholeFrame.loadFromFile(texture);
	this->wholeSprite.setTexture(this->wholeFrame);
	this->stop = false;
	this->currentFrame = sf::IntRect(0, 0, rect_x, rect_y);
	this->distance = 0;
	this->music_path = "music/chicken.ogg";
	if (move_left_right != 0)
		this->moving_left_right = this->sprite.getLocalBounds().height * this->sprite.getScale().y / move_left_right;
	else
		this->moving_left_right = 0;
	if (move_up_down != 0)
		this->moving_up_down = this->sprite.getLocalBounds().width * this->sprite.getScale().x / move_up_down;
	else
		this->moving_up_down = 0;
	this->distance_max = distance_max;
}

Chicken::Chicken() : Creature()
{
	this->wholeFrame.loadFromFile("images/chicken_walk_left.png");
	this->wholeSprite.setTexture(this->wholeFrame);
	this->stop = false;
	this->moving_left_right = 2;
	this->moving_up_down = 2;
	this->currentFrame = sf::IntRect(0, 0, sf::VideoMode::getFullscreenModes()[0].width / 16, sf::VideoMode::getFullscreenModes()[0].height / 16);
	this->distance = 0;
	this->distance_max = 16;
	this->music_path = "music/chicken.ogg";
	this->moving_up_down = this->sprite.getLocalBounds().height * this->sprite.getScale().y / 16;
	this->moving_left_right = this->sprite.getLocalBounds().width * this->sprite.getScale().x / 16;
}

Chicken::Chicken(const Chicken& chicken) : Creature(chicken)
{
	this->wholeFrame = chicken.wholeFrame;
	this->wholeSprite = chicken.wholeSprite;
	this->wholeSprite.setTexture(this->wholeFrame);
	this->stop = chicken.stop;
	this->moving_left_right = chicken.moving_left_right;
	this->moving_up_down = chicken.moving_up_down;
	this->currentFrame = chicken.currentFrame;
	this->distance = chicken.distance;
	this->music_path = chicken.music_path;
	this->animationTimer = chicken.animationTimer;
	this->distance_max = chicken.distance_max;
}

Chicken::Chicken(Chicken&& chicken) noexcept(true) : Creature(std::move(chicken))
{
	this->wholeFrame = sf::Texture();
	this->wholeSprite = sf::Sprite();
	this->stop = bool();
	this->moving_left_right = int();
	this->moving_up_down = int();
	this->currentFrame = sf::IntRect();
	this->distance = unsigned int();
	this->music_path = std::string();
	this->animationTimer = sf::Clock();
	this->distance_max = unsigned int();
	this->wholeFrame = chicken.wholeFrame;
	this->wholeSprite = chicken.wholeSprite;
	this->wholeSprite.setTexture(this->wholeFrame);
	this->stop = chicken.stop;
	this->moving_left_right = chicken.moving_left_right;
	this->moving_up_down = chicken.moving_up_down;
	this->currentFrame = chicken.currentFrame;
	this->distance = chicken.distance;
	this->music_path = chicken.music_path;
	this->animationTimer = chicken.animationTimer;
	this->distance_max = chicken.distance_max;
	chicken.wholeFrame = sf::Texture();
	chicken.wholeSprite = sf::Sprite();
	chicken.stop = bool();
	chicken.moving_left_right = int();
	chicken.moving_up_down = int();
	chicken.currentFrame = sf::IntRect();
	chicken.distance = unsigned int();
	chicken.music_path = std::string();
	chicken.animationTimer = sf::Clock();
	chicken.distance_max = unsigned int();
}

Chicken& Chicken::operator=(const Chicken& chicken)
{
	Creature::operator=(chicken);
	this->wholeFrame = chicken.wholeFrame;
	this->wholeSprite = chicken.wholeSprite;
	this->wholeSprite.setTexture(this->wholeFrame);
	this->stop = chicken.stop;
	this->moving_left_right = chicken.moving_left_right;
	this->moving_up_down = chicken.moving_up_down;
	this->currentFrame = chicken.currentFrame;
	this->distance = chicken.distance;
	this->music_path = chicken.music_path;
	this->animationTimer = chicken.animationTimer;
	this->distance_max = chicken.distance_max;
	return *this;
}

Chicken& Chicken::operator=(Chicken&& chicken) noexcept(true)
{
	Creature::operator=(std::move(chicken));
	if (this != &chicken)
	{
		this->wholeFrame = sf::Texture();
		this->wholeSprite = sf::Sprite();
		this->stop = bool();
		this->moving_left_right = int();
		this->moving_up_down = int();
		this->currentFrame = sf::IntRect();
		this->distance = unsigned int();
		this->music_path = std::string();
		this->animationTimer = sf::Clock();
		this->distance_max = unsigned int();
		this->wholeFrame = chicken.wholeFrame;
		this->wholeSprite = chicken.wholeSprite;
		this->wholeSprite.setTexture(this->wholeFrame);
		this->stop = chicken.stop;
		this->moving_left_right = chicken.moving_left_right;
		this->moving_up_down = chicken.moving_up_down;
		this->currentFrame = chicken.currentFrame;
		this->distance = chicken.distance;
		this->music_path = chicken.music_path;
		this->animationTimer = chicken.animationTimer;
		this->distance_max = chicken.distance_max;
		chicken.wholeFrame = sf::Texture();
		chicken.wholeSprite = sf::Sprite();
		chicken.stop = bool();
		chicken.moving_left_right = int();
		chicken.moving_up_down = int();
		chicken.currentFrame = sf::IntRect();
		chicken.distance = unsigned int();
		chicken.music_path = std::string();
		chicken.animationTimer = sf::Clock();
		chicken.distance_max = unsigned int();
	}
	return *this;
}


void Chicken::move()
{
	if (!stop)
	{
		if (this->distance >= this->distance_max)
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

/*
sf::Vector2f Chicken::get_position() const
{
	return this->position;
}
*/

void Chicken::display(sf::RenderTarget& window) const
{
	Creature::display(window);
}

sf::Sprite Chicken::get_Sprite() const
{
	return Creature::get_Sprite();
}

void Chicken::change_animation()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
		if (this->currentFrame.left >= this->wholeSprite.getLocalBounds().width - this->sprite.getLocalBounds().width){
			this->currentFrame.left = 0;
		}
		this->currentFrame.left += this->currentFrame.width;
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


bool Chicken::get_stop() const
{
	return this->stop;
}

int Chicken::get_moving_up_down() const
{
	return this->moving_up_down;
}

int Chicken::get_moving_left_right() const
{
	return this->moving_left_right;
}

unsigned int Chicken::get_distance() const
{
	return this->distance;
}

unsigned int Chicken::get_distance_max() const
{
	return this->distance_max;
}

sf::IntRect Chicken::get_currentFrame() const
{
	return this->currentFrame;
}

sf::Texture Chicken::get_WholeFrame() const
{
	return this->wholeFrame;
}

sf::Sprite Chicken::get_WholeSprite() const
{
	return this->wholeSprite;
}

sf::Clock Chicken::get_animationTimer() const
{
	return this->animationTimer;
}