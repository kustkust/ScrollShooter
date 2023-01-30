#include "pch.h"
#include "Utility.h"
using uint = unsigned;

sf::Font Arial;
const gm::Vector2D winSize(1300, 720);

int fStub0(void*) {
	return 0;
}

int fStub1(void*) {
	return 1;
}
int random(int l, int r) {
	return rand() % (r - l + 1) + l;
}
sf::Color strToColor(std::string color) {
	auto strToHex = [](std::string s)->sf::Uint8 {
		sf::Uint8 c = 0;
		if (s[0] >= '0'&&s[0] <= '9') {
			c += (s[0] - '0') * 16;
		}
		else {
			c += (s[0] - 'A' + 10) * 16;
		}
		if (s[1] >= '0'&&s[1] <= '9') {
			c += s[1] - '0';
		}
		else {
			c += s[1] - 'A' + 10;
		}
		return c;
	};
	return sf::Color{
		strToHex(std::string(color[0], color[1])),
		strToHex(std::string(color[2], color[3])),
		strToHex(std::string(color[4], color[5])),
		255,
	};
}
std::string dropExt(const std::string & file) {
	int i = file.size() - 1;
	while (file[i] != '.') { i--; }
	return file.substr(0, i);
}

std::wstring dropExt(const std::wstring & file) {
	int i = file.size() - 1;
	while (file[i] != L'.') { i--; }
	return file.substr(0, i);
}

std::string extractName(const std::string&file) {
	int i = file.size() - 1;
	while (i >= 0 && file[i] != '\\') { i--; }
	return file.substr(i + 1);
}

std::wstring extractName(const std::wstring&file) {
	int i = file.size() - 1;
	while (i >= 0 && file[i] != L'\\') { i--; }
	return file.substr(i + 1);
}

std::string extractPath(const std::string & file) {
	int i = file.size() - 1;
	while (i >= 0 && file[i] != '\\') { i--; }
	return file.substr(0, i + 1);
}

std::wstring extractPath(const std::wstring & file) {
	int i = file.size() - 1;
	while (i >= 0 && file[i] != L'\\') { i--; }
	return file.substr(0, i + 1);

}

std::string NoObj("");

sf::Color Gray(128, 128, 128, 255);
sf::Color DarkGray(64, 64, 64, 255);
sf::Color LightGray(196, 196, 196, 255);

sf::Event moveEvMousePos(const sf::Event & ev_, const gm::Vector2D&off) {
	sf::Event ev = ev_;
	if (ev_.type == sf::Event::MouseButtonPressed ||
		ev_.type == sf::Event::MouseButtonReleased
		) {
		ev.mouseButton.x += int(off.x);
		ev.mouseButton.y += int(off.y);
	}
	else if (ev.type == sf::Event::MouseMoved) {
		ev.mouseMove.x += int(off.x);
		ev.mouseMove.y += int(off.y);
	}
	else if (ev.type == sf::Event::MouseWheelScrolled) {
		ev.mouseWheelScroll.x += int(off.x);
		ev.mouseWheelScroll.y += int(off.y);
	}
	return ev;
}

const gm::Vector2D getMouseButPos(const sf::Event&ev) {
	return gm::Vector2D(ev.mouseButton.x, ev.mouseButton.y);
}

const gm::Vector2D getMouseMovPos(const sf::Event & ev) {
	return gm::Vector2D(ev.mouseMove.x, ev.mouseMove.y);
}

const gm::Vector2D getMousePos(const sf::Event & ev) {
	switch (ev.type) {
	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		return { ev.mouseButton.x,ev.mouseButton.y };
	case sf::Event::MouseMoved:
		return { ev.mouseMove.x,ev.mouseMove.y };
	case sf::Event::MouseWheelMoved:
	case sf::Event::MouseWheelScrolled:
		return { ev.mouseWheelScroll.x,ev.mouseWheelScroll.y };
	default:
		return gm::NV;
	}
}

double sgn(double val) {
	return (val > 0.) - (val < 0.);
}

void fixWay(std::string&path) {
	for (int i = 0; i < (int)path.size(); i++) {
		if (path[i] == '\/') {
			path[i] = '\\';
		}
	}
}

void setMaxAbsVector(gm::Vector2D&l, const gm::Vector2D&r) {
	if (abs(l.x) < abs(r.x)) {
		l.x = r.x;
	}
	if (abs(l.y) < abs(r.y)) {
		l.y = r.y;
	}
}