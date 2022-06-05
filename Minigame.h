#pragma once
#include "Player.h"
class Minigame
{
public:
	virtual void start() = 0;
	virtual unsigned int get_score() = 0;
	//virtual bool get_is_end() = 0;
	virtual ~Minigame() {};
};