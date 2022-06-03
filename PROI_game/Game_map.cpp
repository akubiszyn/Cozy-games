#include "Game_map.h"

sf::Vector2i Game_map::get_player_position() const
{
	return this->player_position;
}

unsigned int Game_map::get_gridheight() const
{
	return this->gridheight;
}

unsigned int Game_map::get_gridlength() const
{
	return this->gridlength;
}

std::vector<std::vector<std::unique_ptr<Game_square>>>& Game_map::get_squares()
{
	return this->squares;
}

std::vector<sf::Vector2i>& Game_map::get_npc_positions()
{
	return this->npc_positions;
}

Game_map::Game_map()
{
	this->gridlength = 8;
	this->gridheight = 8;
	this->set_up_initial_state();
}

void Game_map::set_up_initial_state()
{
	//this->player_position = sf::Vector2i(this->get_gridlength() - 1, this->get_gridheight() - 1);
	this->set_up_npc_positions();
	this->set_up_squares();
}

void Game_map::set_up_npc_positions()
{
	this->get_npc_positions().clear();
	/*
	this->get_npc_positions().push_back(sf::Vector2i(0, 2));
	this->get_npc_positions().push_back(sf::Vector2i(6, 0));
	this->get_npc_positions().push_back(sf::Vector2i(2, 7));
	*/
}

void Game_map::set_up_squares()
{
	this->get_squares().clear();
	std::vector<std::unique_ptr<Game_square>> row;
	sf::Vector2i handpaintedwall_positions[27] = { sf::Vector2i(0, 0), sf::Vector2i(1, 0),  sf::Vector2i(2, 0),  sf::Vector2i(3, 0),  sf::Vector2i(4, 0),
												  sf::Vector2i(5, 0),  sf::Vector2i(7, 0),  sf::Vector2i(0, 1),  sf::Vector2i(3, 2), sf::Vector2i(6, 2),
												  sf::Vector2i(7, 2), sf::Vector2i(0, 3), sf::Vector2i(3, 3), sf::Vector2i(7, 3), sf::Vector2i(0, 4),
												  sf::Vector2i(3, 4), sf::Vector2i(4, 4), sf::Vector2i(4, 5), sf::Vector2i(7, 5), sf::Vector2i(0, 6),
												  sf::Vector2i(1, 6), sf::Vector2i(6, 6), sf::Vector2i(7, 6), sf::Vector2i(0, 7), sf::Vector2i(1, 7),
												  sf::Vector2i(3, 7), sf::Vector2i(4, 7) };
	for (int i = 0; i < this->get_gridheight(); i++)
	{
		for (int j = 0; j < this->get_gridlength(); j++)
		{
			auto search_result = std::find(std::begin(handpaintedwall_positions), std::end(handpaintedwall_positions), sf::Vector2i(j, i));
			if (search_result != std::end(handpaintedwall_positions))
			{
				row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 50 * j, 50 * i, false)));
			}
			else
			{
				row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 50 * j, 50 * i, true)));
			}
		}
		this->get_squares().push_back(std::move(row));
	}
	/*
	for (const sf::Vector2i& vec : handpaintedwall_positions)
	{
		this->get_squares()[vec.y][vec.x]->set_Sprite("images/handpaintedwall2.png");
		this->get_squares()[vec.y][vec.x]->set_is_Accessable(false);
	}
	*/
	/*
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 0, 0, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 50, 0, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 100, 0, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 150, 0, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 200, 0, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 250, 0, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 300, 0, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 350, 0, false)));
	this->get_squares().push_back(std::move(row));
	row.clear();
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 0, 50, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 50, 50, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 100, 50, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 150, 50, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 200, 50, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 250, 50, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 300, 50, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 350, 50, true)));
	this->get_squares().push_back(std::move(row));
	row.clear();
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 0, 100, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 50, 100, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 100, 100, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 150, 100, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 200, 100, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 250, 100, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 300, 100, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 350, 100, false)));
	this->get_squares().push_back(std::move(row));
	row.clear();
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 0, 150, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 50, 150, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 100, 150, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 150, 150, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 200, 150, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 250, 150, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 300, 150, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 350, 150, false)));
	this->get_squares().push_back(std::move(row));
	row.clear();
	row.push_back((std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 0, 200, false))));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 50, 200, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 100, 200, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 150, 200, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 200, 200, false)));
	row.push_back((std::make_unique<Game_square>(Game_square("images/grass.png", 250, 200, true))));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 300, 200, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 350, 200, true)));
	this->get_squares().push_back(std::move(row));
	row.clear();
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 0, 250, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 50, 250, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 100, 250, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 150, 250, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 200, 250, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 250, 250, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 300, 250, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 350, 250, false)));
	this->get_squares().push_back(std::move(row));
	row.clear();
	row.push_back(std::move(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 0, 300, false))));
	row.push_back(std::move(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 50, 300, false))));
	row.push_back(std::move(std::make_unique<Game_square>(Game_square("images/grass.png", 100, 300, true))));
	row.push_back(std::move(std::make_unique<Game_square>(Game_square("images/grass.png", 150, 300, true))));
	row.push_back(std::move(std::make_unique<Game_square>(Game_square("images/grass.png", 200, 300, true))));
	row.push_back(std::move(std::make_unique<Game_square>(Game_square("images/grass.png", 250, 300, true))));
	row.push_back(std::move(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 300, 300, false))));
	row.push_back(std::move(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 350, 300, false))));
	this->get_squares().push_back(std::move(row));
	row.clear();
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 0, 350, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 50, 350, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 100, 350, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 150, 350, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/handpaintedwall2.png", 200, 350, false)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 250, 350, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 300, 350, true)));
	row.push_back(std::make_unique<Game_square>(Game_square("images/grass.png", 350, 350, true)));
	this->get_squares().push_back(std::move(row));
	row.clear();
	*/
	for (const std::vector<std::unique_ptr<Game_square>>& vec : this->get_squares())
	{
		for (const std::unique_ptr<Game_square>& ptr : vec)
		{
			ptr->get_sprite().setTexture(ptr->get_Texture());
		}
	}
}