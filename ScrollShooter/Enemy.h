#pragma once
#include "BaseObject.h"
#include "BackTimer.h"

class Enemy : public BaseObject {
protected:
	gm::real speed = 0.2;
	BackTimer damaged;
	int score = 1;
public:
	Enemy() = default;
	Enemy(std::shared_ptr<Game> game, const std::string&animName, const gm::Coord& pos);
	void update()override;
	void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
	void takeDamage(int dmg)override;
	int getScore() const;
	bool onDeleting() override;
	virtual void dropBonus() const;
	virtual ~Enemy() = default;
};
