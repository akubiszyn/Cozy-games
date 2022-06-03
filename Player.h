#include "stdafx.h"
using namespace sf;
class Player
{
	Clock animationTimer;
	IntRect currentFrame;
	bool moving = false;
	Texture texture;
	Sprite shape;
	void initSprite();
	void initTexture();
public:
	Player();
	virtual ~Player() {}

	//functions
	void updateMovement();
	void updateAnimations();
	void render(RenderTarget& target);
};

