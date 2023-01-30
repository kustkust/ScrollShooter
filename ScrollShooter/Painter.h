#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Vector2D.h"
#include "Rectangle.h"
extern sf::Font Arial;

class Painter {
	sf::RenderTarget& ren;
	sf::Color fillColor, outlineColor;
	sf::Font font;
	gm::Vector2D offset;
	uint32_t fontSize = 20;
public:
	Painter(sf::RenderTarget& target, const sf::Color fillColor = sf::Color::White, const sf::Color outlineColor = sf::Color::Black, const sf::Font font = Arial);

	Painter& setFillColor(const sf::Color& fillColor_);
	Painter& setOutlineColor(const sf::Color& outlineColor_);
	Painter& setFont(const sf::Font& font_);
	Painter& setFontSize(uint32_t fonstSize_);
	Painter& setOffset(const gm::Vector2D& offset_);

	sf::Color getFillColor() const;
	sf::Color getOutlineColor() const;
	sf::Font getFont() const;
	uint32_t getFontSize() const;
	gm::Vector2D getOffset() const;

	Painter& drawRectangle(const gm::Rectangle& rect);
	Painter& drawRectangle(const gm::Coord2D& leftTop, const gm::Coord2D& rightDown);
	Painter& drawRectangleS(gm::Coord2D leftTop, gm::Vector2D size);
	Painter& drawRectangleC(gm::Coord2D center, gm::Size2D size);
	Painter& drawSquare(gm::Coord2D leftTop, gm::lenght len);
	Painter& drawSquareC(gm::Coord2D center, gm::lenght len);

	Painter& writeText(const std::string& text, const gm::Coord2D& pos);
	Painter& writeTextC(const std::string& text, const gm::Coord2D& pos);
	Painter& writeTextRT(const std::string& text, const gm::Coord2D& pos);
	Painter& writeTextLB(const std::string& text, const gm::Coord2D& pos);
	Painter& writeTextRB(const std::string& text, const gm::Coord2D& pos);
};