#pragma once
#include "Game_map.h"
class Player
{
	sf::Clock animationTimer;
	sf::IntRect currentFrame;
	bool moving = false;
	sf::Texture texture;
	sf::Sprite shape;
	void initSprite();
	void initTexture();
public:
	Player();
	virtual ~Player() {}

	//functions
	void updateMovement(Game_map&);
	void updateAnimations();
	void render(sf::RenderTarget& target);
	bool check_collision(Game_map&, float, float);
};