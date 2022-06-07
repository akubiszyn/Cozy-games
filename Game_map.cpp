#include "Game_map.h"

/*
sf::Vector2i Game_map::get_player_position() const
{
	return this->player_position;
}
*/
unsigned int Game_map::get_gridheight() const
{
	return this->gridheight;
}

unsigned int Game_map::get_gridlength() const
{
	return this->gridlength;
}

std::map<unsigned int, std::map<unsigned int, Game_square>>& Game_map::get_squares_first()
{
	return this->squares_first;
}

std::map<unsigned int, std::map<unsigned int, Game_square>>& Game_map::get_squares_second()
{
	return this->squares_second;
}

std::vector<sf::Vector2i>& Game_map::get_npc_positions()
{
	return this->npc_positions;
}

Game_map::Game_map(sf::RenderWindow& window) : window(window)
{
	this->set_window_size(this->window);
	this->gridlength = 16;
	this->gridheight = 16;
	this->set_up_initial_state();
	this->set_music_path("");
	this->set_play_music(false);
}

void Game_map::set_up_npc_positions()
{
	this->get_npc_positions().clear();
	this->get_npc_positions().push_back(sf::Vector2i(0, 0));
	this->get_npc_positions().push_back(sf::Vector2i(500, 500));
	this->get_npc_positions().push_back(sf::Vector2i(200, 300));
}

void Game_map::set_up_initial_state()
{
	//this->player_position = sf::Vector2i(this->get_gridlength() - 1, this->get_gridheight() - 1);
	this->set_up_npc_positions();
	this->set_up_squares();
	this->animals.push_back(std::move(std::make_unique<Chicken>(Chicken("images/chicken_walk_left.png", 0, -2, 7, 13, this->window))));
	this->animals.push_back(std::move(std::make_unique<Chicken>(Chicken("images/chicken_walk_left.png", -2, 0, 9, 14, this->window))));
	this->animals.push_back(std::move(std::make_unique<Chicken>(Chicken("images/chicken_walk_left.png", 2, 0, 8, 13, this->window))));
	this->get_animals()[0]->get_Sprite().setTexture(this->get_animals()[0]->get_Texture());
	this->get_animals()[1]->get_Sprite().setTexture(this->get_animals()[0]->get_Texture());
	this->get_animals()[2]->get_Sprite().setTexture(this->get_animals()[0]->get_Texture());
	this->npcs.push_back(std::make_unique<NPC>(NPC("images/walk_leftm.png", get_npc_positions()[0].x, get_npc_positions()[0].y)));
	this->npcs.push_back(std::make_unique<NPC>(NPC("images/walk_leftm.png", get_npc_positions()[1].x, get_npc_positions()[1].y)));
	this->npcs.push_back(std::make_unique<NPC>(NPC("images/walk_leftm.png", get_npc_positions()[2].x, get_npc_positions()[2].y)));
	this->get_npcs()[0]->get_Sprite().setTexture(this->get_npcs()[0]->get_Texture());
	this->get_npcs()[1]->get_Sprite().setTexture(this->get_npcs()[1]->get_Texture());
	this->get_npcs()[2]->get_Sprite().setTexture(this->get_npcs()[2]->get_Texture());

}


