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

Painter& Painter::setOffset(const gm::Vector& offset_) {
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

gm::Vector Painter::getOffset() const {
	return offset;
}

Painter& Painter::drawRectangle(const gm::Rectangle& rect) {
	gm::Rectangle rect_ = rect;
	rect_.move(offset);
	::drawRectangle(ren, rect_, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawRectangle(const gm::Coord& leftTop, const gm::Coord& rightDown) {
	::drawRectangle(ren, leftTop + offset, rightDown + offset, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawRectangleS(gm::Coord leftTop, gm::Vector size) {
	::drawRectangleS(ren, leftTop + offset, size, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawRectangleC(gm::Coord center, gm::Size size) {
	::drawRectangleC(ren, center + offset, size, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawSquare(gm::Coord leftTop, gm::lenght len) {
	::drawSquare(ren, leftTop + offset, len, outlineColor, fillColor);
	return *this;
}

Painter& Painter::drawSquareC(gm::Coord center, gm::lenght len) {
	::drawSquareC(ren, center + offset, len, outlineColor, fillColor);
	return *this;
}

Painter& Painter::writeText(const std::string& text, const gm::Coord& pos) {
	::writeText(ren, text, font, pos + offset, fontSize);
	return *this;
}

Painter& Painter::writeTextC(const std::string& text, const gm::Coord& pos) {
	::writeTextC(ren, text, font, pos + offset, fontSize);
	return *this;
}

Painter& Painter::writeTextRT(const std::string& text, const gm::Coord& pos) {
	::writeTextRT(ren, text, font, pos + offset, fontSize);
	return *this;
}

Painter& Painter::writeTextLB(const std::string& text, const gm::Coord& pos) {
	::writeTextLB(ren, text, font, pos + offset, fontSize);
	return *this;
}

Painter& Painter::writeTextRB(const std::string& text, const gm::Coord& pos) {
	::writeTextRB(ren, text, font, pos + offset, fontSize);
	return *this;
}
