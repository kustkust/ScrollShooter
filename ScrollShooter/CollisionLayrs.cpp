#include "pch.h"
#include "CollisionLayrs.h"

#define DEF_LAYER(name) Layers name = 1 << static_cast<int>(CollisionLayrs::name);

DEF_LAYER(PlayerVsEnemys)
DEF_LAYER(PlayersBulletsVsEnemys)
DEF_LAYER(PlayerVsEnemysBullets)
DEF_LAYER(PlayersShieldVsEnemys)