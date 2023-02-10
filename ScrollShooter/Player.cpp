#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Bulet.h"
#include "DataStorage.h"
#include "DrawBaseElement.h"

Player::Player(std::shared_ptr<Game> game, const std::string& animName, const gm::Coord& pos) :
	BaseObject(game, animName, pos), shootTimer(),
	shootSound(SoundStorage["shoot"]), shieldAnimation(AnimationStorage["Shield"]) {
	collisionLayers[0] = 1;
	collisionLayers[2] = 1;
}

void Player::init() {
	BaseObject::init();
	health.reset(maxHealth);
	shootDuration.reset();
	speed.reset();
	shooting = false;
	firstShoot = false;
	dmg.reset();
	inictableDuration = 500ms;
	show = true;
	score = 0;
	normalOffset = gm::NV;
	anim.restart();
	shieldAnimation.setOrigin({ shieldAnimation.getWidth() / 2, shieldAnimation.getHeight() });
	shieldHitbox.setSize({ 50., 50. });
	shieldAnimation.restart();
	shieldHealth = 5;
}

void Player::control(const sf::Event& e) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		switch (e.key.code) {
		case sf::Keyboard::W:normalOffset.y = -speed; break;
		case sf::Keyboard::S:normalOffset.y = speed; break;
		case sf::Keyboard::A:normalOffset.x = -speed; break;
		case sf::Keyboard::D:normalOffset.x = speed; break;
		case sf::Keyboard::Space:
			if (!shooting) {
				shooting = true;
				firstShoot = true;
				shootTimer.restart(shootDuration);
			}
			break;
		case sf::Keyboard::Num1:
			dmg.tryUpgrade(score);
			break;
		case sf::Keyboard::Num2:
			shootDuration.tryUpgrade(score);
			break;
		case sf::Keyboard::Num3:
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (e.key.code) {
		case sf::Keyboard::W:normalOffset.y = 0; break;
		case sf::Keyboard::S:normalOffset.y = 0; break;
		case sf::Keyboard::A:normalOffset.x = 0; break;
		case sf::Keyboard::D:normalOffset.x = 0; break;
		case sf::Keyboard::Space:
			shooting = false;
			break;
		}
		break;
	}
}

void Player::takeDamage(int dmg) {
	if (!invictable.update()) {
		BaseObject::takeDamage(dmg);
		invictable.restart(inictableDuration);
		showTimer.restart(100ms);
	}
}

void Player::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	if (invictable.update()) {
		if (show == true) {
			BaseObject::draw(ren, states);
		}
		if (!showTimer.update()) {
			showTimer.restart();
			show = !show;
		}
	} else {
		BaseObject::draw(ren, states);
	}
	ren.draw(shieldAnimation);
	if (game->showHitbox) {
		drawCircle(ren, shieldHitbox, sf::Color::Transparent, { 0, 255, 0, 64 });
	}
}

void Player::update() {
	BaseObject::update();

	shieldDir = game->mousePos / 2 - hitbox->getCenter();
	shieldAnimation.setColor({ 255,255,255,sf::Uint8(255 * shieldHealth / 5.) });
	shieldAnimation.setRotation(-gm::VY ^ shieldDir);
	shieldAnimation.setPosition(hitbox->getCenter());
	shieldAnimation.update();
	shieldHitbox.setCenter(hitbox->getCenter());
	if (shieldHealth < 5) {
		shieldHealth += shieldRegenSpeed * game->curFrameSec;
		if (shieldHealth > 5) {
			shieldHealth = 5;
		}
	}

	if (hitbox->getTop() < game->bounds.getTop()) {
		hitbox->move({ .0, game->bounds.getTop() - hitbox->getTop() });
	}
	if (hitbox->getBottom() > game->bounds.getBottom()) {
		hitbox->move({ .0, game->bounds.getBottom() - hitbox->getBottom() });
	}
	if (hitbox->getLeft() < game->bounds.getLeft()) {
		hitbox->move({ game->bounds.getLeft() - hitbox->getLeft(), 0. });
	}
	if (hitbox->getRight() > game->bounds.getRight()) {
		hitbox->move({ game->bounds.getRight() - hitbox->getRight(), 0. });
	}
	if (shooting && (firstShoot || !shootTimer.update())) {
		firstShoot = false;
		shootTimer.restart(shootDuration);
		// shootSound.play();
		game->pushBackBullet<Bullet>(hitbox->getCenter().addY(-20), 0.5, *dmg);
	}
}
