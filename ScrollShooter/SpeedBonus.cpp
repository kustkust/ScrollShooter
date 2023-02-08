#include "pch.h"
#include "SpeedBonus.h"
#include "Player.h"

SpeedBonus::SpeedBonus(std::shared_ptr<Game> game, const gm::Coord& pos) : Bonus(game, "SpeedBonus", pos) {}

void SpeedBonus::interact(Player& player) {
	if (*player.shootDuration > 10ms) {
		*player.shootDuration -= 10ms;
	}
}
