#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Bulet.h"

Player::Player(std::shared_ptr<Game> game, sf::Sprite sprite, const gm::Coord2D& pos) : BaseObject(game, sprite, pos), shootTimer() {
	healf = 5;
}

void Player::control(const sf::Event& e) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		switch (e.key.code) {
		case sf::Keyboard::Up:normalOffset.y = -speed; break;
		case sf::Keyboard::Down:normalOffset.y = speed; break;
		case sf::Keyboard::Left:normalOffset.x = -speed; break;
		case sf::Keyboard::Right:normalOffset.x = speed; break;
		case sf::Keyboard::Z:
			if (!shooting) {
				shooting = true;
				firstShoot = true;
				shootTimer.restart(shootDuration);
			}
			break;
		case sf::Keyboard::Num1:
			if (score >= dmg) {
				score -= dmg;
				dmg += 1;
			}
			break;
		case sf::Keyboard::Num2:
			if (score >= dmg) {
				score -= dmg;
				dmg += 1;
			}
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (e.key.code) {
		case sf::Keyboard::Up:normalOffset.y = 0; break;
		case sf::Keyboard::Down:normalOffset.y = 0; break;
		case sf::Keyboard::Left:normalOffset.x = 0; break;
		case sf::Keyboard::Right:normalOffset.x = 0; break;
		case sf::Keyboard::Z:
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
}

void Player::update() {
	BaseObject::update();
	if (hitbox.getTop() < game->bounds.getTop()) {
		hitbox.move({ .0, game->bounds.getTop() - hitbox.getTop() });
	}
	if (hitbox.getBottom() > game->bounds.getBottom()) {
		hitbox.move({ .0, game->bounds.getBottom() - hitbox.getBottom() });
	}
	if (hitbox.getLeft() < game->bounds.getLeft()) {
		hitbox.move({ game->bounds.getLeft() - hitbox.getLeft(), 0. });
	}
	if (hitbox.getRight() > game->bounds.getRight()) {
		hitbox.move({ game->bounds.getRight() - hitbox.getRight(), 0. });
	}
	if (shooting && (firstShoot || !shootTimer.update())) {
		firstShoot = false;
		shootTimer.restart();
		game->bullets.push_back(std::make_unique<Bullet>(
			game,
			sf::Sprite(game->textures["bullet"]),
			hitbox.getCenter() - 20 * gm::VY,
			0.5,
			dmg
			));
	}
}
