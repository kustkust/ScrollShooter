#pragma once
#include "BaseObject.h"

class Bullet : public BaseObject {
	gm::real speed;
public:
	int dmg;
	bool toDelete = false;
	Bullet(std::shared_ptr<Game> game, sf::Sprite sprite, const gm::Coord2D& pos, gm::real speed, int dmg);
	void update()override;
};

