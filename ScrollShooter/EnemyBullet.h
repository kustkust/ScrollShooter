#pragma once
#include "Enemy.h"
class EnemyBullet : public Enemy {
public:
	EnemyBullet(std::shared_ptr<Game> game, const gm::Coord& pos, const gm::Vector& dir);
	void dropBonus() const override;
};
