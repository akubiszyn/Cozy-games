#pragma once
#include "Ianimations.h"
class Game_square : Ianimations
{
private:
	bool isAccessable;
	sf::Vector2f position;
	sf::Texture square_texture;
	sf::Sprite square_sprite;
	float scale_x;
	float scale_y;

public:
	Game_square();
	virtual ~Game_square() {};
	Game_square(std::string, unsigned int, unsigned int, bool, int, int);
	Game_square(const Game_square&);
	Game_square(Game_square&&) noexcept(true);
	Game_square& operator=(const Game_square&);
	Game_square& operator=(Game_square&&) noexcept(true);
	bool set_Sprite(std::string, unsigned int, unsigned int);
	sf::Sprite& get_Sprite_ref();
	bool get_is_Accessable() const;
	sf::Texture& get_Texture_ref();
	sf::Vector2f get_position() const;
	void set_Texture(std::string);
	void set_position(float, float);
	void set_is_Accessable(bool);
	sf::Sprite get_Sprite() const;
	sf::Texture get_Texture() const;
	float get_scale_x() const;
	float get_scale_y() const;
	virtual void change_animation();

	//void check_square_texture(std::string);
	//void check_position(float, float);
};