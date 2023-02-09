#include "pch.h"
#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(std::shared_ptr<Game> game, const gm::Coord& pos, const gm::Vector& dir) :
	Enemy(game, "EnemyBullet", pos) {
	normalOffset = dir.normal() * 0.2;
	health = -1; // negative means immortal
	collisionLayers.reset();
	collisionLayers[2] = 1;
	auto center = hitbox->getCenter();
	hitbox->setSize({ 4,4 });
	hitbox->setCenter(pos);
}

void EnemyBullet::dropBonus() const {}
