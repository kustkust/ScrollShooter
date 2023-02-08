#include "pch.h"
#include "HealBonus.h"
#include "Player.h"

HealBonus::HealBonus(std::shared_ptr<Game> game, const gm::Coord& pos) : Bonus(game, "HealthBonus", pos) {}

void HealBonus::interact(Player&player) {
	if (player.health < player.maxHealth) {
		*player.health += 1;
	}
}
