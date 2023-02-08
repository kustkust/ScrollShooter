#pragma once
#include "Bonus.h"

class SpeedBonus : public Bonus {
public:
	SpeedBonus(std::shared_ptr<Game> game, const gm::Coord& pos);
	void interact(Player& player) override;
};