void Game_map::set_up_squares()
{
	auto cmpLambda = [](const sf::Vector2i& l, const sf::Vector2i& r)
	{
		if (l.x != r.x)
			return (l.x < r.x);
		else
			return (l.y < r.y);
	};
	std::map<sf::Vector2i, std::string, decltype(cmpLambda)> Vector_comp_map(cmpLambda);
	Vector_comp_map = {};
	std::vector<sf::Vector2i> positions;
	for (const std::pair<sf::Vector2i, std::string>& drawable : Vector_comp_map)
	{
		positions.push_back(drawable.first);
	}

	std::map<sf::Vector2i, std::string, decltype(cmpLambda)> Vector_comp_map2(cmpLambda);
	Vector_comp_map2 = { {sf::Vector2i(8, 11), "images/house1_left_up.png" }, {sf::Vector2i(9, 11), "images/house1_right_up.png" },
					   {sf::Vector2i(8, 12), "images/house1_left_down.png" }, {sf::Vector2i(9, 12), "images/house1_right_down.png" },
					   {sf::Vector2i(0, 0), "images/drzewo.png" }, { sf::Vector2i(1, 0), "images/drzewo.png" },
					   { sf::Vector2i(2, 0), "images/drzewo.png" }, { sf::Vector2i(3, 0), "images/drzewo.png" },
					   { sf::Vector2i(4, 0), "images/drzewo.png" }, { sf::Vector2i(5, 0), "images/drzewo.png" },
					   { sf::Vector2i(7, 0), "images/drzewo.png" }, { sf::Vector2i(0, 1), "images/drzewo.png" },
					   { sf::Vector2i(3, 2), "images/drzewo.png" }, { sf::Vector2i(6, 2), "images/drzewo.png" },
					   { sf::Vector2i(7, 2), "images/drzewo.png" }, { sf::Vector2i(0, 3), "images/drzewo.png" },
					   { sf::Vector2i(3, 3), "images/drzewo.png" }, { sf::Vector2i(7, 3), "images/drzewo.png" },
					   { sf::Vector2i(3, 4), "images/drzewo.png" },
					   { sf::Vector2i(4, 4), "images/drzewo.png" }, { sf::Vector2i(4, 5), "images/drzewo.png" },
					   { sf::Vector2i(7, 5), "images/drzewo.png" }, { sf::Vector2i(0, 6), "images/drzewo.png" },
					   { sf::Vector2i(1, 6), "images/drzewo.png" }, { sf::Vector2i(6, 6), "images/drzewo.png" },
					   { sf::Vector2i(7, 6), "images/drzewo.png" }, { sf::Vector2i(0, 7), "images/drzewo.png" },
					   { sf::Vector2i(1, 7), "images/drzewo.png" }, { sf::Vector2i(3, 7), "images/drzewo.png" },
					   { sf::Vector2i(4, 7), "images/drzewo.png" }, { sf::Vector2i(8, 0), "images/drzewo.png" },
					   { sf::Vector2i(9, 0), "images/drzewo.png" }, { sf::Vector2i(10, 0), "images/drzewo.png" },
					   { sf::Vector2i(11, 0), "images/drzewo.png" }, { sf::Vector2i(12, 0), "images/drzewo.png" },
					   { sf::Vector2i(13, 0), "images/drzewo.png" }, { sf::Vector2i(14, 0), "images/drzewo.png" },
					   { sf::Vector2i(15, 0), "images/drzewo.png" }, { sf::Vector2i(0, 2), "images/drzewo.png" },
					   { sf::Vector2i(0, 3), "images/drzewo.png" },
					   { sf::Vector2i(0, 5), "images/drzewo.png" }, { sf::Vector2i(0, 6), "images/drzewo.png" },
					   { sf::Vector2i(0, 8), "images/drzewo.png" }, { sf::Vector2i(0, 9), "images/drzewo.png" },
					   { sf::Vector2i(0, 11), "images/drzewo.png" }, { sf::Vector2i(0, 12), "images/drzewo.png" },
					   { sf::Vector2i(0, 13), "images/drzewo.png" }, { sf::Vector2i(0, 14), "images/drzewo.png" },
					   { sf::Vector2i(0, 15), "images/drzewo.png" }, { sf::Vector2i(1, 15), "images/drzewo.png" },
					   { sf::Vector2i(2, 15), "images/drzewo.png" }, { sf::Vector2i(1, 14), "images/drzewo.png" },
					   { sf::Vector2i(3, 15), "images/drzewo.png" }, { sf::Vector2i(4, 15), "images/drzewo.png" },
					   { sf::Vector2i(5, 15), "images/drzewo.png" }, { sf::Vector2i(6, 15), "images/drzewo.png" },
					   { sf::Vector2i(7, 15), "images/drzewo.png" }, { sf::Vector2i(9, 15), "images/drzewo.png" },
					   { sf::Vector2i(10, 15), "images/drzewo.png" }, { sf::Vector2i(12, 15), "images/drzewo.png" },
					   { sf::Vector2i(14, 14), "images/drzewo.png" }, { sf::Vector2i(15, 14), "images/drzewo.png" },
					   { sf::Vector2i(15, 13), "images/drzewo.png" }, { sf::Vector2i(15, 12), "images/drzewo.png" },
					   { sf::Vector2i(15, 11), "images/drzewo.png" }, { sf::Vector2i(15, 10), "images/drzewo.png" },
					   { sf::Vector2i(15, 9), "images/drzewo.png" }, { sf::Vector2i(14, 9), "images/drzewo.png" },
					   { sf::Vector2i(15, 7), "images/drzewo.png" }, { sf::Vector2i(14, 7), "images/drzewo.png" },
					   { sf::Vector2i(15, 6), "images/drzewo.png" }, { sf::Vector2i(15, 5), "images/drzewo.png" },
					   { sf::Vector2i(15, 4), "images/drzewo.png" }, { sf::Vector2i(15, 3), "images/drzewo.png" },
					   { sf::Vector2i(15, 2), "images/drzewo.png" }, { sf::Vector2i(15, 1), "images/drzewo.png" },
					   { sf::Vector2i(10, 8), "images/drzewo.png" }, { sf::Vector2i(10, 9), "images/drzewo.png" },
					   { sf::Vector2i(10, 10), "images/drzewo.png" }, { sf::Vector2i(11, 10), "images/drzewo.png" },
					   { sf::Vector2i(11, 11), "images/drzewo.png" }, {sf::Vector2i(12, 4), "images/niebieski_kwiatek.png" },
					   {sf::Vector2i(13, 5), "images/niebieski_kwiatek.png" }, {sf::Vector2i(10, 6), "images/niebieski_kwiatek.png" },
					   {sf::Vector2i(8, 8), "images/glaz.png" }, {sf::Vector2i(10, 4), "images/glaz.png" },
					   {sf::Vector2i(2, 10), "images/glaz.png" }, {sf::Vector2i(3, 5), "images/glaz.png" },
					   {sf::Vector2i(5, 11), "images/house2_left_up.png" }, {sf::Vector2i(6, 11), "images/house2_right_up.png" },
					   {sf::Vector2i(5, 12), "images/house2_left_down.png" }, {sf::Vector2i(6, 12), "images/house2_right_down.png" },
					   {sf::Vector2i(10, 4), "images/glaz.png" }, {sf::Vector2i(6, 3), "images/glaz.png" },
					   {sf::Vector2i(10, 11), "images/opakowanie_pomidor.png" }, {sf::Vector2i(10, 12), "images/opakowanie_ziemniak.png" },
					   {sf::Vector2i(0, 4), "images/drzewo.png" }, {sf::Vector2i(0, 10), "images/drzewo.png" },
					   {sf::Vector2i(6, 0), "images/drzewo.png" }, {sf::Vector2i(15, 8), "images/drzewo.png" },
					   {sf::Vector2i(15, 15), "images/drzewo.png" }, {sf::Vector2i(14, 15), "images/drzewo.png" },
					   {sf::Vector2i(11, 15), "images/drzewo.png" }, {sf::Vector2i(10, 15), "images/drzewo.png" },
					   {sf::Vector2i(8, 15), "images/drzewo.png" }, {sf::Vector2i(13, 15), "images/drzewo.png" } };

	std::vector<sf::Vector2i> positions2;
	for (const std::pair<sf::Vector2i, std::string>& drawable : Vector_comp_map2)
	{
		positions2.push_back(drawable.first);
	}
	unsigned int width = this->get_window_size().x / 16;
	unsigned int height = this->get_window_size().y / 16;

	for (int i = 0; i < this->get_gridheight(); i++)
	{
		for (int j = 0; j < this->get_gridlength(); j++)
		{
			auto search_result = std::find(std::begin(positions), std::end(positions), sf::Vector2i(j, i));
			auto search_result2 = std::find(std::begin(positions2), std::end(positions2), sf::Vector2i(j, i));
			if (search_result != std::end(positions))
			{
				this->squares_first[i][j] = std::move(Game_square(Vector_comp_map.at(sf::Vector2i(j, i)), width, height, false, j, i));
			}
			else
			{
				this->squares_first[i][j] = std::move(Game_square("images/trawa.png", width, height, true, j, i));
			}
			if (search_result2 != std::end(positions2))
			{

				this->squares_first[i][j] = std::move(Game_square("images/trawa.png", width, height, true, j, i));
				this->squares_second[i][j] = std::move(Game_square(Vector_comp_map2.at(sf::Vector2i(j, i)), width, height, false, j, i));
			}
		}
	}

	for (std::pair<const unsigned int, std::map<unsigned int, Game_square>>& row : this->get_squares_first())
	{
		for (std::pair<const unsigned int, Game_square>& column : row.second)
		{
			//const Game_square& temp = column.second;
			//Game_square& non_const = const_cast<Game_square&>(temp);
			//non_const.get_Sprite_ref().setTexture(non_const.get_Texture_ref());
			column.second.get_Sprite_ref().setTexture(column.second.get_Texture_ref());
		}
	}
	for (std::pair<const unsigned int, std::map<unsigned int, Game_square>>& row : this->get_squares_second())
	{
		for (std::pair<const unsigned int, Game_square>& column : row.second)
		{
			//const Game_square& temp = column.second;
			//Game_square& non_const = const_cast<Game_square&>(temp);
			//non_const.get_Sprite_ref().setTexture(non_const.get_Texture_ref());
			column.second.get_Sprite_ref().setTexture(column.second.get_Texture_ref());
		}
	}

}

