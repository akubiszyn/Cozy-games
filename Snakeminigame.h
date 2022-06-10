
#pragma once
#include "Minigame.h"
#include <string>



class Chickens {
	bool if_colliding = true;
	int count = 0;
	bool found = true;
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::IntRect currentFrame;
	std::map<std::string, sf::Texture*> textures;
public:
	Chickens(float x, float y);
	~Chickens();
	void render(sf::RenderTarget&);
	void reset(Player, std::vector<Chickens*>&);
	void set_Sprite(float, float);
	void set_Texture();
	void update_Movement(Player, std::vector<Chickens*>& );
	sf::Sprite get_shape();
	bool check_if_colliding(Player, std::vector<Chickens*>&);
	bool check_collision(Player, Chickens*);
	void get_chicken_restart();
	void set_if_colliding(bool);
};

class Snakegame : public Minigame {
private:
	//sf::RenderWindow* window;

	bool end;
	bool startGame;
	sf::Event event;
	Player player = Player(sf::Vector2u(1366, 768), sf::Vector2i(14, 8), sf::Vector2i(72, 50), 16, 6, 0.8);
	Game_square snake_square;
	Chickens chicken = Chickens(400, 400);
	std::vector<Chickens*> snake;
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	int result = 0;

public:
	Snakegame();
	~Snakegame();
	virtual void start(sf::RenderWindow&);
	void restartGame();
	void update_game(sf::RenderWindow&);
	void initWindow(sf::RenderWindow&);
	void game_over(sf::RenderWindow&);
	void update_world_collision(Player player, sf::RenderWindow&);
	void set_result();
	virtual unsigned int get_score() const;
	void updatePoints();
	void render_text(sf::RenderWindow&);
	bool get_end() const;


};



