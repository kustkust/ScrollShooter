#include "pch.h"
#include "BaseObject.h"
#include "Game.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <string>

BaseObject::BaseObject(std::shared_ptr<Game> game, sf::Sprite sprite, const gm::Coord2D& pos) :
	game(game), sprite(sprite), hitbox({}, { sprite.getGlobalBounds().width,sprite.getGlobalBounds().height }) {
	hitbox.setCenter(pos);
}

void BaseObject::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	sprite.setPosition(hitbox.getCenter() - gm::Size2D(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
	ren.draw(sprite);
}

void BaseObject::update() {
	auto offset = normalOffset * game->curFrameTime;
	hitbox.move(offset);
}

void BaseObject::takeDamage(int damage) {
	if (!toDelete){
		healf -= damage;
		if (healf <= 0) {
			toDelete = true;
		}
	}
	
}
