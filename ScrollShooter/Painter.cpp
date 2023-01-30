#include "pch.h"
#include "DrawBaseElement.h"
#include "Painter.h"

Painter::Painter(sf::RenderTarget& target, const sf::Color fillColor, const sf::Color outlineColor, const sf::Font font) : ren(target), fillColor(fillColor), outlineColor(outlineColor), font(font) {}

Painter& Painter::setFillColor(const sf::Color& fillColor_) {
	fillColor = fillColor_;
	return *this;
}

Painter& Painter::setOutlineColor(const sf::Color& outlineColor_) {
	outlineColor = outlineColor_;
	return *this;
}

Painter& Painter::setFont(const sf::Font& font_) {
	font = font_;
	return *this;
}

Painter& Painter::setFontSize(uint32_t fonstSize_) {
	fontSize = fonstSize_;
	return *this;
}

Painter& Painter::setOffset(const gm::Vector2D& offset_) {
	offset = offset_;
	return *this;
}

sf::Color Painter::getFillColor() const {
	return fillColor;
}

sf::Color Painter::getOutlineColor() const {
	return outlineColor;
}

sf::Font Painter::getFont() const {
	return font;
}

uint32_t Painter::getFontSize() const {
	return fontSize;
}

gm::Vector2D Painter::getOffset() const {
	return offset;
}

Painter& Painter::drawRectangle(const gm::Rectangle& rect) {
	::drawRectangle(ren, rect, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawRectangle(const gm::Coord2D& leftTop, const gm::Coord2D& rightDown) {
	::drawRectangle(ren, leftTop + offset, rightDown + offset, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawRectangleS(gm::Coord2D leftTop, gm::Vector2D size) {
	::drawRectangleS(ren, leftTop + offset, size, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawRectangleC(gm::Coord2D center, gm::Size2D size) {
	::drawRectangleC(ren, center + offset, size, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawSquare(gm::Coord2D leftTop, gm::lenght len) {
	::drawSquare(ren, leftTop + offset, len, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawSquareC(gm::Coord2D center, gm::lenght len) {
	::drawSquareC(ren, center + offset, len, outlineColor, fillColor);
	return *this;
}

Painter& Painter::writeText(const std::string& text, const gm::Coord2D& pos) {
	::writeText(ren, text, font, pos + offset, fontSize);
	return *this;
}

Painter& Painter::writeTextC(const std::string& text, const gm::Coord2D& pos) {
	::writeTextC(ren, text, font, pos + offset, fontSize);
	return *this;
}

Painter& Painter::writeTextRT(const std::string& text, const gm::Coord2D& pos) {
	::writeTextRT(ren, text, font, pos + offset, fontSize);
	return *this;
}

Painter& Painter::writeTextLB(const std::string& text, const gm::Coord2D& pos) {
	::writeTextLB(ren, text, font, pos + offset, fontSize);
	return *this;
}

Painter& Painter::writeTextRB(const std::string& text, const gm::Coord2D& pos) {
	::writeTextRB(ren, text, font, pos + offset, fontSize);
	return *this;
}
