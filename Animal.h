#pragma once
#include "Game_square.h"
class Creature
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	float in_square_scale_x;
	float in_square_scale_y;
	float scale_x;
	float scale_y;
	unsigned int rect_x;
	unsigned int rect_y;
public:
	//int width;
	//int height;
	//sf::Vector2u window_size;
	//sf::IntRect currentFrame;
	virtual void display(sf::RenderTarget&) const;
	virtual ~Creature() {};
	virtual void set_Texture(std::string);
	virtual sf::Sprite& get_Sprite_ref();
	virtual sf::Texture& get_Texture_ref();
	virtual sf::Texture get_Texture() const;
	virtual sf::Sprite get_Sprite() const;
	virtual sf::Vector2f get_position() const;
	virtual void set_position(float, float);
	virtual void set_Sprite(std::string, unsigned int, unsigned int);
	Creature();
	Creature(std::string, unsigned int, unsigned int, float, float, sf::Vector2i, unsigned int, unsigned int);
	Creature(const Creature&);
	Creature(Creature&&) noexcept(true);
	Creature& operator=(const Creature&);
	Creature& operator=(Creature&&) noexcept(true);
	float get_in_square_scale_x() const;
	float get_in_square_scale_y() const;
	float get_scale_x() const;
	float get_scale_y() const;
	unsigned int get_rect_x() const;
	unsigned int get_rect_y() const;
};

class Ianimal
{
protected:
	std::string music_path;
public:
	virtual void move() = 0;
	virtual void stop_now(bool) = 0;
	virtual ~Ianimal() = 0;
	virtual std::string get_music_path() const = 0;
	virtual void display(sf::RenderTarget&) const = 0;
	virtual sf::Sprite get_Sprite() const = 0;
};

class NPC : public Creature {
	sf::Texture talkTexture;
	//sf::Vector2u window_size;
public:
	bool startGame;
	NPC(std::string, unsigned int, unsigned int, float, float, sf::Vector2i, unsigned int, unsigned int);
	NPC();
	NPC(const NPC&);
	NPC(NPC&&) noexcept(true);
	NPC& operator=(const NPC&);
	NPC& operator=(NPC&&) noexcept(true);
	virtual ~NPC() {};
	virtual void talk(int index);
	//virtual void set_position(float, float);
	//virtual void set_Sprite(std::string);
	virtual bool getStartGame();

};

class Chicken : public Creature, public Ianimal, public Ianimations
{
private:
	bool stop;
	int moving_up_down;
	int moving_left_right;
	unsigned int distance;
	unsigned int distance_max;
	//sf::Clock animationTimer;
	//sf::Vector2u window_size;
	//sf::IntRect currentFrame;
	//sf::RenderWindow& window;

public:
	Chicken(std::string, unsigned int, unsigned int, float, float, sf::Vector2i, unsigned int, unsigned int, int, int, unsigned int);
	Chicken();
	Chicken(const Chicken&);
	Chicken(Chicken&&) noexcept(true);
	Chicken& operator=(const Chicken&);
	Chicken& operator=(Chicken&&) noexcept(true);
	virtual void move();
	virtual void change_animation();
	virtual ~Chicken() {};
	virtual void stop_now(bool);
	virtual std::string get_music_path() const;
	virtual void display(sf::RenderTarget&) const override;
	virtual sf::Sprite get_Sprite() const override;
	bool get_stop() const;
	int get_moving_up_down() const;
	int get_moving_left_right() const;
	unsigned int get_distance() const;
	unsigned int get_distance_max() const;
	sf::IntRect get_currentFrame() const;
	sf::Texture get_WholeFrame() const;
	sf::Sprite get_WholeSprite() const;
	sf::Clock get_animationTimer() const;
};
