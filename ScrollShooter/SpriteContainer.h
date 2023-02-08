#pragma once
#include "SFML/Graphics.hpp"
class SpriteContainer :public std::vector<sf::Sprite> {
public:
	SpriteContainer();
	//SpriteContainer(TiXmlElement*el,const sf::Texture&tex);
	SpriteContainer(
		const std::initializer_list<sf::Sprite>&sprv
	);
	SpriteContainer(const std::vector<sf::Sprite>&sprv);
	void loadFromFile(const std::string&path);
};