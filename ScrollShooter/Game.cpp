#include "pch.h"
#include "Game.h"
#include "MyClock.h"
#include "Timer.h"
#include "Utility.h"
#include "DrawBaseElement.h"

Game::Game() : bounds(0, 0, 640, 480), curFrameTime{}, paint(window) {}

void Game::init() {
	textures["player"].loadFromFile("Player.png");
	textures["bullet"].loadFromFile("Bullet.png");
	textures["enemy"].loadFromFile("Enemy.png");
	textures["background"].loadFromFile("Background.png");
	textures["background"].setRepeated(true);
	background.setTexture(textures["background"]);
	background.setTextureRect({ 0,0,640,480 + 32 });
	player = Player(shared_from_this(), sf::Sprite(textures["player"]), { 320, 240 });
	spawnTimer = BackTimer(duration(spawnDuratin(gen)));
	state = GameState::Play;
	window.setSize({ 1280,960 });
	//sf::View view({ 0,0,1280,960 });
	//window.setView(view);
	auto scrRect = sf::VideoMode::getDesktopMode();
	window.setPosition({ (static_cast<int>(scrRect.width) - 1280) / 2, static_cast<int>(scrRect.height - 960) / 2 });
}

void Game::mainLoop() {
	MyClock::clock.start();
	Timer timer, workTimer;
	std::uniform_int_distribution spawnPoint(0, 640);
	std::uniform_int_distribution spawnDuratin(100, 200);

	while (window.isOpen()) {
		curFrameTime = timer.sinceLast().count();
		workTimer.restart();
		control();
		update();
		draw();
		sf::sleep(sf::milliseconds(16 - workTimer.sinceLast().count()));
	}
}

void Game::control() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		switch (state) {
		case GameState::Play: player.control(event); break;
		case GameState::Loose: 
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Space: state = GameState::Play; break;
				}
				break;
			}
			break;
		}
	}
}

void Game::draw() {
	window.clear();
	background.setPosition(bgOffset);
	window.draw(background);
	bgOffset.y += bgSpeed * curFrameTime;
	if (bgOffset.y > 0) {
		bgOffset.y -= 32.0;
	}

	paint.setFillColor({ 137, 43, 56 }).setOutlineColor(sf::Color::Red).setOffset({ 10,10 });
	for (int i = 0; i < player.healf; ++i) {
		paint.drawRectangleS({ i * 15, 0 }, { 10,10 });
	}

	paint.setFillColor(sf::Color::White).writeTextRT("kek", { 0,0 });

	window.draw(player);
	for (auto& enemy : enemys) {
		window.draw(*enemy);
	}
	for (auto& bullet : bullets) {
		window.draw(*bullet);
	}

	if (state == GameState::Loose) {
		paint.setOffset({}).writeTextC("LOOSE", screenSize / 2);
	}

	window.display();
}

void Game::update() {
	switch(state) {
	case GameState::Play:
		player.update();
		for (auto& bullet : bullets) {
			bullet->update();
		}
		for (auto& enemy : enemys) {
			enemy->update();
			if (enemy->hitbox.intersect(player.hitbox)) {
				enemy->toDelete = true;
				player.takeDamage(1);
				if (player.healf <= 0) {
					state = GameState::Loose;
				}
			} else {
				for (auto& bullet : bullets) {
					if (bullet->hitbox.intersect(enemy->hitbox)) {
						enemy->takeDamage(bullet->dmg);
						if (enemy->toDelete) {
							player.score += enemy->getScore();
						}
						bullet->toDelete = true;
						break;
					}
				}
			}
		}

		for (int i = 0; i < enemys.size(); ++i) {
			if (enemys[i]->toDelete) {
				removeByInd(enemys, i);
			}
		}
		for (int i = 0; i < bullets.size(); ++i) {
			if (bullets[i]->toDelete) {
				removeByInd(bullets, i);
			}
		}

		if (!spawnTimer.update()) {
			auto x = spawnPoint(gen);
			enemys.push_back(std::make_unique<Enemy>(shared_from_this(), sf::Sprite(textures["enemy"]), gm::Vector2D{ x, 32 }));
			spawnTimer.restart(duration(spawnDuratin(gen)));
		}
		break;
	case GameState::Loose: break;
	}
}
