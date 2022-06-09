#pragma once
#include  "Game_square.h"

class Ianimations
{
protected:
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
public:
	virtual void change_animation() = 0;
};