void Game_map::update_game_map(sf::RenderTarget& window)
{
	for (const std::pair<const unsigned int, std::map<unsigned int, Game_square>>& row : this->get_squares_first())
	{
		for (const std::pair<const unsigned int, Game_square>& column : row.second)
		{
			window.draw(column.second.get_Sprite());
		}
	}
	for (const std::pair<const unsigned int, std::map<unsigned int, Game_square>>& row : this->get_squares_second())
	{
		for (const std::pair<const unsigned int, Game_square>& column : row.second)
		{
			window.draw(column.second.get_Sprite());
		}
	}
	for (const std::unique_ptr<NPC>& npc : this->get_npcs())
	{
		npc->display(window);
	}
	for (const std::unique_ptr<Chicken>& animal_ptr : this->get_animals())
	{
		animal_ptr->display(window);
		animal_ptr->move();
	}

}

std::vector<std::unique_ptr<Chicken>>& Game_map::get_animals()
{
	return this->animals;
}

std::vector<std::unique_ptr<NPC>>& Game_map::get_npcs()
{
	return this->npcs;
}

void Game_map::set_music_path(std::string text)
{
	this->music_path = text;
}

std::string Game_map::get_music_path() const
{
	return this->music_path;
}

void Game_map::set_play_music(bool value)
{
	this->play_music = value;
}

bool Game_map::get_play_music() const
{
	return this->play_music;
}

void Game_map::set_window_size(sf::RenderWindow& window)
{
	this->window_size = window.getSize();
}

sf::Vector2u Game_map::get_window_size() const
{
	return this->window_size;
}

