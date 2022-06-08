#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3
class Menu
{
public:
	Menu(sf::RenderWindow& window);
	void initColors();
	void initBackground(float width, float height);

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItemIndex; };
	int get_text_width(sf::Text text);

private:
	int selectedItemIndex;
	sf::Font font;
	sf::RectangleShape background;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Color selected_item_color;
	sf::Color not_selected_item_color;
};

