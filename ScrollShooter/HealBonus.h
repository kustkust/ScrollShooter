#pragma once
#include "Bonus.h"
class HealBonus : public Bonus {
public:
	HealBonus(std::shared_ptr<Game> game, const gm::Coord& pos);
	void interact(Player& player) override;
};
