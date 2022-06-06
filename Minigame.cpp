#include "Minigame.h"

//Private functions
/*
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
}
*/
/*
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}
*/
void Clicking_minigame::setFonts()
{
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void Clicking_minigame::setText()
{
	//this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString("NONE");
}
/*
void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}
*/
//Constructors / Destructors
Clicking_minigame::Clicking_minigame()
{
	this->end = false;
	this->score = 0;
	this->to_lose = 20;
	this->food_timer_max = 20.f;
	this->food_timer = this->food_timer_max;
	this->Max_number_of_food_objects = 5;
	this->mouse_is_pressed = false;
	this->textures_info = { {0, "images/banana.png"}, {1, "images/tomato.png"}, {2, "images/apple.png"}, {3, "images/orange.png"}, {4, "images/watermelon.png"}, {5, "images/rotten_banana.png"}, {6, "images/rotten_tomato.png"}, {7, "images/rotten_apple.png"} };
	this->background_texture.loadFromFile("images/background.png");
	this->background.setTextureRect(sf::IntRect(0, 0, 800, 600));
	this->movement_speed = 1.f;
	this->movement_left_right = 0.f;
	for (int i = 0; i < 8; i++)
	{
		this->textures[i].loadFromFile(this->textures_info[i]);
	}
	this->setFonts();
	this->setText();
}

Clicking_minigame::~Clicking_minigame()
{
	//delete this->window;
}

//Accessors
/*
const bool Game::running() const
{
	return this->window->isOpen();
}
*/
bool Clicking_minigame::get_end() const
{
	return this->end;
}

//Functions
void Clicking_minigame::Spawn_enemy(sf::RenderWindow& window)
{
	/*
		@return void
		Spawns enemies and sets their types and colors. Spawns them at random positions.
		-Sets a random type (diff).
		-Sets a random position.
		-Sets a random color.
		-Adds enemy to the vector.
	*/
	/*
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	*/
	this->food_object.setTextureRect(sf::IntRect(0, 0, 100, 100));
	this->food_object.setPosition(sf::Vector2f(static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->food_object.getTextureRect().width)), 0.f));
	//Randomize enemy type
	int type = rand() % 8;

	switch (type)
	{
	case 0:
		this->food_object.setTexture(this->textures[0]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 40, 40));
		//this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		this->food_object.setTexture(this->textures[1]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 30, 30));
		//this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		this->food_object.setTexture(this->textures[2]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 50, 50));
		//this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		this->food_object.setTexture(this->textures[3]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 70, 70));
		//this->enemy.setFillColor(sf::Color::Red);
		break;
	case 4:
		this->food_object.setTexture(this->textures[4]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 100, 100));
		//this->enemy.setFillColor(sf::Color::Green);
		break;
	case 5:
		this->food_object.setTexture(this->textures[5]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 39, 39));
		//this->enemy.setFillColor(sf::Color::Green);
		break;
	case 6:
		this->food_object.setTexture(this->textures[6]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 29, 29));
		//this->enemy.setFillColor(sf::Color::Green);
		break;
	case 7:
		this->food_object.setTexture(this->textures[7]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 49, 49));
		//this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		this->food_object.setTexture(this->textures[0]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 40, 40));
		//this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}

	//Spawn the enemy
	this->food.push_back(this->food_object);
}
/*
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}
*/
void Clicking_minigame::updateMousePositions(sf::RenderWindow& window)
{
	/**
		@ return void
		Updates the mouse positions:
		- Mouse position relative to window (Vector2i)
	*/

	this->mouse_window = sf::Mouse::getPosition(window);
	this->mouse_general = window.mapPixelToCoords(this->mouse_window);
}

void Clicking_minigame::updateText()
{
	std::stringstream ss;

	ss << "Score: " << this->get_score() << "\n"
		<< "To_lose: " << this->to_lose << "\n";

	this->text.setString(ss.str());
}

