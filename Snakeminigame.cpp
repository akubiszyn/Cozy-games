#include "Snakeminigame.h"
#include<sstream>


void Snakegame::update_game(sf::RenderWindow& window) {
	sf::Music music;
	music.openFromFile("music/chicken.ogg");
	music.setLoop(true);
	music.play();
	while (window.isOpen())
	{
		while (window.pollEvent(this->event)) {
			if (this->event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			this->end = true;
		}

		this->updatePoints();
		this->player.updateMovement();
		this->update_world_collision(player, window);
		this->chicken.update_Movement(player, snake);
		if (this->chicken.check_if_colliding(player, snake) == false) {
			music.stop();
			this->game_over(window);
			break;
		}
		this->chicken.reset(player, snake);

		//Draw
		window.clear();
		this->worldBackground.setTexture(this->worldBackgroundTex);
		window.draw(this->worldBackground);

		//Draw everything
		this->chicken.render(window);
		this->render_text(window);
		this->player.render(window);
		for (Chickens* element : this->snake) {
			(*element).render(window);

		}
		window.display();

	}
}
Snakegame::Snakegame()
{
	this->restartGame();

}
Snakegame::~Snakegame()
{
	for (auto& i : snake) {
		delete i;
	}
	snake.clear();

}
void Snakegame::start(sf::RenderWindow& window) {
	this->restartGame();
	initWindow(window);
	update_game(window);
}

void Snakegame::restartGame()
{
	for (auto& i : snake) {
		delete i;
	}
	this->player.get_sprite_ref().setPosition(500, 500);
	snake.clear();
	this->worldBackgroundTex.loadFromFile("images/grass_template.jpg");
	this->chicken.get_chicken_restart();
	this->result = 0;
	this->end = false;
	this->startGame = false;
}

void Snakegame::initWindow(sf::RenderWindow& window) {
	window.create(sf::VideoMode::getFullscreenModes()[0], "Snake game", sf::Style::Default);
	window.setFramerateLimit(60);
}

void Snakegame::game_over(sf::RenderWindow& window)
{
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(50);
	this->pointText.setFillColor(sf::Color::Black);
	this->pointText.setPosition(
	window.getSize().x / 3.f * 2 - this->gameOverText.getGlobalBounds().width / 0.2f,
	window.getSize().y / 3.f * 2 - this->gameOverText.getGlobalBounds().height / 2.f);
	this->worldBackgroundTex.loadFromFile("images/game_over.png");
	this->worldBackground.setTexture(this->worldBackgroundTex);
	while (window.isOpen())
	{
		while (window.pollEvent(this->event)) {
			if (this->event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			this->end = true;
		}
		this->updatePoints();
		window.clear();
		window.draw(this->worldBackground);
		this->render_text(window);
		window.display();
	}
}

void Snakegame::update_world_collision(Player player, sf::RenderWindow& window)
{
	//Left world collision
	if (player.get_sprite().getGlobalBounds().left < 0.f)
	{
		this->chicken.set_if_colliding(false);

	}
	//Right world collison
	else if (player.get_sprite().getGlobalBounds().left + player.get_sprite().getGlobalBounds().width >= window.getSize().x)
	{
		this->chicken.set_if_colliding(false);
	}

	//Top world collision
	if (player.get_sprite().getGlobalBounds().top < 0.f)
	{
		this->chicken.set_if_colliding(false);
	}
	//Bottom world collision
	else if (player.get_sprite().getGlobalBounds().top + player.get_sprite().getGlobalBounds().height >= window.getSize().y)
	{
		this->chicken.set_if_colliding(false);
	}
}

void Snakegame::set_result()
{
	result = snake.size();
}

unsigned int Snakegame::get_score() const
{
	return this->result;
}



void Snakegame::updatePoints()
{
	set_result();
	std::stringstream ss;

	ss << "Score: " << this->get_score() << "\n";

	this->pointText.setString(ss.str());
}

void Snakegame::render_text(sf::RenderWindow& window)
{
	this->font.loadFromFile("fonts/cozy_caps.ttf");
	this->pointText.setFont(this->font);
	window.draw(this->pointText);
}

bool Snakegame::get_end() const
{
	return end;
}


bool Chickens::check_if_colliding(Player player, std::vector<Chickens*>& snake)
{
	if (if_colliding == false) {
		return false;
	}
	for (int i = 4; i < snake.size(); i++) {
		if (this->check_collision(player, snake[i]) == false) {
			count++;
		}
		if( count == 5){
			if_colliding = false;
			return if_colliding;
		}
	}
}

bool Chickens::check_collision(Player player, Chickens* chicken)
{
	sf::FloatRect chicken_rect = (*chicken).sprite.getGlobalBounds();
	sf::FloatRect check = sf::FloatRect(chicken_rect.left, chicken_rect.top, chicken_rect.width, chicken_rect.height);
	sf::FloatRect player_rect = player.get_sprite().getGlobalBounds();
	sf::FloatRect check2 = sf::FloatRect(player_rect.left, player_rect.top, player_rect.width, player_rect.height);
	if (check.intersects(check2)) {
		return false;
	}
	return true;
}

void Chickens::get_chicken_restart()
{
	for (auto& i : textures) {
		delete i.second;
	}
	textures.clear();
	this->set_Sprite(400, 400);
	if_colliding = true;
	count = 0;
	found = true;
}

void Chickens::set_if_colliding(bool set)
{
	this->if_colliding = set;
}

void Chickens::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}



Chickens::Chickens(float x, float y)
{
	this->set_Sprite(x, y);
}

Chickens::~Chickens()
{
	for (auto& i : textures) {
		delete i.second;
	}
	textures.clear();
}

void Chickens::reset(Player player, std::vector<Chickens*> &snake)
{
	//srand((unsigned)time(NULL));
	float x_before = this->sprite.getPosition().x;
	float y_before = this->sprite.getPosition().y;
	if (check_collision(player, this) == false) {
		found = false;
		snake.push_back(new Chickens(x_before, y_before));

	}
	while (found == false) {
		float x = rand() % (640);
		float u = rand() % (500);
		std::cout << x << std::endl;
		float y = rand() % (480);
		float new_x = (x - u);
		float new_y = (y - u);
		if (x_before + new_x < 0) {
			new_x = 0 - x_before;
		}
		if (y_before + new_y < 0) {
			new_y = 0 - y_before;
		}
		if (x_before + new_x > 1366) {
			new_x = 1366 - x_before;
		}
		if (y_before + new_y > 600) {
			new_y = 600 - y_before;
		}
		this->sprite.move(sf::Vector2f(new_x, new_y));


		found = true;

	}
}

void Chickens::set_Sprite(float x, float y)
{
	this->set_Texture();
	texture = this->textures["chickens"];
	this->sprite.setTexture(*texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 29, 48));
	this->currentFrame = sf::IntRect(0, 0, 29, 48);
	this->sprite.setScale(1.0, 1.0);
	this->sprite.setPosition(sf::Vector2f(x, y));
}

