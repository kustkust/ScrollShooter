#include "pch.h"
#include "Boss.h"
#include "Game.h"
#include "Player.h"

BossLaser::BossLaser(std::shared_ptr<Game> game, Boss* boss, const gm::Coord& pos) :
	Enemy(game, "BossLaser", pos),
	boss(boss), shootTimer(2s), aimTimer(5s), rotateSpeed(gm::PI / 180), dir(gm::VY), state(Aim) {}

void BossLaser::update() {
	switch (state) {
	case BossLaser::Aim:
	{
		auto pp = game->player.hitbox->getCenter();
		auto dtp = (pp - hitbox->getCenter());
		auto a = std::clamp(gm::smallestAng(dtp, dir), 0., rotateSpeed);
		
		break;
	}
	case BossLaser::Shoot:
		break;
	}
}
