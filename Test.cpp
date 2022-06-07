#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "C:\Users\Mateusz Kie³bus\Desktop\Studia\PROI\C++\SFML\PROI_game\Game.h"
TEST_CASE("constructor_Game_square1", "[constructors]")
{
	Game_square square;
	REQUIRE(square.get_Sprite_ref().getTextureRect() == sf::IntRect(0, 0, 120, 62));
}
