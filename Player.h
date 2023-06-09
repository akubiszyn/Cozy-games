#pragma once
#include "Animal.h"
class Player
{
	sf::Clock animationTimer;
	sf::IntRect currentFrame;
	bool moving = false;
	sf::Texture texture;
	sf::Sprite shape;
	//sf::RenderWindow& window;
	sf::Vector2u window_size;
	void initSprite();
	void initTexture();
	unsigned int scale_divider;
	unsigned int move_divider;
	sf::Vector2i pos;
	sf::Vector2i shape_size;
	float scale_x;
	float scale_y;
	float shape_in_square_divider;
	float movement_x;
	float movement_y;
	int direction;
public:
	Player(sf::Vector2u, sf::Vector2i, sf::Vector2i, unsigned int, unsigned int, float);
	virtual ~Player() {}

	//functions
	sf::Vector2f updateMovement();
	void updateAnimations();
	void render(sf::RenderTarget& target);
	//bool check_collision(Game_map&, float, float);
	//void scale();
	sf::Sprite get_sprite() const;
	sf::Sprite& get_sprite_ref();
	float get_movement_x() const;
	float get_movement_y() const;
	sf::Texture get_Texture() const;
	sf::Vector2u get_window_size() const;
	unsigned int get_scale_divider() const;
	sf::Vector2i get_shape_size() const;
	float get_scale_x() const;
	float get_scale_y() const;
	float get_in_square_divider() const;
	int get_dir();
};