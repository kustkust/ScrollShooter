#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Rectangle.h"
#include "Clock.h"
#include "ISizeable.h"

using ButtonFoo = std::function<int(void*)>;
#define FHEAD_CAP (void*data)mutable->int
#define FHEAD [&]FHEAD_CAP

class BaseScreenObject : public gm::ISizeable, public sf::Drawable {
public:
	static Clock* defaultInterfaceClock;
protected:
	//������ �� ������ ������ ������
	bool visible;
	//������� �� ������ ������ ������
	bool active;
	//� ������ �� ������
	bool focus;
	//��� �� ������� ������
	bool willChanged;
public:

	enum BaseInteractionCode {
		NothingHappend = 0,
		SomethingHappend = 1 << 15,
	};

	BaseScreenObject();

	virtual const int interact(
		const sf::Event& ev,
		const gm::Vector& pos = gm::NV) = 0;
	virtual const int update() = 0;

	virtual void mainDraw(sf::RenderTarget& ren);
	virtual const int mainInteraction(
		const sf::Event& ev,
		const gm::Vector& pos = { 0.f,0.f });

	virtual const bool mouseContain(const gm::Vector& pos)const;
	virtual const bool mouseContain(const sf::Event& ev) const;
	virtual const bool mouseMoveContain(sf::Event)const;
	virtual const bool mouseButtonContain(sf::Event)const;

	virtual void setPosition(const gm::Vector& pos_);
	virtual void setPosition(const float& x, const float& y);
	virtual const gm::Rectangle getGlobalBounds() const;

	virtual void setVisible(const bool vis_ = 1);
	virtual const bool getVisible() const;

	virtual void setActive(const bool act_ = 1);
	virtual const bool getActive() const;;

	virtual void setFocus(const bool act_ = 1);
	virtual const bool getFocus() const;

protected:

	virtual void receiveFocus();
	virtual void loseFocus();
public:

	void setInRectCenter(const gm::Rectangle& rect);
	void setInSizeCenter(const gm::Vector& size_);

	virtual ~BaseScreenObject();
};

using BSOP = BaseScreenObject*;

const sf::Texture createTextureFromText(const sf::Text& tex);
const sf::Texture createTextButton(sf::Text, sf::Sprite);

const sf::IntRect floatToInt_Rect(const sf::FloatRect& rect);
const sf::FloatRect intTofloat_Rect(const sf::IntRect& rect);

const sf::Vector2i floatToInt_Vector2(const sf::Vector2f& vect_);
const sf::Vector2f intToFloat_Vec2(const sf::Vector2i& vect_);

gm::Vector getSprSize(const sf::Sprite& s);

template<typename T>
inline const gm::real bottomOfRect(sf::Rect<T> rect) {
	return rect.top + rect.height;
}

template<typename T>
inline const T rigthOfRect(sf::Rect<T> rect) {
	return rect.left + rect.width;
}

template<typename T>
inline const sf::Vector2<T> downLeftRect(sf::Rect<T> rect) {
	return sf::Vector2<T>(rect.top + rect.height, rect.left + rect.width);
}

void moveSpriteOnTexture(sf::Sprite& spr, const sf::Vector2i& off);

template<typename T>
T rounding(T val_, T step_ = T{ 10 }) {
	int val = static_cast<int>(val_);
	int step = static_cast<int>(step_);
	if (val % step != 0) {
		return static_cast<T>((val / step + 1) * step);
	}
	return val_;
}

const gm::Vector getSpriteSize(const sf::Sprite& spr);

template<class T>
const gm::Vector operator/(const sf::Vector2<T>& v, gm::real f) {
	return { v.x / f, v.y / f };
}

template<class T>
const gm::Vector getRectSize(const sf::Rect<T>& rect) {
	return { rect.width,rect.height };
}
template<class T>
const sf::Rect<T> setRectSize(const sf::Rect<T>& rect, const gm::Vector& size) {
	auto s = getRectSize(rect);
	return { rect.left,rect.top,T(size.x),T(size.y) };
}
template<class T>
const sf::Rect<T> setRectSizeX(const sf::Rect<T>& rect, T x) {
	auto s = getRectSize(rect);
	return { rect.left,rect.top,x,rect.height };
}
template<class T>
const sf::Rect<T> setRectSizeY(const sf::Rect<T>& rect, T y) {
	auto s = getRectSize(rect);
	return { rect.left,rect.top,rect.width,y };
}
class SpriteContainer;

const sf::Sprite getRot90Spr(const sf::Sprite& spr);

const SpriteContainer getRot90Spr(const SpriteContainer& sc);