void Chickens::set_Texture()
{
	this->textures["chickens"] = new sf::Texture();
	this->textures["chickens"]->loadFromFile("images/chicken_walk_left.png");
}

void Chickens::update_Movement(Player player, std::vector<Chickens*>& snake)
{

	for (int i = (snake.size() - 1); i > 0; i--) {
		float x = snake[i - 1]->get_shape().getPosition().x;
		float y = snake[i - 1]->get_shape().getPosition().y;
		float my_x = snake[i]->get_shape().getPosition().x;
		float my_y = snake[i]->get_shape().getPosition().y;
		if (player.get_dir() == 1) {
			texture->loadFromFile("images/chicken_walk_left.png");
		}
		else if (player.get_dir() == 3) {
			texture->loadFromFile("images/chicken_walk_right.png");
		}
		sf::FloatRect chicken_rect = snake[i]->sprite.getGlobalBounds();
		sf::FloatRect check = sf::FloatRect(chicken_rect.left + (x - my_x) * 0.4f, chicken_rect.top + (y - my_y) * 0.4f, chicken_rect.width, chicken_rect.height);
		sf::FloatRect chicken_rect2 = snake[i-1]->sprite.getGlobalBounds();
		sf::FloatRect check2 = sf::FloatRect(chicken_rect2.left + (x - my_x) * 0.4f, chicken_rect2.top + (y - my_y) * 0.4f, chicken_rect2.width, chicken_rect2.height);
		if (!check.intersects(check2)) {
			snake[i]->sprite.move((x - my_x) * 0.4f, (y - my_y) * 0.4f);
		}

	}
	if (snake.size() != 0) {
		float x = player.get_sprite().getPosition().x;
		float y = player.get_sprite().getPosition().y;
		float my_x = (*snake[0]).sprite.getPosition().x;
		float my_y = (*snake[0]).sprite.getPosition().y;
		if (player.get_dir() == 1) {
			texture->loadFromFile("images/chicken_walk_left.png");
		}
		else if (player.get_dir() == 3) {
			texture->loadFromFile("images/chicken_walk_right.png");
		}
		if(player.get_dir() == 3){
			(*snake[0]).sprite.move((x - my_x - 50) * 0.4f, (y - my_y ) * 0.4f);
		}
		else if (player.get_dir() == 2) {
			(*snake[0]).sprite.move((x - my_x +20 ) * 0.4f, (y - my_y - 80) * 0.4f);
		}
		else if (player.get_dir() == 1) {
			(*snake[0]).sprite.move((x - my_x + 90) * 0.4f, (y - my_y ) * 0.4f);
		}
		else if (player.get_dir() == 0) {
			(*snake[0]).sprite.move((x - my_x + 20) * 0.4f, (y - my_y + 90) * 0.4f);
		}


	}





}

sf::Sprite Chickens::get_shape()
{
	return sprite;
}
