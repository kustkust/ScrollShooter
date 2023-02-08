#include "pch.h"
#include "SinusEnemy.h"
#include "Game.h"
#include "EnemyBullet.h"

SinusEnemy::SinusEnemy(std::shared_ptr<Game> game, const gm::Coord& pos):
	Enemy(game, "Enemy", pos), initialX(pos.x) {
	
}

void SinusEnemy::update() {
	t += 0.005 * game->curFrameTime;
	hitbox->setPosition(sin(t/2) * 50 + initialX, hitbox->getY() + static_cast<gm::real>(game->curFrameTime) * 0.2);
	if (shootTimer.finish()) {
		shootTimer.restart();
		game->addEnemy<EnemyBullet>(hitbox->getCenter() + gm::Vector{0, 8}, gm::Vector{ 0, 1 });
	}
}
