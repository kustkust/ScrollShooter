#pragma once
#include "Enemy.h"
class BounceEnemy : public Enemy {
public:
	BounceEnemy(std::shared_ptr<Game> game, const gm::Vector& pos);
	void update();
};
