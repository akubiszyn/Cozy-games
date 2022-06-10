#include "Exceptions.h"
/*
TextureNotLoadedException::TextureNotLoadedException() : std::exception()
{
	std::cerr << this->what() << std::endl;
}
*/
const char* TextureNotLoadedException::what() const throw()
{
	return "Texture was not loaded.";
}

const char* InvalidPositionException::what() const throw()
{
	return "x < 0 or y < 0.";
}

const char* ZeroOccuredException::what() const throw()
{
	return "Zero is a restricted variable value";
}
/*
InvalidPositionException::InvalidPositionException() : std::exception()
{
	std::cerr << this->what() << std::endl;
}
*/
