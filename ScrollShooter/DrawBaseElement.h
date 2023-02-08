#pragma once
#include "SFML/Graphics.hpp"
#include "Vector.h"
#include "Utility.h"
#include "Rectangle.h"

void drawArrow(
	sf::RenderTarget&ren,
	const gm::Coord&p,
	gm::Vector dir,
	double len,
	const sf::Color color = sf::Color::White
);

void drawLine(
	sf::RenderTarget&ren,
	const gm::Coord&begin,
	const gm::Coord&end,
	const sf::Color color = sf::Color::White
);

void drawX(
	sf::RenderTarget&ren,
	const gm::Coord&pos,
	const double&size = 10.,
	const sf::Color color = sf::Color::White
);

void drawDottedLine(
	sf::RenderTarget&ren,
	const gm::Coord&begin,
	const gm::Coord&end,
	double segment,
	double interval,
	const sf::Color&color = sf::Color::White
);

void drawCircle(
	sf::RenderTarget&ren,
	const gm::Coord&o,
	double r,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::Transparent
);

void drawCircle(
	sf::RenderTarget& ren,
	const gm::Circle& circl,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::Transparent
);

void drawDottedCircle(
	sf::RenderTarget&ren,
	const gm::Coord&o,
	double r,
	const sf::Color&color
);

void drawCirclePart(
	sf::RenderTarget&ren,
	const gm::Coord&o,
	double r,
	gm::angle beg,
	gm::angle end,
	const sf::Color&color = sf::Color::White
);

void drawDottedCirclePart(
	sf::RenderTarget&ren,
	const gm::Coord&o,
	double r,
	gm::angle beg,
	gm::angle end,
	const sf::Color&color = sf::Color::White
);

void writeText(
	sf::RenderTarget&ren,
	const sf::String&s,
	const sf::Font& font = Arial,
	const gm::Vector&pos = gm::NV,
	int size = 20
);

void writeTextC(
	sf::RenderTarget&ren, 
	const sf::String&s,
	const sf::Font& font = Arial,
	const gm::Vector&pos = gm::NV,
	int size = 20
);

void writeTextRT(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font = Arial,
	const gm::Vector& pos = gm::NV,
	int size = 20
);


void writeTextLB(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font = Arial,
	const gm::Vector& pos = gm::NV,
	int size = 20
);


void writeTextRB(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font = Arial,
	const gm::Vector& pos = gm::NV,
	int size = 20
);

void writeInt(
	sf::RenderTarget&ren,
	int num,
	const sf::Font& font = Arial,
	const gm::Vector&pos = gm::NV,
	int size = 20
);

void writeDouble(
	sf::RenderTarget&ren,
	double num,
	const sf::Font& font = Arial,
	const gm::Vector&pos = gm::NV,
	int size = 20
);

void drawArrowLine(
	sf::RenderTarget&ren,
	const gm::Coord&begin,
	const gm::Coord&end,
	double len,
	const sf::Color color = sf::Color::White
);

void drawDottedArrowLine(
	sf::RenderTarget&ren,
	const gm::Coord&begin,
	const gm::Coord&end,
	double arrowLen,
	double segment,
	double interval,
	const sf::Color color = sf::Color::White
);

void drawRectangle(
	sf::RenderTarget& ren,
	const gm::Rectangle& rect,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::Transparent
);

void drawRectangle(
	sf::RenderTarget&ren,
	const gm::Coord&leftTop,
	const gm::Coord&rightDown,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::Transparent
);

void drawRectangleS(
	sf::RenderTarget&ren,
	gm::Coord leftTop,
	gm::Vector size,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::Transparent
);

void drawRectangleC(
	sf::RenderTarget&ren,
	const gm::Coord&center,
	const gm::Vector&size,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::Transparent
);

void drawSquare(
	sf::RenderTarget&ren,
	const gm::Coord&leftTop,
	gm::lenght len,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::Transparent
);

void drawSquareC(
	sf::RenderTarget&ren,
	const gm::Coord&center,
	gm::lenght len,
	const sf::Color& outlineColor = sf::Color::Black,
	const sf::Color& fillColor = sf::Color::Transparent
);

void drawSpiral(
	sf::RenderTarget&ren,
	const gm::Coord&center,
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
	const gm::Coord&beg,
	const gm::Coord&end,
	const gm::lenght&delta,
	const gm::lenght&ampl,
	const gm::lenght&amplSpead,
	const gm::lenght&period,
	const gm::lenght&periodSpead,
	const bool&isDotted = false
);

void drawCurve4(
	sf::RenderTarget&ren,
	const gm::Coord&p0,
	const gm::Coord&p1,
	const gm::Coord&p2,
	const gm::Coord&p3,
	const sf::Color&color = sf::Color::White,
	const bool&isDotted = false
);