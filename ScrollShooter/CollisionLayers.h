#pragma once

enum class CollisionLayers {
	PlayerVsEnemys = 0,
	PlayersBulletsVsEnemys,
	PlayerVsEnemysBullets,
	PlayersShieldVsEnemys,
	PlayersShieldVsLaser,
	LayersCount
};

using Layers = std::bitset<static_cast<int>(CollisionLayers::LayersCount)>;

extern Layers PlayerVsEnemys;
extern Layers PlayersBulletsVsEnemys;
extern Layers PlayerVsEnemysBullets;
extern Layers PlayersShieldVsEnemys;
extern Layers PlayersShieldVsLaser;
