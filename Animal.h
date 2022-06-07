#pragma once
#include "Game_square.h"
class Animal
{
public:
	virtual void move() = 0;
	virtual void change_animation() = 0;
	virtual void display(sf::RenderTarget&) const = 0;
	virtual ~Animal() {};
	virtual sf::Sprite& get_Sprite() = 0;
	virtual sf::Texture& get_Texture() = 0;
	virtual void stop_now(bool) = 0;
	virtual std::string get_music_path() const = 0;
};

class Chicken : public Animal
{
private:
	bool stop;
	int moving_up_down;
	int moving_left_right;
	unsigned int distance;
	sf::Clock animationTimer;
	sf::IntRect currentFrame;
	sf::Texture texture;
	sf::Sprite sprite;
	std::string music_path;
	sf::Vector2f position;
	sf::RenderWindow& window;
public:
	Chicken(std::string, int, int, int, int, sf::RenderWindow&);
	void set_Sprite(std::string);
	void set_Texture(std::string);
	virtual void display(sf::RenderTarget&) const;
	virtual void move();
	virtual void change_animation();
	virtual ~Chicken();
	virtual sf::Sprite& get_Sprite();
	virtual sf::Texture& get_Texture();
	virtual void stop_now(bool);
	virtual std::string get_music_path() const;
	void set_position(float, float);
	sf::Vector2f get_position() const;
};