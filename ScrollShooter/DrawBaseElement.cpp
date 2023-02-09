#include "pch.h"
#include "DrawBaseElement.h"
#include "Line.h"
#include "Utility.h"
#include "Circle.h"
#include "Rectangle.h"

void drawArrow(
	sf::RenderTarget& ren,
	const gm::Coord& p,
	gm::Vector dir,
	double len,
	const sf::Color color
) {
	sf::VertexArray arr{ sf::PrimitiveType::LinesStrip };
	dir.setLength(len);
	arr.append({ p + (dir >> (gm::PI * 3 / 4)) ,color });
	arr.append({ p ,color });
	arr.append({ p + (dir << (gm::PI * 3 / 4)) ,color });
	ren.draw(arr);
}

void drawLine(
	sf::RenderTarget& ren,
	const gm::Coord& begin,
	const gm::Coord& end,
	const sf::Color color
) {
	sf::VertexArray arr{ sf::PrimitiveType::Lines };
	arr.append({ begin,color });
	arr.append({ end,color });
	ren.draw(arr);
}

void drawX(
	sf::RenderTarget& ren,
	const gm::Coord& pos,
	const double& size,
	const sf::Color color
) {
	auto hs = size / 2.;
	drawLine(ren, pos.add(-hs, -hs), pos.add(hs, hs), color);
	drawLine(ren, pos.add(-hs, hs), pos.add(hs, -hs), color);
}

void drawDottedLine(
	sf::RenderTarget& ren,
	const gm::Coord& begin,
	const gm::Coord& end,
	double segment,
	double interval,
	const sf::Color& color
) {
	sf::VertexArray arr{ sf::PrimitiveType::Lines };
	auto dir = end - begin;
	auto len = !dir;
	auto dirs = dir.relen(segment);
	auto diri = dir.relen(interval);
	auto p = begin;
	int count = (int)len / (int)(interval + segment);
	for (auto i = 0; i < count; i++) {
		arr.append({ p,color });
		p += dirs;
		arr.append({ p,color });
		p += diri;
	}
	if (!gm::OE(!(p - end))) {
		arr.append({ p,color });
		arr.append({ end,color });
	}
	ren.draw(arr);
}

void drawCircle(
	sf::RenderTarget& ren,
	const gm::Coord& o,
	double r,
	const sf::Color& outlineColor,
	const sf::Color& fillColor
) {
	sf::CircleShape circ(r);
	circ.setPosition(o);
	circ.setFillColor(fillColor);
	circ.setOutlineColor(outlineColor);
	ren.draw(circ);
	/*sf::VertexArray arr{sf::PrimitiveType::LinesStrip};
	auto v = gm::VI.relen(r);
	for (auto i = 0; i < 32; i++) {
		arr.append({ o + v,color });
		v <<= gm::PI2 / 32;
	}
	arr.append({ o + v,color });
	ren.draw(arr);*/
}

void drawCircle(
	sf::RenderTarget& ren, 
	const gm::Circle& circ,
	const sf::Color& outlineColor,
	const sf::Color& fillColor
) {
	drawCircle(ren, circ.getCenter(), circ.radius, outlineColor, fillColor);
}

void drawDottedCircle(
	sf::RenderTarget& ren,
	const gm::Coord& o,
	double r,
	const sf::Color& color
) {
	sf::VertexArray arr{ sf::PrimitiveType::Lines };
	auto v = gm::VI.relen(r);
	for (auto i = 0; i < 32; i++) {
		arr.append({ o + v,color });
		v <<= gm::PI2 / 32;
	}
	ren.draw(arr);
}

// angle from 0 to 2PI
void drawCirclePart(
	sf::RenderTarget& ren,
	const gm::Coord& center,
	double r,
	gm::angle beg,
	gm::angle end,
	const sf::Color& color
) {
	sf::VertexArray arr{ sf::PrimitiveType::LinesStrip };
	auto v = gm::VI.relen(r) << beg;
	const int part = 64;
	if (beg > end) {
		end += gm::PI2;
	}
	int count = (int)round((end - beg) / gm::PI2 * part);
	for (auto i = 0; i <= count; i++) {
		arr.append({ center + v,color });
		v <<= gm::PI2 / part;
	}
	ren.draw(arr);
}

void drawDottedCirclePart(
	sf::RenderTarget& ren,
	const gm::Coord& o,
	double r,
	gm::angle beg,
	gm::angle end,
	const sf::Color& color
) {
	sf::VertexArray arr{ sf::PrimitiveType::Lines };
	auto v = gm::VI.relen(r) >> beg;
	const int part = 64;
	for (auto i = 0; i <= round((end - beg) / gm::PI2 * part); i++) {
		arr.append({ o + v,color });
		v <<= gm::PI2 / part;
	}
	ren.draw(arr);
}

