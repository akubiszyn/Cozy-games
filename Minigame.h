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
	sf::Event ev;

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
	unsigned int points;
	int health;
	float Enemy_timer;
	float Enemy_timer_max;
	int Max_number_of_enemies;
	bool mouse_is_pressed;

		//Game objects
	std::vector<sf::Sprite> enemies;
	sf::Texture textures[5];
	sf::Sprite enemy;
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

	void pollEvents();
	void updateMousePositions(sf::RenderWindow&);
	void updateText();
	void updateEnemies(sf::RenderWindow&);
	//void update_game();
	virtual void start(sf::RenderWindow&);
	void displayText(sf::RenderTarget& target);
	void displayEnemies(sf::RenderTarget& target);
	void display();
	virtual unsigned int get_score() const;
};