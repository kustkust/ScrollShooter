#include "pch.h"
#include "Bulet.h"
#include "Game.h"

Bullet::Bullet(std::shared_ptr<Game> game, const gm::Coord& pos, gm::real speed, int dmg): BaseObject(game, "BulletV2", pos), speed(speed), dmg(dmg) {
	normalOffset.y = -speed;
	collisionLayers = PlayersBulletsVsEnemys;
}

void Bullet::update() {
	BaseObject::update();
	if (hitbox->outside(game->bounds)) {
		toDelete = true;
	}
}
