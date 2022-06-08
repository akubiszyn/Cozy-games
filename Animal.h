#pragma once
#include "Game_square.h"
class Creature
{
public:
	int width;
	int height;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::IntRect currentFrame;
	virtual void display(sf::RenderTarget&) const;
	virtual ~Creature() {};
	virtual void set_Texture(std::string);
	virtual sf::Sprite& get_Sprite();
	virtual sf::Texture& get_Texture();
	
};

class NPC : public Creature {
	sf::Texture talkTexture;
	sf::Vector2u window_size;
public:
	bool startGame;
	NPC(std::string texture, float xPos, float yPos, sf::Vector2u);
	virtual ~NPC() {};
	virtual void talk(int index);
	virtual void set_position(float, float);
	virtual void set_Sprite(std::string);
	virtual bool getStartGame();

};

class Chicken : public Creature
{
private:
	bool stop;
	int moving_up_down;
	int moving_left_right;
	unsigned int distance;
	sf::Clock animationTimer;
	std::string music_path;
	sf::Vector2u window_size;
	//sf::RenderWindow& window;

public:
	Chicken(std::string, int, int, int, int, sf::Vector2u);
	virtual void move();
	virtual void change_animation();
	virtual ~Chicken();
	virtual void stop_now(bool);
	virtual std::string get_music_path() const;
	sf::Vector2f get_position() const;
	virtual void set_position(float, float);
	virtual void set_Sprite(std::string);
};
