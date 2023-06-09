#pragma once
#include "Game_map.h"
#include<ctime>
#include<sstream>

class Minigame
{
public:
	virtual void start(sf::RenderWindow&) = 0;
	virtual unsigned int get_score() const = 0;
	virtual ~Minigame() = 0;
};

class Clicking_minigame : public Minigame
{
private:
	sf::Event event;
	sf::Vector2i mouse_window;
	sf::Vector2f mouse_general;
	sf::Font font;
	std::map<unsigned int, std::string> textures_info;
	sf::Text text;
	sf::Text end_game;
	bool end;
	unsigned int score;
	int to_lose;
	float food_timer;
	float food_timer_max;
	int Max_number_of_food_objects;
	bool mouse_is_pressed;
	float movement_speed;
	float movement_left_right;
	std::vector<sf::Sprite> food;
	sf::Texture textures[8];
	sf::Sprite food_object;
	sf::Texture texture;
	sf::Sprite background;
	sf::Texture background_texture;
	sf::Sprite end_screen;
	sf::Texture edn_screen_texture;
	void setFonts();
	void setText();
public:
	Clicking_minigame();
	virtual ~Clicking_minigame();
	void restartGame();
	bool get_end() const;
	void Spawn_food_object(sf::RenderWindow&);
	void updateMousePositions(sf::RenderWindow&);
	void updateText();
	void updateFood(sf::RenderWindow&);
	virtual void start(sf::RenderWindow&);
	void displayText(sf::RenderTarget& target);
	void displayFood(sf::RenderTarget& target);
	void display_end_game(sf::RenderTarget& target);
	virtual unsigned int get_score() const;
	void scale(sf::RenderWindow&, sf::Sprite&, int, int);
	void make_end_game(sf::RenderWindow&);
};

class Point { public: int x, y; };
class JumpingMinigame : public Minigame {
	sf::Event event;
	int width;
	int height;

	//Resources
	sf::Font font;

	//Text
	sf::Text text;

	//Game logic
	bool startGame;
	bool end;
	unsigned int score;
	int xPos;
	int yPos;
	int screenBorder;
	int platformNumber;
	float dXPos, dYPos, fallingSpeed;
	int chickenWidth, chickenHeight;
	int platformWidth, platformHeight;

	//Game objects
	Point platforms[10];
	sf::Texture backgroundT, platformT, chickenT, gameOverT;
	sf::Sprite background, platform, chicken, gameOver;

	//private funs


public:
	void restartGame();
	void setFonts();
	void setText();
	//Constructors / Destructors
	JumpingMinigame();
	virtual ~JumpingMinigame();

	//Accessors
	int getWidth();
	int getHeight();
	int getXPos();
	int getYPos();
	void updateText();
	void start(sf::RenderWindow&);
	void displayText(sf::RenderTarget& target);
	// Game logic
	void adjustPlatforms(float scale, int width, int height);
	void adjustChicken(float scale, int width, int height);
	void moveChicken();
	void generatePlatformsPositions();
	void updatePlatformsPositions();
	void platformJump();
	void play(sf::RenderWindow& window);
	virtual unsigned int get_score() const;
};

class DestroyBlockMinigame : public Minigame {
	sf::Event event;
	int width;
	int height;

	//Resources
	sf::Font font;

	//Text
	sf::Text text;

	//Game logic
	bool startGame;
	bool end;
	unsigned int score;
	float dx, dy;
	float xBall, yBall;
	int blockNumber;

	//Game objects
	sf::Texture paddleT, blockT, ballT, backgroundT, gameOverT;
	sf::Sprite paddle, block[1000], ball, background, gameOver;

	//private funs


public:
	void restartGame();
	void setFonts();
	void setText();
	//Constructors / Destructors
	DestroyBlockMinigame();
	~DestroyBlockMinigame() {};
	//Accessors
	//int getWidth();
	//int getHeight();
	void updateText();
	void start(sf::RenderWindow&);
	void setUpBlocks();
	void updateMovement();
	void updateWallCollision();
	void movePaddle();
	void displayText(sf::RenderTarget& target);
	// Game logic
	void play(sf::RenderWindow& window);
	virtual unsigned int get_score() const;
};

