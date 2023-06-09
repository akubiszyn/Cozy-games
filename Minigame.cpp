#include "Minigame.h"

Minigame::~Minigame() {}

void Clicking_minigame::setFonts()
{
	if (!this->font.loadFromFile("fonts/edo.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void Clicking_minigame::setText()
{
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString("NONE");
	this->end_game.setCharacterSize(32);
	this->end_game.setFillColor(sf::Color::Black);
}

void Clicking_minigame::make_end_game(sf::RenderWindow& window)
{
	std::stringstream ss;

	ss << "Your Score: " << this->get_score() << std::endl << "Press Esc to continue.";
	this->end_game.setFont(this->font);
	this->end_game.setString(ss.str());
	this->end_game.setPosition(float(window.getSize().x) / 2.f - this->end_game.getLocalBounds().width, float(window.getSize().y) / 2.f);
}
Clicking_minigame::Clicking_minigame()
{
	this->restartGame();
	this->Max_number_of_food_objects = 5;
	this->mouse_is_pressed = false;
	this->textures_info = { {0, "images/banana.png"}, {1, "images/tomato.png"}, {2, "images/apple.png"}, {3, "images/orange.png"}, {4, "images/watermelon.png"}, {5, "images/rotten_banana.png"}, {6, "images/rotten_tomato.png"}, {7, "images/rotten_apple.png"} };
	this->background_texture.loadFromFile("images/background.png");
	this->background.setTextureRect(sf::IntRect(0, 0, 800, 600));
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

void Clicking_minigame::restartGame() {
	this->end = false;
	this->score = 0;
	this->to_lose = 20;
	this->food_timer_max = 20.f;
	this->food_timer = this->food_timer_max;
	this->movement_speed = 1.f;
	this->movement_left_right = 0.f;
}

bool Clicking_minigame::get_end() const
{
	return this->end;
}

void Clicking_minigame::Spawn_food_object(sf::RenderWindow& window)
{
	this->food_object.setTextureRect(sf::IntRect(0, 0, 100, 100));
	unsigned int x = window.getSize().x / 30;
	float scale_x = float(x) / float(this->food_object.getLocalBounds().width);
	this->food_object.setPosition(sf::Vector2f(static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->food_object.getTextureRect().width * scale_x)), 0.f));
	int type = rand() % 8;

	switch (type)
	{
	case 0:
		this->food_object.setTexture(this->textures[0]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 924, 1439));
		this->scale(window, this->food_object, 45, 45);
		break;
	case 1:
		this->food_object.setTexture(this->textures[1]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 30, 30));
		this->scale(window, this->food_object, 50, 50);
		break;
	case 2:
		this->food_object.setTexture(this->textures[2]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 166, 184));
		this->scale(window, this->food_object, 40, 40);
		break;
	case 3:
		this->food_object.setTexture(this->textures[3]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 70, 70));
		this->scale(window, this->food_object, 35, 35);
		break;
	case 4:
		this->food_object.setTexture(this->textures[4]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 100, 100));
		this->scale(window, this->food_object, 30, 30);
		break;
	case 5:
		this->food_object.setTexture(this->textures[5]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 39, 39));
		this->scale(window, this->food_object, 25, 25);
		break;
	case 6:
		this->food_object.setTexture(this->textures[6]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 29, 29));
		this->scale(window, this->food_object, 20, 20);
		break;
	case 7:
		this->food_object.setTexture(this->textures[7]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 49, 49));
		this->scale(window, this->food_object, 15, 15);
		break;
	default:
		this->food_object.setTexture(this->textures[0]);
		this->food_object.setTextureRect(sf::IntRect(0, 0, 40, 40));
		this->scale(window, this->food_object, 45, 45);
		break;
	}

	this->food.push_back(this->food_object);
}

