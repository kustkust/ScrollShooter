#pragma once
#include "Enemy.h"


class Boss : public Enemy {
private:
	int leftLaser = 0, rightLaser = 1, leftCannon = 2, rightCannon = 3;
	std::array<BaseObject*, 4> comp;
	friend class Laser;
	friend class Cannon;

	Boss(std::shared_ptr<Game> game);

public:
	class Cannon : public Enemy {
		Boss* b;
	public:
		Cannon(std::shared_ptr<Game> game, Boss* boss, const std::string& animName, const gm::Coord& pos);
		void update() override;
		bool onDeleting() override;
	};

	class LaserBeam;
	class Laser : public Enemy {
		Boss* b;
		gm::angle rotateSpeed;
		gm::Vector dir;
		enum { Aim, Shoot } state;
		LaserBeam* laser;
		friend LaserBeam;
	public:
		Laser(std::shared_ptr<Game> game, Boss* boss, const gm::Coord& pos);
		void update() override;
		bool onDeleting() override;
	};

	class LaserBeam : public Enemy {
		BackTimer existTimer;
		Laser* parent = nullptr;
		friend class Laser;
		gm::Coord endPoint;
	public:
		LaserBeam(std::shared_ptr<Game> game, const gm::Coord& pos, const gm::Vector& dir, Duration existTime);
		void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
		void update() override;
		void onCollideWithPlayer(const gm::Collision&) override;
		bool onDeleting() override;
	};

	static void makeBoss(std::shared_ptr<Game> game);
	void update() override;
	bool onDeleting() override;
	void onChiledDeleting(Enemy* child);
	void takeDamage(int dmg) override;
};
