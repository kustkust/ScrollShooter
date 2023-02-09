#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bulet.h"
#include "Rectangle.h"
#include "Painter.h"
#include "QuadTree.h"
#include "Bonus.h"

class Game : public std::enable_shared_from_this<Game> {
public:
	gm::Size screenSize{ 640, 480 };
	sf::RenderWindow window{ sf::VideoMode(static_cast<int>(screenSize.x * 2), static_cast<int>(screenSize.y * 2)), "kust Shooter" };

	std::map<std::string, sf::Texture> textures;
	gm::Rectangle bounds;
	sf::RenderTexture gameTexture;
	int64_t curFrameTime = 0;
	gm::real curFrameSec = 0.;
	Player player;
	QuadTree<std::unique_ptr<Bullet>> bullets;
	QuadTree<std::unique_ptr<Enemy>> enemys;
	QuadTree<std::unique_ptr<Bonus>> bonuses;
	Painter paint;

	std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution<int> spawnPoint{ 16, 624 };
	std::uniform_int_distribution<int> spawnDuratin{ 100, 200 };
	std::uniform_int_distribution<int> enemyType{ 0, 2 };
	std::uniform_int_distribution<int> bonusType{ 0, 10 };
	BackTimer spawnTimer{};

	gm::Coord mousePos;

	sf::Sprite background;
	gm::Vector bgOffset{ 0, -32 };
	gm::real bgSpeed = 0.1;

	bool showHitbox = false;

	enum class GameState {
		Play,
		Loose,
	}state = GameState::Play;

	Game();
	void init();
	void startGame();
	void mainLoop();
	void control();
	void draw();
	void drawGame();
	void update();

	template<class T, class... Args>
	decltype(auto) pushBackEnemy(Args... args) {
		return enemys.pushBack(std::make_unique<T>(shared_from_this(), args...));
	}

	template<class T, class... Args>
	decltype(auto) pushBackBullet(Args... args) {
		return bullets.pushBack(std::make_unique<T>(shared_from_this(), args...));
	}

	template<class T, class... Args>
	decltype(auto) pushBackBonus(Args... args) {
		return bonuses.pushBack(std::make_unique<T>(shared_from_this(), args...));
	}
};
