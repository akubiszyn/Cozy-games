#include "Snakeminigame.h"
#include<sstream>


void Snakegame::update_game(sf::RenderWindow& window) {
	while (window.isOpen())
	{
		while (window.pollEvent(this->event)) {
			if (this->event.type == sf::Event::Closed) {
				window.close();
			}
		}

		this->updatePoints();
		this->player.updateMovement(this->map);
		this->update_world_collision(player, window);
		this->chicken.update_Movement(player, snake);
		if (this->chicken.check_if_colliding(player, snake) == false) {
			this->game_over(window);
			break;
		}
		this->chicken.reset(player, snake);

		//Draw
		window.clear();
		this->map.update_game_map(window);

		//Draw everything

		this->render_text(window);
		this->player.render(window);
		this->chicken.render(window);
		for (Chickens* element : this->snake) {
			(*element).render(window);
		}
		window.display();

	}
}
Snakegame::~Snakegame()
{
	for (auto& i : snake) {
		delete i;
	}
}
void Snakegame::start(sf::RenderWindow& window) {
	initWindow(window);
	update_game(window);
}

void Snakegame::initWindow(sf::RenderWindow& window) {
	window.create(sf::VideoMode(640, 480), "Snake game", sf::Style::Default);
	window.setFramerateLimit(60);
}
void Snakegame::initPlayer() {
}

void Snakegame::game_over(sf::RenderWindow& window)
{
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(50);
	this->pointText.setFillColor(sf::Color::Red);
	this->pointText.setPosition(
	window.getSize().x / 3.f * 2 - this->gameOverText.getGlobalBounds().width / 0.2f,
	window.getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
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
	if (player.get_shape().getGlobalBounds().left < 0.f)
	{
		player.get_shape().setPosition(0.f, player.get_shape().getGlobalBounds().top);
	}
	//Right world collison
	else if (player.get_shape().getGlobalBounds().left + player.get_shape().getGlobalBounds().width >= window.getSize().x)
	{
		player.get_shape().setPosition(window.getSize().x - player.get_shape().getGlobalBounds().width,player.get_shape().getGlobalBounds().top);
	}

	//Top world collision
	if (player.get_shape().getGlobalBounds().top < 0.f)
	{
		player.get_shape().setPosition(player.get_shape().getGlobalBounds().left, 0.f);
	}
	//Bottom world collision
	else if (player.get_shape().getGlobalBounds().top + player.get_shape().getGlobalBounds().height >= window.getSize().y)
	{
		player.get_shape().setPosition(player.get_shape().getGlobalBounds().left, window.getSize().y - player.get_shape().getGlobalBounds().height);
	}
}

void Snakegame::set_result()
{
	result = snake.size();
}

int Snakegame::get_result()
{
	return this->result;
}

void Snakegame::updatePoints()
{
	set_result();
	std::stringstream ss;

	ss << "Score: " << this->get_result() << "\n";

	this->pointText.setString(ss.str());
}

void Snakegame::render_text(sf::RenderWindow& window)
{
	this->font.loadFromFile("fonts/arial.ttf");
	this->pointText.setFont(this->font);
	window.draw(this->pointText);
}


bool Chickens::check_if_colliding(Player player, std::vector<Chickens*>& snake)
{
	
	for (int i = 4; i < snake.size(); i++) {
		if (this->check_collision(player, snake[i]) == false) {
			count++;
		}
		if( count == 5){
			return false;
		}
	}	
}

bool Chickens::check_collision(Player player, Chickens* chicken)
{
	sf::FloatRect chicken_rect = (*chicken).sprite.getGlobalBounds();
	sf::FloatRect check = sf::FloatRect(chicken_rect.left, chicken_rect.top, chicken_rect.width, chicken_rect.height);
	sf::FloatRect player_rect = player.get_shape().getGlobalBounds();
	sf::FloatRect check2 = sf::FloatRect(player_rect.left, player_rect.top, player_rect.width, player_rect.height);
	if (check.intersects(check2)) {
		return false;
	}
	return true;
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
		if (x_before + new_x > 640) {
			new_x = 640 - x_before;
		}
		if (y_before + new_y > 480) {
			new_y = 480 - y_before;
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
	this->textures["chickens"]->loadFromFile("images/chicken_walk_right.png");
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
		float x = player.get_shape().getPosition().x;
		float y = player.get_shape().getPosition().y;
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


