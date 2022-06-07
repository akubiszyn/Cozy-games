#pragma once
#include "stdafx.h"

class TextureNotLoadedException : public std::exception
{
public:
	//TextureNotLoadedException();
	const char* what() const throw();
};

class InvalidPositionException : public std::exception
{
public:
	//InvalidPositionException();
	const char* what() const throw();
};