void Clicking_minigame::updateEnemies(sf::RenderWindow& window)
{
	/**
		@return void
		Updates the enemy spawn timer and spawns enemies
		When the total amount of enemies is smaller than the maximum.
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen. //TODO
	*/

	//Updating the timer for enemy spawning
	if (this->food.size() < this->Max_number_of_food_objects)
	{
		if (this->food_timer >= this->food_timer_max)
		{
			//Spawn the enemy and reset the timer
			this->Spawn_enemy(window);
			this->food_timer = 0.f;
		}
		else
			this->food_timer += 1.f;
	}

	//Moving and updating enemies
	for (int i = 0; i < this->food.size(); i++)
	{
		bool deleted = false;

		this->food[i].move(0.f, this->movement_speed);

		if (this->food[i].getPosition().y > window.getSize().y)
		{
			this->food.erase(this->food.begin() + i);
			if(this->food[i].getTextureRect() != sf::IntRect(0, 0, 29, 29) && this->food[i].getTextureRect() != sf::IntRect(0, 0, 39, 39) && this->food[i].getTextureRect() != sf::IntRect(0, 0, 49, 49))
				this->to_lose -= 1;
			std::cout << "to_lose: " << this->to_lose << "\n";
		}
	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouse_is_pressed == false)
		{
			this->mouse_is_pressed = true;
			bool deleted = false;
			for (size_t i = 0; i < this->food.size() && deleted == false; i++)
			{
				if (this->food[i].getGlobalBounds().contains(this->mouse_general))
				{
					//Gain points
					if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 40, 40))
					{
						this->score += 7;
						if (this->movement_speed < 8.f && this->movement_speed != 0)
							this->movement_speed += 0.5;
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 30, 30))
					{
						this->score += 10;
						if (this->movement_speed < 8.f && this->movement_speed != 0)
							this->movement_speed += 0.5;
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 50, 50))
					{
						this->score += 5;
						if (this->movement_speed < 8.f && this->movement_speed != 0)
							this->movement_speed += 0.5;
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 70, 70))
					{
						this->score += 3;
						if (this->movement_speed < 8.f && this->movement_speed != 0)
							this->movement_speed += 0.5;
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 100, 100))
					{
						this->score += 1;
						if (this->movement_speed < 8.f && this->movement_speed != 0)
							this->movement_speed += 0.5;
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 39, 39))
					{
						this->to_lose -= 2;
						//this->movement_speed = -this->movement_speed;
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 29, 29))
					{
						this->to_lose -= 1;
						//this->movement_speed = -this->movement_speed;
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 49, 49))
					{
						this->to_lose -= 3;
					}


					std::cout << "Points: " << this->to_lose << "\n";

					//Delete the enemy
					deleted = true;
					this->food.erase(this->food.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouse_is_pressed = false;
	}
}

void Clicking_minigame::start(sf::RenderWindow& window)
{
	window.create(sf::VideoMode(800, 600), "Clicking_minigame", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
	std::srand(static_cast<unsigned int>(time(NULL)));
	while (window.isOpen() && !this->get_end())
	{
		while (window.pollEvent(this->event))
		{
			switch (this->event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}
		if (this->end == false)
		{
			this->updateMousePositions(window);

			this->updateText();

			this->updateEnemies(window);
		}
		if (this->to_lose <= 0)
			this->end = true;
		window.clear();
		this->background.setTexture(this->background_texture);
		window.draw(this->background);
		this->displayEnemies(window);
		this->displayText(window);
		window.display();
	}
}
/*
void Clicking_minigame::update(sf::RenderWindow& window)
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}

	//End game condition
	if (this->health <= 0)
		this->endGame = true;
}
*/
void Clicking_minigame::displayText(sf::RenderTarget& target)
{
	this->text.setFont(this->font);
	target.draw(this->text);
}

void Clicking_minigame::displayEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->food)
	{
		target.draw(e);
	}
}

unsigned int Clicking_minigame::get_score() const
{
	return this->score;
}
/*
void Clicking_minigame::display()
{
	
		@return void
		- clear old frame
		- render objects
		- display frame in window
		Renders the game objects.

	this->window->clear();

	//Draw game objects
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->display();
}*/