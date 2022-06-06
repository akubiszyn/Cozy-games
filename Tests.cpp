#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "C:\Users\Mateusz Kiełbus\Desktop\Studia\PROI\C++\SFML\PROI_game\Game.h"

TEST_CASE("constructor_Game_square1", "[constructors]")
{
	Game_square square;
	REQUIRE(square.get_Sprite().getTextureRect() == sf::IntRect(0, 0, 120, 62));
	const sf::Texture& temp = *square.get_Sprite_ref().getTexture();
	sf::Texture& non_const = const_cast<sf::Texture&>(temp);
	REQUIRE(non_const.getSize() == square.get_Texture_ref().getSize());
	REQUIRE(square.get_position() == sf::Vector2f(0, 0));
	REQUIRE(square.get_is_Accessable() == true);
	REQUIRE(square.get_Texture_ref().isSmooth() == true);
}

TEST_CASE("constructor_Game_square2", "[constructors]")
{
	Game_square square("images/grass.png", 10, 10, true);
	REQUIRE(square.get_Sprite().getTextureRect() == sf::IntRect(0, 0, 120, 62));
	const sf::Texture& temp = *square.get_Sprite_ref().getTexture();
	sf::Texture& non_const = const_cast<sf::Texture&>(temp);
	REQUIRE(non_const.getSize() == square.get_Texture_ref().getSize());
	REQUIRE(square.get_position() == sf::Vector2f(10, 10));
	REQUIRE(square.get_is_Accessable() == true);
	REQUIRE(square.get_Texture_ref().isSmooth() == true);
}

TEST_CASE("constructor_Game_square3_invalid_texture", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("sahavfha", 10, 10, true);
	}
	catch (const TextureNotLoadedException& e)
	{
		REQUIRE(std::string(e.what()) == "Game_square texture was not loaded.");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Game_square3_invalid_position", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("images/drzewo.png", -2, 10, true);
	}
	catch (const InvalidPositionException& e)
	{
		REQUIRE(e.what() == "x < 0 or y < 0.");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Game_square3_invalid_position2", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("images/drzewo.png", 8, -12, true);
	}
	catch (const InvalidPositionException& e)
	{
		REQUIRE(e.what() == "x < 0 or y < 0.");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Game_square3_invalid_position3", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("images/drzewo.png", -7, -12, true);
	}
	catch (const InvalidPositionException& e)
	{
		REQUIRE(e.what() == "x < 0 or y < 0.");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Game_map", "[constructors]")
{
	Game_map map;
	REQUIRE(map.get_gridheight() == 16);
	REQUIRE(map.get_gridlength() == 16);
	REQUIRE(map.get_play_music() == false);
	REQUIRE(map.get_minigame_choice() == 0);
	REQUIRE(map.get_music_path() == "");
	REQUIRE(map.get_animals().size() == 3);
	REQUIRE(map.get_squares_first().empty() == false);
	REQUIRE(map.get_squares_second().empty() == false);
	REQUIRE(map.get_squares_first().size() == 16);
	REQUIRE(map.get_squares_second().size() == 16);
}

TEST_CASE("constructor_Game", "[constructors]")
{
	sf::RenderWindow window(sf::VideoMode(1920, 992), "PROI_game");
	Game game(window, 30);
	REQUIRE(game.get_is_end() == false);
}
