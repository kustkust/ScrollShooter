#pragma once
#include "SFML/Graphics.hpp"
#include "Vector2D.h"
#include "Utility.h"
#include "Rectangle.h"

void drawArrow(
	sf::RenderTarget&ren,
	const gm::Coord2D&p,
	gm::Vector2D dir,
	float len,
	const sf::Color color = sf::Color::White
);

void drawLine(
	sf::RenderTarget&ren,
	const gm::Coord2D&begin,
	const gm::Coord2D&end,
	const sf::Color color = sf::Color::White
);

void drawX(
	sf::RenderTarget&ren,
	const gm::Coord2D&pos,
	const double&size = 10.,
	const sf::Color color = sf::Color::White
);

void drawDottedLine(
	sf::RenderTarget&ren,
	const gm::Coord2D&begin,
	const gm::Coord2D&end,
	float segment,
	float interval,
	const sf::Color&color = sf::Color::White
);

void drawCircle(
	sf::RenderTarget&ren,
	const gm::Coord2D&o,
	double r,
	const sf::Color&color = sf::Color::White
);

void drawDottedCircle(
	sf::RenderTarget&ren,
	const gm::Coord2D&o,
	float r,
	const sf::Color&color
);

void drawCirclePart(
	sf::RenderTarget&ren,
	const gm::Coord2D&o,
	float r,
	gm::angle beg,
	gm::angle end,
	const sf::Color&color = sf::Color::White
);

void drawDottedCirclePart(
	sf::RenderTarget&ren,
	const gm::Coord2D&o,
	float r,
	gm::angle beg,
	gm::angle end,
	const sf::Color&color = sf::Color::White
);

void writeText(
	sf::RenderTarget&ren,
	const sf::String&s,
	const sf::Font& font = Arial,
	const gm::Vector2D&pos = gm::NV,
	size_t size = 20
);

void writeTextC(
	sf::RenderTarget&ren, 
	const sf::String&s,
	const sf::Font& font = Arial,
	const gm::Vector2D&pos = gm::NV,
	size_t size = 20
);

void writeTextRT(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font = Arial,
	const gm::Vector2D& pos = gm::NV,
	size_t size = 20
);


void writeTextLB(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font = Arial,
	const gm::Vector2D& pos = gm::NV,
	size_t size = 20
);


void writeTextRB(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font = Arial,
	const gm::Vector2D& pos = gm::NV,
	size_t size = 20
);

void writeInt(
	sf::RenderTarget&ren,
	int num,
	const sf::Font& font = Arial,
	const gm::Vector2D&pos = gm::NV,
	size_t size = 20
);

void writeDouble(
	sf::RenderTarget&ren,
	double num,
	const sf::Font& font = Arial,
	const gm::Vector2D&pos = gm::NV,
	size_t size = 20
);

void drawArrowLine(
	sf::RenderTarget&ren,
	const gm::Coord2D&begin,
	const gm::Coord2D&end,
	float len,
	const sf::Color color = sf::Color::White
);

void drawDottedArrowLine(
	sf::RenderTarget&ren,
	const gm::Coord2D&begin,
	const gm::Coord2D&end,
	double arrowLen,
	double segment,
	double interval,
	const sf::Color color = sf::Color::White
);

void drawRectangle(
	sf::RenderTarget& ren,
	const gm::Rectangle& rect,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::White
);

void drawRectangle(
	sf::RenderTarget&ren,
	const gm::Coord2D&leftTop,
	const gm::Coord2D&rightDown,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::White
);

void drawRectangleS(
	sf::RenderTarget&ren,
	gm::Coord2D leftTop,
	gm::Vector2D size,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::White
);

void drawRectangleC(
	sf::RenderTarget&ren,
	const gm::Coord2D&center,
	const gm::Vector2D&size,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::White
);

void drawSquare(
	sf::RenderTarget&ren,
	const gm::Coord2D&leftTop,
	gm::lenght len,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::White
);

void drawSquareC(
	sf::RenderTarget&ren,
	const gm::Coord2D&center,
	gm::lenght len,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::White
);

void drawSpiral(
	sf::RenderTarget&ren,
	const gm::Coord2D&center,
	const gm::lenght&radius,
	const gm::lenght&radiusSpeed,
	const gm::angle&startAngle,
	const gm::angle&angleLen,
	const gm::angle&angleSpeed,
	const sf::Color&color = sf::Color::White,
	const bool&isDotted = false
);

void drawSinus(
	sf::RenderTarget&ren,
	const gm::Coord2D&beg,
	const gm::Coord2D&end,
	const gm::lenght&delta,
	const gm::lenght&ampl,
	const gm::lenght&amplSpead,
	const gm::lenght&period,
	const gm::lenght&periodSpead,
	const bool&isDotted = false
);

void drawCurve4(
	sf::RenderTarget&ren,
	const gm::Coord2D&p0,
	const gm::Coord2D&p1,
	const gm::Coord2D&p2,
	const gm::Coord2D&p3,
	const sf::Color&color = sf::Color::White,
	const bool&isDotted = false
);