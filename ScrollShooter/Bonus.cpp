#include "pch.h"
#include "Bonus.h"

Bonus::Bonus(std::shared_ptr<Game> game, const std::string& animName, const gm::Vector& pos) : BaseObject(game, animName, pos) {
	axel = 0.01;
	normalOffset.y = -0.2;
}

void Bonus::update() {
	BaseObject::update();
	normalOffset.y += axel;
	normalOffset.y = std::clamp(normalOffset.y, -1., 0.5);
}
