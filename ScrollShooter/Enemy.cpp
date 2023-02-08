#include "pch.h"
#include "Enemy.h"
#include "Game.h"
#include "HealBonus.h"
#include "DMGBonus.h"
#include "SpeedBonus.h"

Enemy::Enemy(std::shared_ptr<Game> game, const std::string& animName, const gm::Coord& pos) :
	BaseObject(game, animName, pos) {
	normalOffset.y = speed;
	hitbox->setSize({ 32,32 });
	health.reset(5);
	collisionLayers[0] = 1;
	collisionLayers[1] = 1;
}

void Enemy::update() {
	BaseObject::update();
	if (hitbox->outside(game->bounds)) {
		toDelete = true;
	}
}

void Enemy::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	if (damaged.update()) {
		anim.setColor({ 255,128,128 });
	} else {
		anim.setColor(sf::Color::White);
	}
	BaseObject::draw(ren, states);
}

void Enemy::takeDamage(int dmg) {
	BaseObject::takeDamage(dmg);
	damaged.restart(100ms);
}

int Enemy::getScore() const {
	return score;
}

bool Enemy::onDeleting() {
	dropBonus();
	return false;
}

void Enemy::dropBonus() const {
	if (health == 0) {
		switch (game->bonusType(game->gen)) {
		case 0: game->addBonus<HealBonus>(hitbox->getPosition()); break;
		case 1: game->addBonus<DMGBonus>(hitbox->getPosition()); break;
		case 2: game->addBonus<SpeedBonus>(hitbox->getPosition()); break;
		}
	}
}
