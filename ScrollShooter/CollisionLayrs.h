#pragma once

enum class CollisionLayrs {
	PlayerVsEnemys = 0,
	PlayersBulletsVsEnemys = 1,
	PlayerVsEnemysBullets = 2,
	PlayersShieldVsEnemys = 3,
};

using Layers = std::bitset<8>;

extern Layers PlayerVsEnemys;
extern Layers PlayersBulletsVsEnemys;
extern Layers PlayerVsEnemysBullets;
extern Layers PlayersShieldVsEnemys;