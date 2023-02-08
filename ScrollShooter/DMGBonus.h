#pragma once
#include "Bonus.h"

class DMGBonus : public Bonus {
public:
	DMGBonus(std::shared_ptr<Game> game, const gm::Coord& pos);
	void interact(Player& player) override;
};


