#include "pch.h"
#include "BounceEnemy.h"
#include "Game.h"

BounceEnemy::BounceEnemy(std::shared_ptr<Game> game, const gm::Vector& pos) : 
	Enemy(game, "Enemy2", pos) {
	normalOffset = { 0.2, 0.2 };
}

void BounceEnemy::update() {
	Enemy::update();
	if (hitbox->getLeft() <= game->bounds.getLeft()) {
		normalOffset.x = std::abs(normalOffset.x);
	} else if (hitbox->getRight() >= game->bounds.getRight()) {
		normalOffset.x = -std::abs(normalOffset.x);
	}
}
