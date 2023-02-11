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
	collisionLayers &= ~PlayersBulletsVsEnemys;
}

void Boss::makeBoss(std::shared_ptr<Game> game) {
	// auto b = dynamic_cast<Boss*>(game->pushBackEnemy<Boss>()->item.get());
	auto b = dynamic_cast<Boss*>(game->enemys.pushBack(std::unique_ptr<Boss>(new Boss(game)))->get());
	/*
	b->comp[b->leftLaser] = dynamic_cast<Laser*>(game->pushBackEnemy<Laser>(b, gm::NV)->get());
	b->comp[b->leftLaser]->hitbox->setCenter(b->hitbox->getLeftTop().add(21, 34));
	b->comp[0] = b->comp[b->leftLaser];
	b->comp[b->rightLaser] = dynamic_cast<Laser*>(game->pushBackEnemy<Laser>(b, gm::NV)->get());
	b->comp[b->rightLaser]->hitbox->setCenter(b->hitbox->getLeftTop().add(107, 34));
	b->comp[1] = b->comp[b->rightLaser];

	b->comp[b->leftCannon] = dynamic_cast<Cannon*>(game->pushBackEnemy<Cannon>(b, "BossCannonV2Left", gm::NV)->get());
	b->comp[b->leftCannon]->hitbox->setRightTop(b->hitbox->getTopCenter().addY(32));
	b->comp[2] = b->comp[b->leftCannon];
	b->comp[b->rightCannon] = dynamic_cast<Cannon*>(game->pushBackEnemy<Cannon>(b, "BossCannonV2Right", gm::NV)->get());
	b->comp[b->rightCannon]->hitbox->setLeftTop(b->hitbox->getTopCenter().addY(32));
	b->comp[3] = b->comp[b->rightCannon];
	*/

	b->leftLaser = b->born<Laser>(gm::NV);
	(*b->leftLaser)->hitbox->setCenter(b->hitbox->getLeftTop().add(21, 34));
	b->rightLaser = b->born<Laser>(gm::NV);
	(*b->rightLaser)->hitbox->setCenter(b->hitbox->getLeftTop().add(107, 34));

	b->leftCannon = b->born<Cannon>("BossCannonV2Left", gm::NV);
	(*b->leftCannon)->hitbox->setRightTop(b->hitbox->getTopCenter().addY(32));
	b->rightCannon = b->born<Cannon>("BossCannonV2Right", gm::NV);
	(*b->rightCannon)->hitbox->setLeftTop(b->hitbox->getTopCenter().addY(32));

	for (auto c : b->children) {
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
	for (auto c : children) {
		if (c) {
			c->normalOffset = normalOffset;
		}
	}
}

bool Boss::onDeleting() {
	for (auto c : children) {
		if (c) {
			c->toDelete = true;
		}
	}
	return true;
}

void Boss::onChildDeleting(Children::iterator child) {
	BaseObject::onChildDeleting(child);
	if (!std::ranges::any_of(children, [](auto ch) { return ch; })) {
		collisionLayers |= PlayersBulletsVsEnemys;
	}
}

void Boss::takeDamage(int dmg) {
	if (std::ranges::any_of(children, [](auto p) { return p; })) {
		dmg = 0;
	}
	Enemy::takeDamage(dmg);
}

Boss::Cannon::Cannon(std::shared_ptr<Game> game, const std::string& animName, const gm::Coord& pos) :
	Enemy(game, animName, pos) {
	anim.setTimes(1);
	health = 10;
}

void Boss::Cannon::update() {
	Enemy::update();
	if (anim.restartIfFinish(1)) {
		// game->pushBackEnemy<EnemyBullet>(hitbox->getTopCenter().addY(12), gm::VY);
	}
}

Boss::Laser::Laser(std::shared_ptr<Game> game, const gm::Coord& pos) :
	Enemy(game, "BossLaser", pos),
	rotateSpeed(gm::PI/360), dir(gm::VY), state(Aim) {
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
			born<LaserBeam>(hitbox->getCenter() + dir(30),
				dir,
				anim.getAnimTime("shoot"));
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

void Boss::LaserBeam::onCollideWithPlayer(const gm::Collision& coll) {
	auto col = coll.getPoints();
	if (col.empty()) return;
	auto l = hitbox->as<gm::Sect>();
	gm::Coord p = col.front();
	for (auto& cp : col) {
		if (cp / l->p0 < p / l->p0) {
			p = cp;
		}
	}
	if (std::abs((p - game->player.hitbox->getCenter()) ^ game->player.shieldDir) < gm::PI / 4) {
		l->p1 = p;
		game->player.shieldHealth -= 1 * game->curFrameSec;
	}
}

void Boss::LaserBeam::onParrentDeleting() {
	toDelete = true;
}
