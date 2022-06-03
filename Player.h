#pragma once
#include "stdafx.h"
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
	void updateMovement(const std::map<unsigned int, std::map<unsigned int, std::unique_ptr<Game_square>>>& map);
	void updateAnimations();
	void render(sf::RenderTarget& target);
	bool check_collision(const std::map<unsigned int, std::map<unsigned int, std::unique_ptr<Game_square>>>&, float, float);
};