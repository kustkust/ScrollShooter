#include "pch.h"
#include "DMGBonus.h"
#include "Player.h"

DMGBonus::DMGBonus(std::shared_ptr<Game> game, const gm::Coord& pos) : Bonus(game, "DMGBonus", pos) {}

void DMGBonus::interact(Player& player) {
	*player.dmg += 1;
}
