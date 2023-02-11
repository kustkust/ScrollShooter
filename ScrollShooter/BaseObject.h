#pragma once
#include "Vector.h"
#include "Shape.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Parametr.h"
#include "Animation.h"
#include "CollisionLayers.h"
class Game;

class BaseObject : public sf::Drawable {
public:
	Layers collisionLayers;

	using Children = std::list<BaseObject*>;
	BaseObject* parent = nullptr;
	Children::iterator inParent;
	Children children;

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
	virtual void onCollideWithPlayer(const gm::Collision& col);
	virtual bool onDeleting();

	Children::iterator adopt(BaseObject* child);
	template<class T, class... Args>
	BaseObject::Children::iterator born(Args... args);
	void unadopt(Children::iterator chldPos);
	virtual void onChildDeleting(Children::iterator chldPos);
	virtual void onParrentDeleting();

	virtual ~BaseObject() = default;
};