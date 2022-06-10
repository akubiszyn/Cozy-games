#pragma once
#include  "Exceptions.h"

class Ianimations
{
protected:
	sf::IntRect currentFrame;
	sf::Texture wholeFrame;
	sf::Sprite wholeSprite;
	sf::Clock animationTimer;
public:
	virtual void change_animation() = 0;
	virtual ~Ianimations() = 0;
};