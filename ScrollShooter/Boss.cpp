#include "pch.h"
#include "Boss.h"
#include "Game.h"
#include "Player.h"
#include "EnemyBullet.h"

Boss::Boss(std::shared_ptr<Game> game) :
	Enemy(game, "BossV2", game->bounds.getSize().mulX(0.5)) {
	hitbox->setSize({ 128, 64 });
	hitbox->setCenter({ game->bounds.getWidth() / 2, 128. });
	health = 100;
	collisionLayers[0] = 0;
	// normalOffset = { 0.125, 0. };
}

void Boss::makeBoss(std::shared_ptr<Game> game) {
	// auto b = dynamic_cast<Boss*>(game->pushBackEnemy<Boss>()->item.get());
	auto b = dynamic_cast<Boss*>(game->enemys.pushBack(std::unique_ptr<Boss>(new Boss(game)))->item.get());

	b->comp[b->leftLaser] = dynamic_cast<Laser*>(game->pushBackEnemy<Laser>(b, gm::NV)->item.get());
	b->comp[b->leftLaser]->hitbox->setCenter(b->hitbox->getLeftTop().add(21, 34));
	b->comp[0] = b->comp[b->leftLaser];
	b->comp[b->rightLaser] = dynamic_cast<Laser*>(game->pushBackEnemy<Laser>(b, gm::NV)->item.get());
	b->comp[b->rightLaser]->hitbox->setCenter(b->hitbox->getLeftTop().add(107, 34));
	b->comp[1] = b->comp[b->rightLaser];

	b->comp[b->leftCannon] = dynamic_cast<Cannon*>(game->pushBackEnemy<Cannon>(b, "BossCannonV2Left", gm::NV)->item.get());
	b->comp[b->leftCannon]->hitbox->setRightTop(b->hitbox->getTopCenter().addY(32));
	b->comp[2] = b->comp[b->leftCannon];
	b->comp[b->rightCannon] = dynamic_cast<Cannon*>(game->pushBackEnemy<Cannon>(b, "BossCannonV2Right", gm::NV)->item.get());
	b->comp[b->rightCannon]->hitbox->setLeftTop(b->hitbox->getTopCenter().addY(32));
	b->comp[3] = b->comp[b->rightCannon];

	for (auto c : b->comp) {
		c->normalOffset = b->normalOffset;
	}
}

void Boss::update() {
	Enemy::update();
	if (hitbox->getLeft() <= game->bounds.getLeft()) {
		normalOffset.x = std::abs(normalOffset.x);
	} else if (hitbox->getRight() >= game->bounds.getRight()) {
		normalOffset.x = -std::abs(normalOffset.x);
	}
	for (auto c : comp) {
		if (c) {
			c->normalOffset = normalOffset;
		}
	}
}

bool Boss::onDeleting() {
	for (auto c : comp) {
		if (c) {
			c->toDelete = true;
		}
	}
	return true;
}

void Boss::takeDamage(int dmg) {
	if (std::ranges::any_of(comp, [](auto p) { return p; })) {
		dmg = 0;
	}
	Enemy::takeDamage(dmg);
}

Boss::Cannon::Cannon(std::shared_ptr<Game> game, Boss* b, const std::string& animName, const gm::Coord& pos) :
	Enemy(game, animName, pos), b(b) {
	anim.setTimes(1);
	health = 10;
}

void Boss::Cannon::update() {
	Enemy::update();
	if (anim.restartIfFinish(1)) {
		game->pushBackEnemy<EnemyBullet>(hitbox->getTopCenter().addY(12), gm::VY);
	}
}

bool Boss::Cannon::onDeleting() {
	if (b->comp[b->leftCannon] == this) {
		b->comp[b->leftCannon] = nullptr;
	} else if (b->comp[b->rightCannon] == this) {
		b->comp[b->rightCannon] = nullptr;
	}
	return true;
}

Boss::Laser::Laser(std::shared_ptr<Game> game, Boss* b, const gm::Coord& pos) :
	Enemy(game, "BossLaser", pos),
	b(b), rotateSpeed(gm::PI/360), dir(gm::VY), state(Aim) {
	anim.setAnim("aim");
	anim.setOrigin({ 16, 10 });
	anim.setAnimTime("aim", 5s);
	anim.setAnimTime("shoot", 2s);
	anim.setTimes(1);
}

void Boss::Laser::update() {
	BaseObject::update();
	switch (state) {
	case Aim:
	{
		auto pp = game->player.hitbox->getCenter();
		auto dtp = (pp - hitbox->getCenter());
		dir <<= std::clamp(dir ^ dtp, -rotateSpeed, rotateSpeed);
		anim.setRotation(gm::VY ^ dir);
		if (anim.restartIfFinish("shoot")) {
			state = Shoot;
			game->pushBackEnemy<Boss::LaserBeam>(hitbox->getCenter() + dir(30), dir, anim.getAnimTime("shoot"));
		}
		break;
	}
	case Shoot:
		if (anim.restartIfFinish("aim")) {
			state = Aim;
		}
		break;
	}
}

bool Boss::Laser::onDeleting() {
	if (b->comp[b->leftLaser] == this) {
		b->comp[b->leftLaser] = nullptr;
	} else if (b->comp[b->rightLaser] == this) {
		b->comp[b->rightLaser] = nullptr;
	}
	if (laser) {
		laser->toDelete = true;
		laser->parent = nullptr;
	}
	return true;
}

Boss::LaserBeam::LaserBeam(std::shared_ptr<Game> game, const gm::Coord& pos, const gm::Vector& dir, Duration existTime) :
	Enemy(game, "BossLaserBeam", pos) , existTimer(existTime) {
	collisionLayers = PlayerVsEnemys | PlayersShieldVsLaser;
	existTimer.restart();
	auto col = game->bounds.collides(gm::Line(pos, pos + dir)).getPoints();
	if ((col[0] - pos) * dir > 0) {
		hitbox = std::make_unique<gm::Sect>(pos, col[0] + dir(10.));
	} else {
		hitbox = std::make_unique<gm::Sect>(pos, col[1] + dir(10.));
	}
	anim.setOrigin({ anim.getWidth() / 2, anim.getHeight() });
	anim.setRotation(gm::VY ^ dir);
	health = -1;
	endPoint = hitbox->as<gm::Sect>()->p1;
}

void Boss::LaserBeam::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	auto s = hitbox->as<gm::Sect>();
	auto p = s->p0, d = (s->p1 - s->p0)(anim.getLocalBounds().getHeight());
	auto h = anim.getBounds();
	while (d * (s->p1 - p) > 0) {
		anim.setPosition(p);
		ren.draw(anim);
		p += d;
	}
}

void Boss::LaserBeam::update() {
	Enemy::update();
	hitbox->as<gm::Sect>()->p1 = endPoint;
	if (existTimer.finish()) {
		toDelete = true;
	}
}

void Boss::LaserBeam::onCollideWithPlayer(const gm::Collision&) {

}

bool Boss::LaserBeam::onDeleting() {
	if (parent) {
		parent->laser = nullptr;
	}
	return true;
}
