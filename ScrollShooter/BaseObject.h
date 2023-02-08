#pragma once
#include "Vector.h"
#include "Rectangle.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Parametr.h"
#include "Animation.h"
class Game;

/*
* Collision Layers
* 0 - player and enemys
* 1 - player's bullets and enemys
* 2 - player and enemy's bullets
*/

class BaseObject : public sf::Drawable {
public:
	std::bitset<8> collisionLayers;

	BaseObject() = default;
	BaseObject(std::shared_ptr<Game> game, const std::string& anim, const gm::Coord& pos);
	BaseObject& operator=(BaseObject&& obj) = default;

	mutable Animations anim;
	std::shared_ptr<Game> game;
	Parametr<int> health{ 1, 0 };
	gm::Rectangle hitbox;
	gm::Vector normalOffset;
	bool toDelete = false;

	virtual void init();
	void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
	virtual void update();
	virtual void takeDamage(int damage);
	bool collide(BaseObject* other);
	virtual bool onDeleting();
	virtual ~BaseObject() = default;
};
