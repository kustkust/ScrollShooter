#include "pch.h"
#include "Game.h"
#include "Clock.h"
#include "Timer.h"
#include "Utility.h"
#include "DrawBaseElement.h"
#include "DataStorage.h"
#include "SinusEnemy.h"
#include "StraigthEnemy.h"
#include "BounceEnemy.h"
#include "EnemyBullet.h"

Game::Game() :
	bounds({ 0, 0 }, { 320, 480 }), curFrameTime{},
	enemys(bounds, 8, [](const std::unique_ptr<Enemy>& en) { return en->hitbox->getBounds(); }),
	bullets(bounds, 8, [](const std::unique_ptr<Bullet>& en) { return en->hitbox->getBounds(); }),
	bonuses(bounds, 8, [](const std::unique_ptr<Bonus>& en) { return en->hitbox->getBounds(); }),
	paint(window) {
	background = SpriteStorage["Background"];
	background.setTextureRect({ {},screenSize.addY(32) });
	TextureStorage["Background"].setRepeated(true);

	// window.setSize(screenSize * 2);
	auto scrRect = sf::VideoMode::getDesktopMode();
	window.setView(sf::View(screenSize, screenSize * 2));
	window.setPosition({
		static_cast<int>(scrRect.width - screenSize.x * 2) / 2,
		static_cast<int>(scrRect.height - screenSize.y * 2) / 2
		});

	gameTexture.create(unsigned int(bounds.getWidth()), unsigned int(bounds.getHeight()));
}

void Game::init() {
	player = Player(shared_from_this(), "Player", {});
	BaseScreenObject::defaultInterfaceClock->start();
}

void Game::startGame() {
	player.hitbox->setCenter(bounds.getSize() / 2);
	player.init();
	spawnTimer.restart(duration(spawnDuratin(gen)));
	state = GameState::Play;
}

void Game::mainLoop() {
	startGame();
	Clock::clock.start();
	Timer timer, workTimer;
	std::uniform_int_distribution spawnPoint(0, static_cast<int>(screenSize.x));
	std::uniform_int_distribution spawnDuratin(100, 200);

	while (window.isOpen()) {
		curFrameTime = timer.sinceLast().count();
		curFrameSec = curFrameTime / 1000.;
		workTimer.restart();
		control();
		update();
		draw();
		sf::sleep(sf::milliseconds(static_cast<sf::Int32>(16 - workTimer.sinceLast().count())));
	}
}

void Game::control() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::MouseMoved) {
			mousePos = gameTexture.mapCoordsToPixel({ float(event.mouseMove.x), float(event.mouseMove.y) });
			// mousePos *= 2;
		}
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		switch (state) {
		case GameState::Play:
			player.control(event);
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					Clock::clock.switchClock();
				}
				break;
			}
			break;
		case GameState::Loose:
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Space:
					enemys.clear();
					bullets.clear();
					startGame();
					break;
				}
				break;
			}
			break;
		}
	}
}

void Game::draw() {
	window.clear();

	drawGame();
	sf::Sprite spr(gameTexture.getTexture());
	spr.scale({ 2,2 });
	window.draw(spr);

	paint.setFillColor(sf::Color::Red).setOutlineColor(sf::Color::Red).setOffset({ 650,10 });
	for (int i = 0; i < player.health; ++i) {
		paint.drawRectangleS({ i * 15, 0 }, { 10,10 });
	}
	gm::real y = 0;
	paint.setFillColor(sf::Color::Blue).drawRectangle({ 0., y += 20, player.shieldHealth * 10, 15. });

	paint.setFillColor(sf::Color::White).setFontSize(15);
	paint.writeText("score:" + std::to_string(player.score), { 0., y += 20 });
	paint.writeText("dmg:" + std::to_string(player.dmg) + " cost:" + std::to_string(player.dmg.getCost()), { 0., y += 20 });
	paint.writeText("shootDur:" + std::to_string(player.shootDuration->count()) + " cost:" + std::to_string(player.shootDuration.getCost()), { 0., y += 20 });

	if (state == GameState::Loose) {
		paint.setOffset({}).writeTextC("LOOSE", screenSize / 2);
	}

	paint.setOffset({});
	paint.drawRectangleC(mousePos, { 10,10 });

	window.display();
}

