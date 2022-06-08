#include "Player.h"
#include "Game_map.h"
#include "Game_square.h"
#include <map>
#include <vector>
#include <string>


class Chickens : Player {
	int count = 0;
	bool found = true;
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::IntRect currentFrame;
	std::map<std::string, sf::Texture*> textures;
	sf::Clock timer;
	float last_x = 0.0f;
	float last_y = 0.0f;
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
};

class Snakegame {
private:
	//sf::RenderWindow* window;
	sf::Event event;
	Player player;
	Game_square snake_square;
	Game_map map = Game_map(false);
	Chickens chicken = Chickens(200, 200);
	std::vector<Chickens*> snake;
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	int result = 0;

public:
	Snakegame() {}
	~Snakegame();
	void start(sf::RenderWindow&);
	void update_game(sf::RenderWindow&);
	void initWindow(sf::RenderWindow&);
	void initPlayer();
	void game_over(sf::RenderWindow&);
	void update_world_collision(Player player, sf::RenderWindow&);
	void set_result();
	int get_result();
	void updatePoints();
	void render_text(sf::RenderWindow&);

	
};

class Snake {

};



