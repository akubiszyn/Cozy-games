#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "C:\Users\Mateusz Kie³bus\Desktop\Studia\PROI\C++\SFML\PROI_game\Game.h"

TEST_CASE("constructor_Game_square1", "[constructors]")
{
	Game_square square;
	const sf::Texture& temp = *square.get_Sprite_ref().getTexture();
	sf::Texture& non_const = const_cast<sf::Texture&>(temp);
	REQUIRE(non_const.getSize() == square.get_Texture_ref().getSize());
	REQUIRE(square.get_is_Accessable() == true);
	REQUIRE(square.get_Texture_ref().isSmooth() == true);
	REQUIRE(square.get_position() == sf::Vector2f(0, 0));
	REQUIRE(square.get_scale_x() == 120.f / square.get_Sprite().getLocalBounds().width);
	REQUIRE(square.get_scale_x() == 62.f / square.get_Sprite().getLocalBounds().height);
}

TEST_CASE("constructor_Game_square2", "[constructors]")
{
	Game_square square("images/grass.png", 10, 10, true, 10, 10);
	const sf::Texture& temp = *square.get_Sprite_ref().getTexture();
	sf::Texture& non_const = const_cast<sf::Texture&>(temp);
	REQUIRE(non_const.getSize() == square.get_Texture_ref().getSize());
	REQUIRE(square.get_is_Accessable() == true);
	REQUIRE(square.get_Texture_ref().isSmooth() == true);
	REQUIRE(square.get_position() == sf::Vector2f(square.get_Sprite().getLocalBounds().width * square.get_scale_x() * 10, square.get_Sprite().getLocalBounds().height * square.get_scale_y() * 10));
	REQUIRE(square.get_scale_x() == 10.f / square.get_Sprite().getLocalBounds().width);
	REQUIRE(square.get_scale_x() == 10.f / square.get_Sprite().getLocalBounds().height);
}

