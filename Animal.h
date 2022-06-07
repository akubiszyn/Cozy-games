#pragma once
#include "Game_square.h"
class Animal
{
public:
	int width;
	int height;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::IntRect currentFrame;
	virtual void display(sf::RenderTarget&) const;
	virtual ~Animal() {};
	virtual void set_Sprite(std::string);
	virtual void set_Texture(std::string);
	virtual sf::Sprite& get_Sprite();
	virtual sf::Texture& get_Texture();
	void set_position(float, float);
};

class NPC : public Animal {
	sf::Texture talkTexture;
	bool startGame;
public:
	NPC(std::string texture, float xPos, float yPos);
	virtual ~NPC() {};
	//virtual void talk();

};

class Chicken : public Animal
{
private:
	bool stop;
	int moving_up_down;
	int moving_left_right;
	unsigned int distance;
	sf::Clock animationTimer;
	std::string music_path;

public:
	Chicken(std::string, int, int, int, int);
	virtual void move();
	virtual void change_animation();
	virtual ~Chicken();
	virtual void stop_now(bool);
	virtual std::string get_music_path() const;
	sf::Vector2f get_position() const;
};