#include "pch.h"
#include "BaseScreenObject.h"
#include "Vector.h"
#include "SpriteContainer.h"
#include "Clock.h"

Clock* BaseScreenObject::defaultInterfaceClock = new Clock();

BaseScreenObject::BaseScreenObject() :
	visible(true),
	focus(0),
	active(1),
	willChanged(true) {}

void BaseScreenObject::setPosition(const gm::Vector& pos_) {
	move(pos_ - getPosition());
}

void BaseScreenObject::setPosition(const float& X, const float& Y) {
	setPosition({ X,Y });
}

void BaseScreenObject::mainDraw(sf::RenderTarget& ren) {
	if (visible) {
		ren.draw(*this);
		if (!active) {
			sf::RectangleShape mute(getSize());
			mute.setPosition(getPosition());
			mute.setFillColor({ 0,0,0,127 });
			ren.draw(mute);
		}
	}
}

const int BaseScreenObject::mainInteraction(
	const sf::Event& ev,
	const gm::Vector& pos
) {
	if (active) {
		return interact(ev, pos);
	}
	return NothingHappend;
}

const bool BaseScreenObject::mouseContain(const gm::Vector& pos) const {
	return getGlobalBounds().contains(pos);
}

const bool BaseScreenObject::mouseContain(const sf::Event& ev) const {
	switch (ev.type) {
	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		return mouseButtonContain(ev);
	case sf::Event::MouseMoved:
		return mouseMoveContain(ev);
	}
	return false;
}

const bool BaseScreenObject::mouseMoveContain(sf::Event ev) const {
	return getGlobalBounds().contains(gm::Vector(ev.mouseMove.x, ev.mouseMove.y));
}

const bool BaseScreenObject::mouseButtonContain(sf::Event ev) const {
	return getGlobalBounds().contains(gm::Vector(ev.mouseButton.x, ev.mouseButton.y));
}

const gm::Rectangle BaseScreenObject::getGlobalBounds() const {
	return gm::Rectangle(getPosition(), getSize());
}

void BaseScreenObject::setVisible(const bool vis_) {
	visible = vis_;
}

const bool BaseScreenObject::getVisible() const {
	return visible;
}

void BaseScreenObject::setActive(const bool act_) {
	active = act_;
}

const bool BaseScreenObject::getActive() const {
	return active;
}

void BaseScreenObject::setFocus(const bool act_) {
	if (focus && !act_) {
		focus = false;
		loseFocus();
	} else if (!focus && act_) {
		focus = true;
		receiveFocus();
	}
}

const bool BaseScreenObject::getFocus() const {
	return focus;
}

void BaseScreenObject::receiveFocus() {}

void BaseScreenObject::loseFocus() {}

void BaseScreenObject::setInRectCenter(const gm::Rectangle& rect) {
	auto hs = getSize() / 2;
	auto rc = rect.getCenter();
	setPosition(rc - hs);
}

void BaseScreenObject::setInSizeCenter(const gm::Vector& size_) {
	auto hs = getSize() / 2;
	setPosition((size_ / 2 - hs).correct_coord(1));
}

BaseScreenObject::~BaseScreenObject() {}

const sf::Texture createTextureFromText(const sf::Text& text) {
	gm::Rectangle rect = text.getLocalBounds();
	sf::RenderTexture buf;
	auto tmpSize = rect.getRightBottom();
	buf.create(static_cast<unsigned int>(tmpSize.x), static_cast<unsigned int>(tmpSize.y));
	buf.draw(text);
	buf.display();
	return buf.getTexture();
}

const sf::IntRect floatToInt_Rect(const sf::FloatRect& rect) {
	return {
		static_cast<int>(rect.left),
		static_cast<int>(rect.top),
		static_cast<int>(rect.width),
		static_cast<int>(rect.height),
	};
}

const sf::FloatRect intTofloat_Rect(const sf::IntRect& rect) {
	return {
		static_cast<float>(rect.left),
		static_cast<float>(rect.top),
		static_cast<float>(rect.width),
		static_cast<float>(rect.height),
	};
}

const sf::Vector2i floatToInt_Vector2(const sf::Vector2f& vect_) {
	return {
		static_cast<int>(vect_.x),
		static_cast<int>(vect_.y),
	};
}

const sf::Vector2f intToFloat_Vec2(const sf::Vector2i& vect_) {
	return {
		static_cast<float>(vect_.x),
		static_cast<float>(vect_.y),
	};
}

gm::Vector getSprSize(const sf::Sprite& s) {
	auto temp = s.getGlobalBounds();
	return gm::Vector(temp.width, temp.height);
}

void moveSpriteOnTexture(sf::Sprite& spr, const sf::Vector2i& off) {
	auto& buf = spr.getTextureRect();
	spr.setTextureRect({
		buf.left + off.x,buf.top + off.y,buf.width,buf.height
		});
}

const sf::Texture createTextButton(
	sf::Text text,
	sf::Sprite background
) {
	gm::Rectangle rect = background.getLocalBounds();
	sf::RenderTexture buf;
	auto tmpSize = rect.getRightBottom();
	buf.create(static_cast<unsigned int>(tmpSize.x), static_cast<unsigned int>(tmpSize.y));
	buf.draw(background);
	text.setPosition(
		static_cast<float>(rect.getSize().x - text.getLocalBounds().width / 2),
		static_cast<float>(rect.getSize().y - text.getLocalBounds().height / 2)
	);
	buf.draw(text);
	buf.display();
	return buf.getTexture();
}

const gm::Vector getSpriteSize(const sf::Sprite& spr) {
	auto temp = spr.getGlobalBounds();
	return { temp.width,temp.height };
}

const sf::Sprite getRot90Spr(const sf::Sprite& spr) {
	sf::Sprite temp = spr;
	auto rect = spr.getGlobalBounds();
	temp.setOrigin(rect.width, 0);
	temp.rotate(-90);
	return temp;
}

const SpriteContainer getRot90Spr(const SpriteContainer& sc) {
	SpriteContainer temp = sc;
	for (auto& s : temp) {
		s = getRot90Spr(s);
	}
	return temp;
}