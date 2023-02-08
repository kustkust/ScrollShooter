#pragma once
#include "BaseObject.h"
class Player;
class Bonus : public BaseObject {
	gm::real axel;
public:
	Bonus(std::shared_ptr<Game> game, const std::string& animName, const gm::Vector& pos);
	void update() override;
	virtual void interact(Player&) = 0;
};
