#pragma once
#include "BaseObject.h"
#include "BackTimer.h"

class Enemy : public BaseObject {
	gm::real speed = 0.2;
	BackTimer damaged;
	int score = 1;
public:
	Enemy() = default;
	Enemy(std::shared_ptr<Game> game, sf::Sprite sprite, const gm::Coord2D& pos);
	void update()override;
	void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
	void takeDamage(int dmg)override;
	int getScore()const;
};