void Clicking_minigame::updateMousePositions(sf::RenderWindow& window)
{


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

void Clicking_minigame::updateFood(sf::RenderWindow& window)
{


	if (this->food.size() < this->Max_number_of_food_objects)
	{
		if (this->food_timer >= this->food_timer_max)
		{
			this->Spawn_food_object(window);
			this->food_timer = 0.f;
		}
		else
			this->food_timer += 1.f;
	}
	for (int i = 0; i < this->food.size(); i++)
	{
		bool deleted = false;

		this->food[i].move(0.f, this->movement_speed);

		if (this->food[i].getPosition().y > window.getSize().y)
		{
			if (this->food[i].getTextureRect() != sf::IntRect(0, 0, 29, 29) && this->food[i].getTextureRect() != sf::IntRect(0, 0, 39, 39) && this->food[i].getTextureRect() != sf::IntRect(0, 0, 49, 49))
				this->to_lose -= 1;
			this->food.erase(this->food.begin() + i);
			std::cout << "to_lose: " << this->to_lose << "\n";
		}
	}

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
					if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 924, 1439))
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
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 166, 184))
					{
						this->score += 5;
						if (this->movement_speed < 2.f && this->movement_speed != 0)
							this->movement_speed += 0.5;
						else
							this->movement_speed = 2.f;
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
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 29, 29))
					{
						this->to_lose -= 1;
					}
					else if (this->food[i].getTextureRect() == sf::IntRect(0, 0, 49, 49))
					{
						this->to_lose -= 3;
						this->movement_speed = 8.f;
					}


					std::cout << "Points: " << this->to_lose << "\n";

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
	window.create(sf::VideoMode::getFullscreenModes()[0], "Clicking minigame", sf::Style::Fullscreen | sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
	restartGame();
	std::srand(static_cast<unsigned int>(time(NULL)));
	this->scale(window, this->background, 1, 1);
	sf::Music music;
	music.openFromFile("music/Clicking_minigame.ogg");
	music.setLoop(true);
	music.play();
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
					this->end = true;
				break;
			}
		}
		if (this->end == false)
		{
			this->updateMousePositions(window);

			this->updateText();

			this->updateFood(window);
		}
		if (this->to_lose <= 0)
			this->end = true;
		window.clear();
		this->background.setTexture(this->background_texture);
		window.draw(this->background);
		this->displayFood(window);
		this->displayText(window);
		window.display();
	}
	this->make_end_game(window);
	this->background.setTexture(this->background_texture);
	window.draw(this->background);
	window.draw(this->end_game);
	window.display();
	bool wait = true;
	while (wait)
	{
		while (window.isOpen() && wait)
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
						wait = false;
					break;
				}
			}
		}
	}
	music.stop();
}

void Clicking_minigame::displayText(sf::RenderTarget& target)
{
	this->text.setFont(this->font);
	target.draw(this->text);
}

void Clicking_minigame::displayFood(sf::RenderTarget& target)
{

	for (auto& e : this->food)
	{
		target.draw(e);
	}
}

unsigned int Clicking_minigame::get_score() const
{
	return this->score;
}

void Clicking_minigame::scale(sf::RenderWindow& window, sf::Sprite& sprite, int divider_width, int divider_height)
{
	unsigned int x = window.getSize().x / divider_width;
	unsigned int y = window.getSize().y / divider_height;
	float scale_x = float(x) / float(sprite.getLocalBounds().width);
	float scale_y = float(y) / float(sprite.getLocalBounds().height);
	sprite.setScale(scale_x, scale_y);
}


JumpingMinigame::JumpingMinigame()
{
	this->chickenWidth = 80;
	this->chickenHeight = 80;
	this->platformWidth = 72;
	this->platformHeight = 17;
	this->width = 400;
	this->height = 533;
	this->xPos = 100;
	this->yPos = 100;
	this->dXPos = 0;
	this->dYPos = 0;
	this->fallingSpeed = 0.2;
	this->screenBorder = 200;
	this->end = false;
	this->score = 0;
	this->backgroundT.loadFromFile("images/jump_game_background.png");
	this->platformT.loadFromFile("images/platform.png");
	this->chickenT.loadFromFile("images/small_single_chicken.png");
	this->gameOverT.loadFromFile("images/game_over.png");
	this->background.setTexture(backgroundT);
	this->platform.setTexture(platformT);
	this->chicken.setTexture(chickenT);
	this->gameOver.setTexture(gameOverT);
	this->adjustChicken(5.0, 16, 16);
	this->adjustPlatforms(3.0, 24, 7);
	this->setFonts();
	this->setText();
}

