#include "Exceptions.h"
/*
TextureNotLoadedException::TextureNotLoadedException() : std::exception()
{
	std::cerr << this->what() << std::endl;
}
*/
const char* TextureNotLoadedException::what() const throw()
{
	return "Game_square texture was not loaded.";
}

const char* InvalidPositionException::what() const throw()
{
	return "x < 0 or y < 0.";
}
/*
InvalidPositionException::InvalidPositionException() : std::exception()
{
	std::cerr << this->what() << std::endl;
}
*/