TEST_CASE("constructor_Game_square3_invalid_texture", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("sahavfha", 10, 10, true, 10, 10);
	}
	catch (const TextureNotLoadedException& e)
	{
		REQUIRE(std::string(e.what()) == "Texture was not loaded.");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Game_square3_invalid_width", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("images/drzewo.png", 0, 10, true, -9, 10);
	}
	catch (const ZeroOccuredException& e)
	{
		REQUIRE(e.what() == "Zero is a restricted variable value");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Game_square3_invalid_height", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("images/drzewo.png", 8, 0, true, 10, 10);
	}
	catch (const ZeroOccuredException& e)
	{
		REQUIRE(e.what() == "Zero is a restricted variable value");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Game_square3_invalid_width_height", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("images/drzewo.png", 0, 0, true, 8, 5);
	}
	catch (const ZeroOccuredException& e)
	{
		REQUIRE(e.what() == "Zero is a restricted variable value");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Game_square3_invalid_position", "[constructors]")
{
	bool check = false;
	try
	{
		Game_square("images/drzewo.png", 7, 12, true, -8, 5);
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
		Game_square("images/drzewo.png", 7, 12, true, 8, -5);
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
		Game_square("images/drzewo.png", 7, 12, true, -84, -53);
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
	REQUIRE(map.get_music_path() == "");
	REQUIRE(map.get_animals().size() == 9);
	REQUIRE(map.get_squares_first().empty() == false);
	REQUIRE(map.get_squares_second().empty() == false);
	REQUIRE(map.get_squares_first().size() == 16);
	REQUIRE(map.get_squares_second().size() == 16);
	REQUIRE(map.get_window_size() == sf::Vector2u(sf::VideoMode::getFullscreenModes()[0].width, sf::VideoMode::getFullscreenModes()[0].height));
	REQUIRE(map.get_npc_positions() == std::vector<sf::Vector2i>({ sf::Vector2i(6, 9), sf::Vector2i(12, 3), sf::Vector2i(13, 13) }));
}

TEST_CASE("constructor_Game", "[constructors]")
{
	sf::RenderWindow wind(sf::VideoMode(300, 300), "OK");
	wind.close();
	Game game(wind, 30);
	REQUIRE(game.get_is_end() == false);
	REQUIRE(game.get_is_background_music_playing() == false);
	REQUIRE(game.get_is_music_playing() == false);
	REQUIRE(game.get_minigames_ref().empty() == true);
	REQUIRE(game.get_minigames_ref().size() == 0);
	REQUIRE(game.get_music_ref().getLoop() == false);
	REQUIRE(game.get_window_ref().getSize() == sf::Vector2u(300, 300));
}

TEST_CASE("constructor_Game_invalid_frame_limit", "[constructors]")
{
	bool check = false;
	try
	{
		sf::RenderWindow wind(sf::VideoMode(300, 300), "OK");
		wind.close();
		Game game(wind, 0);
	}
	catch (const ZeroOccuredException& e)
	{
		REQUIRE(e.what() == "Zero is a restricted variable value");
		check = true;
	}
	REQUIRE(check);

}

TEST_CASE("constructor_Chicken", "[constructors]")
{
	Chicken chicken("images/chicken_walk_left.png", sf::VideoMode::getFullscreenModes()[0].width / 16, sf::VideoMode::getFullscreenModes()[0].height / 16, 0.5, 0.5, sf::Vector2i(10, 13), 29, 48, 16, 0, 20);
	REQUIRE(chicken.get_music_path() == "music/chicken.ogg");
	REQUIRE(chicken.get_Sprite().getTextureRect() == sf::IntRect(0, 0, 29, 48));
	REQUIRE(chicken.get_position() == sf::Vector2f(chicken.get_Sprite().getLocalBounds().width * chicken.get_scale_x() * 10, chicken.get_Sprite().getLocalBounds().height * chicken.get_scale_y() * 13));
	REQUIRE(chicken.get_distance() == 0);
	REQUIRE(chicken.get_distance_max() == 20);
	REQUIRE(chicken.get_in_square_scale_x() == 0.5);
	REQUIRE(chicken.get_in_square_scale_y() == 0.5);
	REQUIRE(chicken.get_moving_left_right() == 0);
	REQUIRE(chicken.get_rect_x() == 29);
	REQUIRE(chicken.get_rect_y() == 48);
}

TEST_CASE("constructor_Chicken_invalid_texture", "[constructors]")
{
	bool check = false;
	try
	{

		Chicken chicken("salmfkasniqaa", sf::VideoMode::getFullscreenModes()[0].width / 16, sf::VideoMode::getFullscreenModes()[0].height / 16, 0.5, 0.5, sf::Vector2i(10, 13), 29, 48, 16, 0, 20);
	}
	catch (const TextureNotLoadedException& e)
	{
		REQUIRE(e.what() == "Texture was not loaded.");
		check = true;
	}
	REQUIRE(check);
}

TEST_CASE("constructor_Chicken_invalid_width", "[constructors]")
{
	bool check = false;
	try
	{
		Chicken chicken("images/chicken_walk_left.png", 0, sf::VideoMode::getFullscreenModes()[0].height / 16, 0.5, 0.5, sf::Vector2i(10, 13), 29, 48, 16, 0, 20);
	}
	catch (const ZeroOccuredException& e)
	{
		REQUIRE(e.what() == "Zero is a restricted variable value");
		check = true;
	}
	REQUIRE(check);
}

TEST_CASE("constructor_Chicken_invalid_height", "[constructors]")
{
	bool check = false;
	try
	{
		Chicken chicken("images/chicken_walk_left.png", sf::VideoMode::getFullscreenModes()[0].width / 16, 0, 0.5, 0.5, sf::Vector2i(10, 13), 29, 48, 16, 0, 20);
	}
	catch (const ZeroOccuredException& e)
	{
		REQUIRE(e.what() == "Zero is a restricted variable value");
		check = true;
	}
	REQUIRE(check);
}

TEST_CASE("constructor_Chicken_invalid_in_square_scale_x", "[constructors]")
{
	bool check = false;
	try
	{
		Chicken chicken("images/chicken_walk_left.png", sf::VideoMode::getFullscreenModes()[0].width / 16, sf::VideoMode::getFullscreenModes()[0].height / 16, 0, 0.5, sf::Vector2i(10, 13), 29, 48, 16, 0, 20);
	}
	catch (const ZeroOccuredException& e)
	{
		REQUIRE(e.what() == "Zero is a restricted variable value");
		check = true;
	}
	REQUIRE(check);
}

TEST_CASE("constructor_Chicken_invalid_in_square_scale_y", "[constructors]")
{
	bool check = false;
	try
	{
		Chicken chicken("images/chicken_walk_left.png", sf::VideoMode::getFullscreenModes()[0].width / 16, sf::VideoMode::getFullscreenModes()[0].height / 16, 0.5, 0, sf::Vector2i(10, 13), 29, 48, 16, 0, 20);
	}
	catch (const ZeroOccuredException& e)
	{
		REQUIRE(e.what() == "Zero is a restricted variable value");
		check = true;
	}
	REQUIRE(check);
}

TEST_CASE("constructor_Chicken_invalid_pos", "[constructors]")
{
	bool check = false;
	try
	{
		Chicken chicken("images/chicken_walk_left.png", sf::VideoMode::getFullscreenModes()[0].width / 16, sf::VideoMode::getFullscreenModes()[0].height / 16, 0.5, 0.5, sf::Vector2i(-10, 13), 29, 48, 16, 0, 20);
	}
	catch (const InvalidPositionException& e)
	{
		REQUIRE(e.what() == "x < 0 or y < 0.");
		check = true;
	}
	REQUIRE(check);
}

TEST_CASE("constructor_Chicken_invalid_pos2", "[constructors]")
{
	bool check = false;
	try
	{
		Chicken chicken("images/chicken_walk_left.png", sf::VideoMode::getFullscreenModes()[0].width / 16, sf::VideoMode::getFullscreenModes()[0].height / 16, 0.5, 0.5, sf::Vector2i(10, -13), 29, 48, 16, 0, 20);
	}
	catch (const InvalidPositionException& e)
	{
		REQUIRE(e.what() == "x < 0 or y < 0.");
		check = true;
	}
	REQUIRE(check);
}