int JumpingMinigame::getWidth() {
	return this->width;
}

int JumpingMinigame::getHeight() {
	return this->height;
}

int JumpingMinigame::getXPos() {
	return this->xPos;
}
int JumpingMinigame::getYPos() {
	return this->yPos;
}

JumpingMinigame::~JumpingMinigame()
{
	//delete this->window;
}

void JumpingMinigame::setFonts()
{
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void JumpingMinigame::setText()
{
	//this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString("NONE");
}

void JumpingMinigame::updateText()
{
	std::stringstream ss;

	ss << "Score: " << this->get_score() << "\n";

	this->text.setString(ss.str());
}

void JumpingMinigame::adjustPlatforms(float scale, int width, int height) {
	this->platform.setTextureRect(sf::IntRect(0, 0, width, height));
	this->platform.setScale(scale, scale);
}

void JumpingMinigame::adjustChicken(float scale, int width, int height) {
	this->chicken.setTextureRect(sf::IntRect(0, 0, width, height));
	this->chicken.setScale(scale, scale);
}

void JumpingMinigame::moveChicken() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->startGame = true;
		this->xPos += 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->startGame = true;
		this->xPos -= 3;
	}
}

void JumpingMinigame::generatePlatformsPositions() {
	for (int i = 0; i < 10; i++)
	{
		this->platforms[i].x = rand() % this->width;
		this->platforms[i].y = rand() % this->height;
	}
}

void JumpingMinigame::updatePlatformsPositions() {
	for (int i = 0; i < 10; i++)
	{
		this->yPos = this->screenBorder;
		this->platforms[i].y = this->platforms[i].y - dYPos;
		if (this->platforms[i].y > this->height) {
			this->platforms[i].y = 0;
			this->platforms[i].x = rand() % this->width;
		}
	}
}

void JumpingMinigame::platformJump() {
	for (int i = 0; i < 10; i++) {
		if ((this->xPos + this->chickenWidth / 2 > this->platforms[i].x)
			&& (this->xPos + this->chickenWidth / 4 < this->platforms[i].x + this->platformWidth)
			&& (this->yPos + this->chickenHeight - 10 > this->platforms[i].y)
			&& (this->yPos + this->chickenHeight - 10 < this->platforms[i].y + this->platformHeight)
			&& (this->dYPos > 0)) {
			this->dYPos = -10;
			this->score++;
		}

	}
}

void JumpingMinigame::displayText(sf::RenderTarget& target)
{
	this->text.setFont(this->font);
	target.draw(this->text);
}

void JumpingMinigame::play(sf::RenderWindow& window) {
	this->chicken.setPosition(this->xPos, this->yPos);
	this->background.setTexture(this->backgroundT);
	window.draw(this->background);
	this->chicken.setTexture(this->chickenT);
	window.draw(this->chicken);
	displayText(window);
	for (int i = 0; i < 10; i++)
	{
		this->platform.setPosition(this->platforms[i].x, this->platforms[i].y);
		this->platform.setTexture(this->platformT);
		window.draw(this->platform);
	}
	window.display();
}

void JumpingMinigame::restartGame() {
	this->startGame = false;
	this->xPos = 100;
	this->yPos = 100;
	this->dXPos = 0;
	this->dYPos = 0;
	this->end = false;
	this->score = 0;
}


void JumpingMinigame::start(sf::RenderWindow& window)
{
	restartGame();
	srand(time(0));
	window.create(sf::VideoMode(this->width, this->height), "Jumping_minigame", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	generatePlatformsPositions();
	while (window.isOpen())
	{

		//text.setString(std::to_string(score));
		//sf::Event e;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (startGame) {
			this->dYPos += fallingSpeed;
			this->yPos += this->dYPos;
		}

		if (this->yPos > this->height - 30) {
			end = true;
			this->gameOver.setTexture(this->gameOverT);
			window.draw(gameOver);
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}

		if (this->yPos < this->screenBorder) {
			updatePlatformsPositions();
		}
		moveChicken();
		platformJump();
		updateText();
		displayText(window);
		if (!this->end) {
			play(window);
		}
	}
}

