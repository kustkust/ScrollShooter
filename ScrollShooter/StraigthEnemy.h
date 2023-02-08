#pragma once
#include "Enemy.h"
class StraigthEnemy : public Enemy {
public:
	StraigthEnemy(std::shared_ptr<Game> game, const gm::Coord& pos);
};
