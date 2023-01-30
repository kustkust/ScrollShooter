#include "pch.h"
#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(std::shared_ptr<Game> game, sf::Sprite sprite, const gm::Coord2D& pos) :
	BaseObject(game, sprite, pos) {
	normalOffset.y = speed;
	hitbox.setSize({ 32,32 });
	healf = 5;
}

void Enemy::update() {
	BaseObject::update();
	if (!hitbox.intersect(game->bounds)) {
		toDelete = true;
	}
}

void Enemy::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	if (damaged.update()) {
		sprite.setColor({ 255,128,128 });
	} else {
		sprite.setColor(sf::Color::White);
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
