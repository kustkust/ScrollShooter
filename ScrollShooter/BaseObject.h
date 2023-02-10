#pragma once
#include "Vector.h"
#include "Shape.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Parametr.h"
#include "Animation.h"
#include "CollisionLayrs.h"
class Game;

class BaseObject : public sf::Drawable {
public:
	Layers collisionLayers;

	BaseObject() = default;
	BaseObject(std::shared_ptr<Game> game, const std::string& anim, const gm::Coord& pos);
	BaseObject& operator=(BaseObject&& obj) = default;

	mutable Animations anim;
	std::shared_ptr<Game> game;
	Parametr<int> health{ 1, 0 };
	std::unique_ptr<gm::IShape> hitbox;
	gm::Vector normalOffset;
	bool toDelete = false;

	template<class T>
	T* as() {
		return dynamic_cast<T*>(this);
	}

	virtual void init();
	void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
	virtual void update();
	virtual void takeDamage(int damage);
	bool collide(BaseObject* other);
	virtual bool onDeleting();
	virtual ~BaseObject() = default;
};
