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

bool BaseObject::onDeleting() {
	return false;
}
