#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bulet.h"
#include "Rectangle.h"
#include "Painter.h"

class Game : public std::enable_shared_from_this<Game> {
public:
	std::map<std::string, sf::Texture> textures;
	gm::Rectangle bounds;
	int64_t curFrameTime = 0;
	Player player;
	std::vector<std::unique_ptr<Bullet>> bullets;
	std::vector< std::unique_ptr<Enemy>> enemys;
	gm::Size2D screenSize{640, 480};
	sf::RenderWindow window{ sf::VideoMode(640, 480), "kust Shooter" };
	Painter paint;

	std::mt19937 gen{ std::random_device{}()};
	std::uniform_int_distribution<int> spawnPoint{0, 640};
	std::uniform_int_distribution<int> spawnDuratin{ 100, 200 };
	BackTimer spawnTimer{};

	sf::Sprite background;
	gm::Vector2D bgOffset{ 0, -32 };
	gm::real bgSpeed = 0.1;

	enum class GameState {
		Play,
		Loose,
	};
	GameState state;

	Game();
	void init();
	void mainLoop();
	void control();
	void draw();
	void update();
};

