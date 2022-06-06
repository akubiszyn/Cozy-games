#pragma once
#include "Exceptions.h"
class Game_square
{
private:
	bool isAccessable;
	sf::Vector2f position;
	sf::Texture square_texture;
	sf::Sprite square_sprite;
public:
	Game_square();
	Game_square(std::string, float, float, bool);
	bool set_Sprite(std::string);
	sf::Sprite& get_Sprite_ref();
	bool get_is_Accessable() const;
	sf::Texture& get_Texture_ref();
	sf::Vector2f get_position() const;
	void set_Texture(std::string);
	void set_position(float, float);
	void set_is_Accessable(bool);
	sf::Sprite get_Sprite() const;
	sf::Texture get_Texture() const;
	//void check_square_texture(std::string);
	//void check_position(float, float);
};