#pragma once
#include "Player.h"
#include<iostream>
#include<ctime>
#include<sstream>

class Minigame
{
public:
	virtual void start(sf::RenderWindow&) = 0;
	virtual unsigned int get_score() const = 0;
	//virtual bool get_is_end() = 0;
	virtual ~Minigame() {};
};

class Clicking_minigame : public Minigame
{
private:
		//Variables
		//Window
	//sf::RenderWindow& window;
	//sf::VideoMode videoMode;
	sf::Event event;

		//Mouse positions
	sf::Vector2i mouse_window;
	sf::Vector2f mouse_general;

		//Resources
	sf::Font font;
	std::map<unsigned int, std::string> textures_info;

		//Text
	sf::Text text;

		//Game logic
	bool end;
	unsigned int score;
	int to_lose;
	float food_timer;
	float food_timer_max;
	int Max_number_of_food_objects;
	bool mouse_is_pressed;
	float movement_speed;
	float movement_left_right;

		//Game objects
	std::vector<sf::Sprite> food;
	sf::Texture textures[8];
	sf::Sprite food_object;
	sf::Texture texture;
	sf::Sprite background;
	sf::Texture background_texture;

		//Private functions
	//void iniVariables();
	//void initWindow();
	void setFonts();
	void setText();
	//void setEnemies();

public:
		//Constructors / Destructors
	Clicking_minigame();
	virtual ~Clicking_minigame();

		//Accessors
	//const bool running() const;
	bool get_end() const;

		//Functions
	void Spawn_enemy(sf::RenderWindow&);

	//void pollEvents();
	void updateMousePositions(sf::RenderWindow&);
	void updateText();
	void updateEnemies(sf::RenderWindow&);
	//void update_game();
	virtual void start(sf::RenderWindow&);
	void displayText(sf::RenderTarget& target);
	void displayEnemies(sf::RenderTarget& target);
	//void display();
	virtual unsigned int get_score() const;
};