#pragma once
#include "Enemy.h"
#include "BackTimer.h"

class SinusEnemy :  public Enemy {
	gm::real t = 0;
	gm::real initialX;
	BackTimer shootTimer{1000ms};
public:
	SinusEnemy() = default;
	SinusEnemy(std::shared_ptr<Game> game, const gm::Coord& pos);
	void update()override;
};
