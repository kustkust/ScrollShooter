#include "pch.h"
#include "BaseObject.h"
#include "Game.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <string>
#include "DataStorage.h"

BaseObject::BaseObject(std::shared_ptr<Game> game, const std::string& animName, const gm::Coord& pos) :
	game(game), anim(AnimationStorage.get(animName)), hitbox({}, anim.getSize()) {
	hitbox.setCenter(pos);
	init();
}

void BaseObject::init() {
	toDelete = false;
}

void BaseObject::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	anim.setCenter(hitbox.getCenter().correct_coord(1));
	anim.update();
	ren.draw(anim);
}

void BaseObject::update() {
	auto offset = normalOffset * static_cast<gm::real>(game->curFrameTime);
	hitbox.move(offset);
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
