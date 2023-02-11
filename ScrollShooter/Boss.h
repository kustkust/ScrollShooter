#pragma once
#include "Enemy.h"


class Boss : public Enemy {
private:
	Children::iterator leftLaser, rightLaser, leftCannon, rightCannon;
	friend class Laser;
	friend class Cannon;

	Boss(std::shared_ptr<Game> game);

public:
	class Cannon : public Enemy {
	public:
		Cannon(std::shared_ptr<Game> game, const std::string& animName, const gm::Coord& pos);
		void update() override;
	};

	class LaserBeam;
	class Laser : public Enemy {
		gm::angle rotateSpeed;
		gm::Vector dir;
		enum { Aim, Shoot } state;
		friend LaserBeam;
	public:
		Laser(std::shared_ptr<Game> game, const gm::Coord& pos);
		void update() override;
	};

	class LaserBeam : public Enemy {
		BackTimer existTimer;
		friend class Laser;
		gm::Coord endPoint;
	public:
		LaserBeam(std::shared_ptr<Game> game, const gm::Coord& pos, const gm::Vector& dir, Duration existTime);
		void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
		void update() override;
		void onCollideWithPlayer(const gm::Collision&) override;
		void onParrentDeleting() override;
	};

	static void makeBoss(std::shared_ptr<Game> game);
	void update() override;
	bool onDeleting() override;
	void onChildDeleting(Children::iterator child) override;
	void takeDamage(int dmg) override;
};
