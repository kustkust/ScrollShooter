#include "pch.h"
#include "SpriteContainer.h"
#include "DataStorage.h"
#include "Names.h"
SpriteContainer::SpriteContainer() :std::vector<sf::Sprite>() {
}

SpriteContainer::SpriteContainer(
	const std::initializer_list<sf::Sprite>& sprv
) :std::vector<sf::Sprite>(sprv) {
}

SpriteContainer::SpriteContainer(const std::vector<sf::Sprite>& sprv) :
	std::vector<sf::Sprite>(sprv) {
}

void SpriteContainer::loadFromFile(const std::string & path) {
	auto&text = TextureStorage.get("InterfaceTexture.png");
	if (path == Name::Arrow) {
		*this = { {text,{140,56,12,12}},
				{text,{140,56,12,12}},
				{text,{140,56,12,12}},
				{text,{140,56,12,12}}, };
	}
	else if (path == Name::TextInput) {
		*this = { {text,{0,72,16,24}},
				{text,{16,72,8,24}},};
	}
	else if (path == Name::Cursor) {
		*this = { {text,{24,73,2,22}},
				{text,{26,73,2,22}},};
	}
	else if (path == Name::Bar) {
		*this = { {text,{140,68,12,28}},
				{text,{140,68,12,28}},
				{text,{140,68,12,28}},
				{text,{140,68,12,28}}, };
	}
	else if (path == Name::Mark) {
		*this = { {text,{48,72,3,24}},
				{text,{51,72,3,24}}, };
	}
	else if (path == Name::CheckBoxes) {
		*this = { {text,{72,72,24,24}},
				{text,{96,72,24,24}}, };
	}
}