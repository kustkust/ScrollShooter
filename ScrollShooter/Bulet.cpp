#include "pch.h"
#include "Bulet.h"
#include "Game.h"

Bullet::Bullet(std::shared_ptr<Game> game, const gm::Coord& pos, gm::real speed, int dmg): BaseObject(game, "Bullet", pos), speed(speed), dmg(dmg) {
	normalOffset.y = -speed;
	hitbox->setSize({ 32,32 });
	collisionLayers = PlayersBulletsVsEnemys;
}

void Bullet::update() {
	BaseObject::update();
	if (hitbox->outside(game->bounds)) {
		toDelete = true;
	}
}
