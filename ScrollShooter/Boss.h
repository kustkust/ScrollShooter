#pragma once
#include "Enemy.h"

class BossLaser;
class BossCannon;

class Boss :
    public Enemy {
    BossLaser* leftLaser, *rightLaser;
    BossCannon* leftCannon, *rightCannon;
public:
    Boss(std::shared_ptr<Game> game);
    void update() override;
    bool onDeleting() override;
    void takeDamage(int dmg) override;
};

class BossLaser : public Enemy {
    Boss* boss;
    BackTimer shootTimer;
    BackTimer aimTimer;
    gm::angle rotateSpeed;
    gm::Vector dir;
    enum { Aim, Shoot } state;
public:
    BossLaser(std::shared_ptr<Game> game, Boss* boss, const gm::Coord&pos);
    void update() override;
    bool onDeleting() override;
    void takeDamage(int dmg) override;
};

class BossCannon : public Enemy {
    Boss* boss;
public:
    BossCannon(std::shared_ptr<Game> game, Boss* boss, const gm::Coord& pos);
    void update() override;
    bool onDeleting() override;
    void takeDamage(int dmg) override;
};

class BossLaserBeam : public Enemy {
public:
    BossLaserBeam(std::shared_ptr<Game> game, const gm::Coord& pos, const gm::Vector&dir);
    void update() override;
    bool onDeleting() override;
    void takeDamage(int dmg) override;
};
