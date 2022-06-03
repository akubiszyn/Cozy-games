#pragma once
#include <SFML/Graphics.hpp>

class Game_square
{
private:
	bool isAccessable;
	sf::Vector2f position;
	sf::Texture square_texture;
	sf::Sprite square_sprite;
public:
	Game_square(std::string, float, float, bool);
	bool set_Sprite(std::string);
	sf::Sprite& get_sprite();
	bool get_is_Accessable() const;
	sf::Texture& get_Texture();
	sf::Vector2f get_position() const;
	void set_Texture(std::string);
	void set_position(float, float);
	void set_is_Accessable(bool);
};