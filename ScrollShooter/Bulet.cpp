#include "pch.h"
#include "Bulet.h"
#include "Game.h"

Bullet::Bullet(std::shared_ptr<Game> game, sf::Sprite sprite, const gm::Coord2D& pos, gm::real speed, int dmg): BaseObject(game, sprite, pos), speed(speed), dmg(dmg) {
	normalOffset.y = -speed;
	hitbox.setSize({ 32,32 });
}

void Bullet::update() {
	BaseObject::update();
	if (!hitbox.intersect(game->bounds)) {
		toDelete = true;
	}
}