void Game::drawGame() {
	gameTexture.clear();
	background.setPosition(bgOffset);
	gameTexture.draw(background);
	bgOffset.y += bgSpeed * curFrameTime;
	if (bgOffset.y > 0) {
		bgOffset.y -= 32.0;
	}
	gameTexture.draw(player);
	for (auto& bullet : bullets) {
		gameTexture.draw(*bullet);
	}
	for (auto& enemy : enemys) {
		gameTexture.draw(*enemy);
	}
	for (auto& bonus : bonuses) {
		gameTexture.draw(*bonus);
	}
	gameTexture.display();
}

void Game::update() {
	switch (state) {
	case GameState::Play:
	{
		player.update();
		for (auto& bullet : bullets) {
			bullet->update();
		}
		bullets.updateAll();
		for (auto& enemy : enemys) {
			enemy->update();
		}
		enemys.updateAll();
		for (auto& bonus : bonuses.all()) {
			bonus->update();
		}
		bonuses.updateAll();

		if (player.shieldHealth > 1) {
			for (auto& enemy : enemys.collide(&player.shieldHitbox)) {
				if (!enemy->toDelete && std::abs((enemy->hitbox->getCenter() - player.hitbox->getCenter()) ^ player.shieldDir) < gm::PI / 4) {
					enemy->toDelete = true;
					player.shieldHealth -= 1;
				}
			}
		}

		for (auto& enemy : enemys.collide(player.hitbox.get())) {
			if (!enemy->toDelete && enemy->hitbox->fastCollides(player.hitbox.get())) {
				enemy->toDelete = true;
				player.takeDamage(1);
				if (player.health <= 0) {
					state = GameState::Loose;
				}
			}
		}

		for (auto& bonus : bonuses.collide(player.hitbox.get())) {
			bonus->interact(player);
			bonus->toDelete = true;
		}

		for (auto& enemy : enemys) {
			if (enemy->hitbox->outside(bounds)) {
				enemy->toDelete = true;
			}
			if (enemy->toDelete) continue;
			for (auto& bullet : bullets.collide(enemy->hitbox.get())) {
				if (bullet->hitbox->outside(bounds)) {
					bullet->toDelete = true;
				}
				if (bullet->toDelete) continue;
				if (bullet->collide(enemy.get()) && bullet->hitbox->fastCollides(enemy->hitbox.get())) {
					enemy->takeDamage(bullet->dmg);
					if (enemy->toDelete) {
						player.score += enemy->getScore();
					}
					bullet->toDelete = true;
					break;
				}
			}
		}
		for (auto it = enemys.origBegin(); it != enemys.origEnd();) {
			if (it->item->toDelete) {
				it->item->onDeleting();
				it = enemys.erase(it);
			} else {
				++it;
			}
		}
		for (auto it = bullets.origBegin(); it != bullets.origEnd();) {
			if (it->item->toDelete) {
				it->item->onDeleting();
				it = bullets.erase(it);
			} else {
				++it;
			}
		}
		for (auto it = bonuses.origBegin(); it != bonuses.origEnd();) {
			if (it->item->toDelete) {
				it->item->onDeleting();
				it = bonuses.erase(it);
			} else {
				++it;
			}
		}

		if (!spawnTimer.update()) {
			spawnTimer.restart(duration(spawnDuratin(gen)));
			auto x = spawnPoint(gen);
			switch (enemyType(gen)) {
			case 0:
				addEnemy<StraigthEnemy>(gm::Vector{ x, 32 });
				break;
			case 1:
				addEnemy<SinusEnemy>(gm::Vector{ x, 32 });
				break;
			case 2:
				addEnemy<BounceEnemy>(gm::Vector{ x, 32 });
				break;
			}
			// addEnemy<EnemyBullet>(gm::Vector{ bounds.getCenter().x, 10. }, gm::VY);
		}
		break;
	}
	case GameState::Loose: break;
	}
}
