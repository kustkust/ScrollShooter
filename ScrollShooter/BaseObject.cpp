#include "pch.h"
#include "BaseObject.h"
#include "Game.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "DataStorage.h"
#include "Rectangle.h"
#include "DrawBaseElement.h"

BaseObject::BaseObject(std::shared_ptr<Game> game, const std::string& animName, const gm::Coord& pos) :
	game(game), 
	anim(AnimationStorage.get(animName)), 
	hitbox(std::make_unique<gm::Rectangle>(gm::VN, anim.getSize())) {
	anim.setOrigin();
	anim.restart();
	hitbox->setCenter(pos);
	init();
}

void BaseObject::init() {
	toDelete = false;
}

void BaseObject::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	auto c = hitbox->getCenter();
	anim.setPosition({ std::round(c.x), std::round(c.y) });
	anim.update();
	ren.draw(anim);
	if (game->showHitbox) {
		if (auto s = dynamic_cast<const gm::Rectangle*>(hitbox.get())) {
			drawRectangle(ren, *s, sf::Color::Transparent, {128,0,0,64});
		}
	}
}

void BaseObject::update() {
	auto offset = normalOffset * static_cast<gm::real>(game->curFrameTime);
	hitbox->move(offset);
	anim.update();
}

void BaseObject::takeDamage(int damage) {
	if (!toDelete){
		*health -= damage;
		if (health <= 0) {
			health = 0;
			toDelete = true;
		}
	}
}

bool BaseObject::collide(BaseObject* other) {
	return (collisionLayers & other->collisionLayers).any();
}

void BaseObject::onCollideWithPlayer(const gm::Collision& col) {
	toDelete = true;
}

bool BaseObject::onDeleting() {
	for (auto it = children.begin(); it != children.end();) {
		auto child = *it;
		++it;
		child->onParrentDeleting();
		unadopt(child->inParent);
	}
	if (parent) {
		parent->onChildDeleting(inParent);
	}
	return false;
}

BaseObject::Children::iterator BaseObject::adopt(BaseObject* child) {
	if (child->parent) {
		child->parent->unadopt(child->inParent);
	}
	child->parent = this;
	children.push_back(child);
	child->inParent = --children.end();
	return --children.end();
}

void BaseObject::unadopt(Children::iterator chldPos) {
	if ((*chldPos)->parent == this) {
		(*chldPos)->parent = nullptr;
		children.erase(chldPos);
	}
}

void BaseObject::onChildDeleting(Children::iterator chldPos) {
	unadopt(chldPos);
}

void BaseObject::onParrentDeleting() {}
