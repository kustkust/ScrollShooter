#pragma once
#include "BaseObject.h"

class Bullet : public BaseObject {
	gm::real speed;
public:
	int dmg;
	bool toDelete = false;
	Bullet(std::shared_ptr<Game> game, const gm::Coord& pos, gm::real speed, int dmg);
	void update()override;
};