void writeText(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font,
	const gm::Vector& pos,
	int size
) {
	sf::Text t(s, font, size);
	t.setPosition(pos.correct_coord(1.));
	ren.draw(t);
}

void writeTextC(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font,
	const gm::Vector& pos,
	int size
) {
	sf::Text t(s, font, size);
	gm::Rectangle rect = t.getGlobalBounds();
	t.setPosition((pos - rect.getSize() / 2.).correct_coord(1));
	ren.draw(t);
}

void writeTextRT(
	sf::RenderTarget& ren,
	const sf::String& s,
	const sf::Font& font,
	const gm::Vector& pos,
	int size
) {
	sf::Text t(s, font, size);
	gm::Rectangle rect = t.getGlobalBounds();
	t.setPosition(pos.addX(-rect.getSize().x).correct_coord(1));
	ren.draw(t);
}

void writeTextLB(sf::RenderTarget& ren, const sf::String& s, const sf::Font& font, const gm::Vector& pos, int size) {
	sf::Text t(s, font, size);
	gm::Rectangle rect = t.getGlobalBounds();
	t.setPosition(pos.addY(-rect.getSize().y).correct_coord(1));
	ren.draw(t);
}

void writeTextRB(sf::RenderTarget& ren, const sf::String& s, const sf::Font& font, const gm::Vector& pos, int size) {
	sf::Text t(s, font, size);
	gm::Rectangle rect = t.getGlobalBounds();
	t.setPosition(pos - rect.getSize().correct_coord(1));
	ren.draw(t);
}

void writeInt(
	sf::RenderTarget& ren,
	int num,
	const sf::Font& font,
	const gm::Vector& pos,
	int size
) {
	writeText(ren, std::to_string(num), font, pos, size);
}

void writeDouble(
	sf::RenderTarget& ren,
	double num,
	const sf::Font& font,
	const gm::Vector& pos,
	int size
) {
	writeText(ren, std::to_string(num), font, pos, size);
}

void drawArrowLine(
	sf::RenderTarget& ren,
	const gm::Coord& begin,
	const gm::Coord& end,
	double len,
	const sf::Color color
) {
	drawArrow(ren, end, end - begin, len, color);
	drawLine(ren, begin, end, color);
}

void drawDottedArrowLine(
	sf::RenderTarget& ren,
	const gm::Coord& begin,
	const gm::Coord& end,
	double arrowLen,
	double segment,
	double interval,
	const sf::Color color
) {
	drawArrow(ren, end, end - begin, arrowLen, color);
	drawDottedLine(ren, begin, end, segment, interval, color);
}

void drawRectangle(
	sf::RenderTarget& ren, 
	const gm::Rectangle& rect, 
	const sf::Color& outlineColor, 
	const sf::Color& fillColor
) {
	drawRectangleS(ren, rect.getLeftTop(), rect.getSize(), outlineColor, fillColor);
}

void drawRectangle(
	sf::RenderTarget& ren,
	const gm::Coord& leftTop,
	const gm::Coord& rightDown,
	const sf::Color& outlineColor,
	const sf::Color& fillColor
) {
	drawRectangleS(ren, leftTop, rightDown - leftTop, outlineColor, fillColor);
}

void drawRectangleS(
	sf::RenderTarget& ren,
	gm::Coord leftTop,
	gm::Vector size,
	const sf::Color& outlineColor,
	const sf::Color& fillColor
) {
	leftTop += gm::VIJ;
	sf::VertexArray arr(sf::PrimitiveType::LinesStrip);
	arr.append({ leftTop.correct_coord(1),outlineColor });
	arr.append({ leftTop.addX(size.x - 1).correct_coord(1),outlineColor });
	arr.append({ (leftTop + size - gm::VIJ).correct_coord(1),outlineColor });
	arr.append({ leftTop.addY(size.y - 1).correct_coord(1),outlineColor });
	arr.append({ leftTop.correct_coord(1),outlineColor });
	// ren.draw(arr);
	sf::RectangleShape shape(size);
	shape.setFillColor(fillColor);;
	shape.setOutlineColor(outlineColor);
	shape.setPosition(leftTop - gm::VXY);
	shape.setOutlineThickness(1);
	ren.draw(shape);
}

