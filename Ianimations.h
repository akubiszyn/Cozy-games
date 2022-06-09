#pragma once
#include  "Exceptions.h"

class Ianimations
{
public:
	virtual void change_animation() = 0;
	virtual ~Ianimations() = 0;
};