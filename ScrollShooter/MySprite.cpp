#include "pch.h"
#include "MySprite.h"
#include "DataStorage.h"
#include "Utility.h"

MySprite::MySprite() :spr(), BaseScreenObject() {}

MySprite::MySprite(const sf::Texture& tex) :
	spr(tex),
	BaseScreenObject() {}

MySprite::MySprite(const sf::Texture& tex, const sf::IntRect& rect) :
	spr(tex, rect), BaseScreenObject() {}

MySprite::MySprite(const sf::Texture& tex, const gm::Rectangle& rect) :
	spr(tex,
		{
	static_cast<int>(rect.getLeft()),
	static_cast<int>(rect.getTop()),
	static_cast<int>(rect.getWidth()),
	static_cast<int>(rect.getHeight())
		}) {}

MySprite::MySprite(
	const sf::Sprite& spr_
) :
	spr(spr_),
	BaseScreenObject() {}

const int MySprite::interact(
	const sf::Event& ev,
	const gm::Vector& pos
) {
	return 0;
}

void MySprite::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	ren.draw(spr);
}

void MySprite::move(const gm::Vector& off) {
	spr.move(off);
}

void MySprite::setPosition(const gm::Vector& pos_) {
	spr.setPosition(pos_);
}

const gm::Vector MySprite::getPosition() const {
	return spr.getPosition();
}

const gm::Rectangle MySprite::getGlobalBounds() const {
	return spr.getGlobalBounds();
}

const gm::Rectangle MySprite::getLocalBounds() const {
	return spr.getLocalBounds();
}

void MySprite::setSize(const gm::Size& newSize) {
	auto size = getSize();
	spr.setScale({
		static_cast<float>(newSize.x / size.x),
		static_cast<float>(newSize.y / size.y)
		});
}

const gm::Vector MySprite::getSize() const {
	return getGlobalBounds().getSize();
}

const int MySprite::update() {
	return 0;
}

MySprite::operator sf::Sprite() {
	return spr;
}

bool MySprite::loadFromFile(const std::string& path) {
	spr.setTexture(TextureStorage[extractName(path)]);
	return true;
}

void MySprite::rotate(gm::angle ang) {
	spr.rotate(static_cast<float>(ang));
}

void MySprite::setRotation(gm::angle angOff) {
	spr.setRotation(static_cast<float>(angOff * gm::RtoG));
}

const gm::angle MySprite::getRotation() const {
	return spr.getRotation();
}

void MySprite::setScale(const gm::Vector& scale) {
	spr.setScale(scale);
}

const gm::Vector MySprite::getScale() const {
	return spr.getScale();
}

void MySprite::scale(const gm::Vector& scale_) {
	spr.scale(scale_);
}

void MySprite::setOrigin(const gm::Vector& orig) {
	spr.setOrigin(orig);
}

const gm::Vector MySprite::getOrigin() const {
	return spr.getOrigin();
}

void MySprite::setColor(const sf::Color& color) {
	spr.setColor(color);
}
