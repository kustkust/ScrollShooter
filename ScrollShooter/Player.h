#pragma once
#include "BaseObject.h"
#include "SFML/Window/Event.hpp"
#include "BackTimer.h"
#include "Parametr.h"
#include "Animation.h"
#include "SFML/Audio/Sound.hpp"
#include "Circle.h"

class Player : public BaseObject {
public:
	Parametr<gm::real> speed{ 0.3, 1,[](gm::real& p) { static_cast<void>(p + 0.1); }, [](int& cost) { cost *= 2; } };

	bool shooting = false;
	bool firstShoot = false;
	Parametr <Duration> shootDuration{ 100ms, 1, 
		[](Duration& p) {if (p > 10ms) p -= 10ms; }, 
		[](int& cost) { cost *= 2; } 
	};
	BackTimer shootTimer;
	Parametr<int> dmg{ 1, 1,[](int& dmg) { ++dmg; }, [](int& cost) { cost *= 2; } };
	int maxHealth = 10;
	sf::Sound shootSound;

	BackTimer invictable;
	Duration inictableDuration = 500ms;
	mutable bool show = true;
	mutable BackTimer showTimer;

	Animations shieldAnimation;
	gm::Vector shieldDir;
	gm::Circle shieldHitbox;
	gm::real shieldHealth = 5;
	gm::real shieldRegenSpeed = 0.5;

	int score = 0;
	Player() = default;
	Player(std::shared_ptr<Game> game, const std::string& animName, const gm::Coord& pos);
	void init() override;
	void control(const sf::Event& e);
	void takeDamage(int dmg)override;
	void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
	void update()override;
};
