#pragma once
#include "Vector2D.h"
#include "Rectangle.h"
#include "SFML/Graphics/Sprite.hpp"
class Game;

class BaseObject : public sf::Drawable {
public:
	BaseObject() = default;
	BaseObject(std::shared_ptr<Game> game, sf::Sprite sprite, const gm::Coord2D& pos);

	std::shared_ptr<Game> game;
	mutable sf::Sprite sprite;
	int healf = 1;
	gm::Rectangle hitbox;
	gm::Vector2D normalOffset;
	bool toDelete = false;

	void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
	virtual void update();
	virtual void takeDamage(int damage);
	virtual  ~BaseObject() = default;
};

