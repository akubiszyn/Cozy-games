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
	this->points = 0;
	this->health = 20;
	this->Enemy_timer_max = 20.f;
	this->Enemy_timer = this->Enemy_timer_max;
	this->Max_number_of_enemies = 5;
	this->mouse_is_pressed = false;
	this->textures_info = { {0, "images/banana.png"}, {1, "images/tomato.png"}, {2, "images/apple.png"}, {3, "images/orange.png"}, {4, "images/watermelon.png"}};
	this->background_texture.loadFromFile("images/background.png");
	this->background.setTextureRect(sf::IntRect(0, 0, 800, 600));
	for (int i = 0; i < 5; i++)
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
	this->enemy.setTextureRect(sf::IntRect(0, 0, 100, 100));
	this->enemy.setPosition(sf::Vector2f(static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->enemy.getTextureRect().width)), 0.f));
	//Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setTexture(this->textures[0]);
		this->enemy.setTextureRect(sf::IntRect(0, 0, 10, 10));
		//this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		this->enemy.setTexture(this->textures[1]);
		this->enemy.setTextureRect(sf::IntRect(0, 0, 30, 30));
		//this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		this->enemy.setTexture(this->textures[2]);
		this->enemy.setTextureRect(sf::IntRect(0, 0, 50, 50));
		//this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		this->enemy.setTexture(this->textures[3]);
		this->enemy.setTextureRect(sf::IntRect(0, 0, 70, 70));
		//this->enemy.setFillColor(sf::Color::Red);
		break;
	case 4:
		this->enemy.setTexture(this->textures[4]);
		this->enemy.setTextureRect(sf::IntRect(0, 0, 100, 100));
		//this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		this->enemy.setTexture(this->textures[0]);
		this->enemy.setTextureRect(sf::IntRect(0, 0, 10, 10));
		//this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}

	//Spawn the enemy
	this->enemies.push_back(this->enemy);
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

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n";

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
	if (this->enemies.size() < this->Max_number_of_enemies)
	{
		if (this->Enemy_timer >= this->Enemy_timer_max)
		{
			//Spawn the enemy and reset the timer
			this->Spawn_enemy(window);
			this->Enemy_timer = 0.f;
		}
		else
			this->Enemy_timer += 1.f;
	}

	//Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 1.f);

		if (this->enemies[i].getPosition().y > window.getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
		}
	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouse_is_pressed == false)
		{
			this->mouse_is_pressed = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mouse_general))
				{
					//Gain points
					if (this->enemies[i].getTextureRect() == sf::IntRect(0, 0, 10, 10))
						this->points += 10;
					else if (this->enemies[i].getTextureRect() == sf::IntRect(0, 0, 30, 30))
						this->points += 7;
					else if (this->enemies[i].getTextureRect() == sf::IntRect(0, 0, 50, 50))
						this->points += 5;
					else if (this->enemies[i].getTextureRect() == sf::IntRect(0, 0, 70, 70))
						this->points += 3;
					else if (this->enemies[i].getTextureRect() == sf::IntRect(0, 0, 100, 100))
						this->points += 1;

					std::cout << "Points: " << this->points << "\n";

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
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
		while (window.pollEvent(this->ev))
		{
			switch (this->ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
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
		if (this->health <= 0)
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
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

unsigned int Clicking_minigame::get_score() const
{
	return this->points;
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