unsigned int JumpingMinigame::get_score() const
{
	return this->score;
}

DestroyBlockMinigame::DestroyBlockMinigame() {
	this->restartGame();
	this->width = 520;
	this->height = 450;
	this->blockNumber = 100;
	this->blockT.loadFromFile("images/block03.png");
	this->backgroundT.loadFromFile("images/background.png");
	this->paddleT.loadFromFile("images/paddle.png");
	this->ballT.loadFromFile("images/ball.png");
	this->gameOverT.loadFromFile("images/destroyGameOver.png");
	this->paddle.setTexture(paddleT);
	this->ball.setTexture(ballT);
	this->background.setTexture(backgroundT);
	this->paddle.setPosition(300, 440);
	this->gameOver.setTexture(gameOverT);
	this->setFonts();
	this->setText();
}

void DestroyBlockMinigame::restartGame() {
	this->dx = 3;
	this->dy = 2.5;
	this->xBall = 300;
	this->yBall = 300;
	this->end = false;
	this->startGame = false;
	this->score = 0;
}

void DestroyBlockMinigame::setUpBlocks() {
	int n = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			this->block[n].setTexture(blockT);
			this->block[n].setPosition(i * 43, j * 20);
			n++;
		}
}

void DestroyBlockMinigame::updateMovement() {
	this->xBall += this->dx;
	for (int i = 0; i < this->blockNumber; i++)
		if (sf::FloatRect(this->xBall + 3, this->yBall + 3, 6, 6).intersects(block[i].getGlobalBounds()))
		{
			this->block[i].setPosition(-100, 0); dx = -dx;
			this->score++;
		}

	this->yBall += this->dy;
	for (int i = 0; i < this->blockNumber; i++)
		if (sf::FloatRect(this->xBall + 3, this->yBall + 3, 6, 6).intersects(block[i].getGlobalBounds()))
		{
			this->block[i].setPosition(-100, 0); dy = -dy;
			this->score++;
		}
}

void DestroyBlockMinigame::updateWallCollision() {
	if (this->xBall < 0 || this->xBall>this->width)  this->dx = -dx;
	if (this->yBall < 0)  this->dy = -dy;
}

void DestroyBlockMinigame::movePaddle() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->paddle.move(6, 0), this->startGame=true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) this->paddle.move(-6, 0), this->startGame = true;

	if (sf::FloatRect(this->xBall, this->yBall, 12, 12).intersects(this->paddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

}
void DestroyBlockMinigame::play(sf::RenderWindow& window) {
	if (this->startGame) {
		updateMovement();
		updateWallCollision();
	}
	movePaddle();

	this->ball.setPosition(this->xBall, this->yBall);

	window.clear();
	this->background.setTexture(this->backgroundT);
	window.draw(this->background);
	this->ball.setTexture(this->ballT);
	window.draw(this->ball);
	this->paddle.setTexture(this->paddleT);
	window.draw(this->paddle);
	for (int i = 0; i < this->blockNumber; i++)
		window.draw(this->block[i]);

	updateText();
	displayText(window);
	window.display();
}


void DestroyBlockMinigame::start(sf::RenderWindow& window)
{
	restartGame();
	srand(time(0));
	window.create(sf::VideoMode(this->width, this->height), "DestoryBlocks", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	srand(time(0));
	setUpBlocks();

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}
		if (this->yBall > this->height) {
			end = true;
			this->gameOver.setTexture(this->gameOverT);
			window.draw(gameOver);
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}
		
		if (!this->end) {
			play(window);
		}
		
		
	}

}

unsigned int DestroyBlockMinigame::get_score() const
{
	return this->score;
}


void DestroyBlockMinigame::setFonts()
{
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void DestroyBlockMinigame::setText()
{
	//this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString("NONE");
}

void DestroyBlockMinigame::updateText()
{
	std::stringstream ss;

	ss << "Score: " << this->get_score() << "\n";

	this->text.setString(ss.str());
}

void DestroyBlockMinigame::displayText(sf::RenderTarget& target)
{
	this->text.setFont(this->font);
	target.draw(this->text);
}