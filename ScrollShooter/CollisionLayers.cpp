#include "pch.h"
#include "CollisionLayers.h"

#define DEF_LAYER(name) Layers name = 1 << static_cast<int>(CollisionLayers::name);

DEF_LAYER(PlayerVsEnemys)
DEF_LAYER(PlayersBulletsVsEnemys)
DEF_LAYER(PlayerVsEnemysBullets)
DEF_LAYER(PlayersShieldVsEnemys)
DEF_LAYER(PlayersShieldVsLaser)
