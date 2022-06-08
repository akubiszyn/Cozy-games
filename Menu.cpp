#include "Menu.h"


Menu::Menu(sf::RenderWindow& window) {
	if (!font.loadFromFile("fonts/cozy_caps.ttf"))
	{
		// error
	}
	float width = window.getSize().x;
	float height = window.getSize().y;

	initColors();
	initBackground(width, height);
	

	menu[0].setFont(font);
	menu[0].setFillColor(selected_item_color);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f((width - get_text_width(menu[0])) / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(not_selected_item_color);
	menu[1].setString("Exit");
	menu[1].setPosition(sf::Vector2f((width - get_text_width(menu[1])) / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	selectedItemIndex = 0;
}

void Menu::initBackground(float width, float height)
{
	background.setSize(sf::Vector2f(width, height));
	background.setFillColor(sf::Color(64, 54, 54));
}

void Menu::initColors()
{
	selected_item_color = sf::Color::White;
	not_selected_item_color = sf::Color(122, 94, 94);
}

int Menu::get_text_width(sf::Text text)
{
	sf::FloatRect boundingBox = text.getGlobalBounds();
	return boundingBox.width;
}

void Menu::draw(sf::RenderWindow &window)
{
	window.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(not_selected_item_color);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(selected_item_color);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(not_selected_item_color);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(selected_item_color);
	}

}