void drawRectangleC(
	sf::RenderTarget& ren,
	const gm::Coord& center,
	const gm::Vector& halfSize,
	const sf::Color& outlineColor,
	const sf::Color& fillColor
) {
	drawRectangleS(ren, center - halfSize, halfSize * 2 /*- gm::VIJ*/, outlineColor, fillColor);
}

void drawSquare(
	sf::RenderTarget& ren,
	const gm::Coord& leftTop,
	gm::lenght len,
	const sf::Color& outlineColor,
	const sf::Color& fillColor
) {
	drawRectangleS(ren, leftTop, { len,len }, outlineColor, fillColor);
}

void drawSquareC(
	sf::RenderTarget& ren,
	const gm::Coord& center,
	gm::lenght len,
	const sf::Color& outlineColor,
	const sf::Color& fillColor
) {
	drawRectangleC(ren,
		center,
		{ len, len },
		outlineColor,
		fillColor
	);
}

void drawSpiral(
	sf::RenderTarget& ren,
	const gm::Coord& center,
	const gm::lenght& radius,
	const gm::lenght& radiusSpeed,
	const gm::angle& startAngle,
	const gm::angle& angleLen,
	const gm::angle& angleSpeed,
	const sf::Color& color,
	const bool& isDotted
) {
	sf::VertexArray spiral(sf::PrimitiveType::LinesStrip);
	if (isDotted) {
		spiral.setPrimitiveType(sf::PrimitiveType::Lines);
	}
	auto r = abs(radius);
	auto rSpeed = radiusSpeed * abs((gm::PI2 / 64) / angleSpeed);
	gm::Coord v = gm::VI.relen(r) << startAngle;
	int accuracy = 64;
	auto aSpeed = gm::PI / 32 * gm::sign(angleSpeed);
	int count = std::min((int)round(abs(angleLen) / gm::PI2 * 64), 640);
	for (int i = 0; i < count; i++) {
		spiral.append(sf::Vertex(center + v, color));
		r += rSpeed;
		v <<= aSpeed;
		v.setLength(r);
	}
	v = gm::VI.relen(abs(radius) +
		(abs(angleLen / angleSpeed) * radiusSpeed)) <<
		(abs(angleLen) * gm::sign(angleSpeed) + startAngle);
	spiral.append(sf::Vertex(center + v, color));
	ren.draw(spiral);
}

void drawSinus(
	sf::RenderTarget& ren,
	const gm::Coord& beg,
	const gm::Coord& end,
	const gm::lenght& delta,
	const gm::lenght& ampl,
	const gm::lenght& amplSpead,
	const gm::lenght& period,
	const gm::lenght& periodSpead,
	const bool& isDotted
) {
	int step = 30;
	sf::VertexArray sinus(sf::PrimitiveType::LinesStrip);
	if (isDotted) {
		sinus.setPrimitiveType(sf::PrimitiveType::Lines);
	}
	gm::Line l(beg, end);
	gm::angle ang = gm::VI ^ (end - beg);
	gm::Coord p =
		(gm::Coord(0., ampl * sin(-delta / period * gm::PI2)) << ang) +
		beg;
	int t = 0;
	sinus.append(sf::Vertex(p, sf::Color::White));
	while ((p - end) * (beg - end) >= 0 && t / step < 1000) {
		double k = gm::PI2 / (period + periodSpead * t);
		double nowAmp = ampl + amplSpead * t;
		gm::lenght nowLen = beg / l.projection(p) - delta;
		gm::Vector n(-k * nowAmp * cos(nowLen * k), 1.);
		gm::Vector speedV = n.relen(0.1) >> gm::PI_1_2;
		speedV <<= ang;
		p += speedV * step;
		sinus.append(sf::Vertex(p, sf::Color::White));
		t += step;
	}
	ren.draw(sinus);
}

void drawCurve4(
	sf::RenderTarget& ren,
	const gm::Coord& p0,
	const gm::Coord& p1,
	const gm::Coord& p2,
	const gm::Coord& p3,
	const sf::Color& color,
	const bool& isDotted
) {
	sf::VertexArray curve(sf::PrimitiveType::LinesStrip);
	if (isDotted) {
		curve.setPrimitiveType(sf::PrimitiveType::Lines);
	}
	for (int i = 0; i <= 100; i++) {
		double t = 1. / 100. * i;
		double t_ = 1 - t;
		curve.append(sf::Vertex(
			p0 * t * t * t +
			3 * p1 * t * t * t_ +
			3 * p2 * t * t_ * t_ +
			p3 * t_ * t_ * t_,
			color));
	}
	ren.draw(curve);
}
