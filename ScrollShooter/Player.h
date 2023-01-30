#pragma once
#include "BaseObject.h"
#include "SFML/Window/Event.hpp"
#include "BackTimer.h"

class Player : public BaseObject {
	gm::real speed = 0.3;

	bool shooting = false;
	bool firstShoot = false;
	duration shootDuration = 100ms;
	BackTimer shootTimer;
	int dmg = 1;

	BackTimer invictable;
	duration inictableDuration = 500ms;
	mutable bool show = true;
	mutable BackTimer showTimer;
public:
	int score = 0;
	Player() = default;
	Player(std::shared_ptr<Game> game, sf::Sprite sprite, const gm::Coord2D& pos);
	void control(const sf::Event& e);
	void takeDamage(int dmg)override;
	void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
	void update()override;
};

