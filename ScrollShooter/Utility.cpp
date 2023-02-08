#include "pch.h"
#include "Utility.h"
using uint = unsigned;

sf::Font Arial;
const gm::Vector winSize(1300, 720);

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
		if (s[0] >= '0' && s[0] <= '9') {
			c += (s[0] - '0') * 16;
		} else {
			c += (s[0] - 'A' + 10) * 16;
		}
		if (s[1] >= '0' && s[1] <= '9') {
			c += s[1] - '0';
		} else {
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
std::string dropExt(const std::string& file) {
	int i = static_cast<int>(file.size()) - 1;
	while (file[i] != '.') { i--; }
	return file.substr(0, i);
}

std::wstring dropExt(const std::wstring& file) {
	int i = static_cast<int>(file.size()) - 1;
	while (file[i] != L'.') { i--; }
	return file.substr(0, i);
}

std::string extractName(const std::string& file) {
	int i = static_cast<int>(file.size()) - 1;
	while (i >= 0 && file[i] != '\\' && file[i] != '/') { i--; }
	return file.substr(i + 1);
}

std::wstring extractName(const std::wstring& file) {
	int i = static_cast<int>(file.size()) - 1;
	while (i >= 0 && file[i] != L'\\' && file[i] != L'/') { i--; }
	return file.substr(i + 1);
}

std::string extractPath(const std::string& file) {
	int i = static_cast<int>(file.size()) - 1;
	while (i >= 0 && file[i] != '\\' && file[i] != '/') { i--; }
	return file.substr(0, i + 1);
}

std::wstring extractPath(const std::wstring& file) {
	int i = static_cast<int>(file.size()) - 1;
	while (i >= 0 && file[i] != L'\\' && file[i] != L'/') { i--; }
	return file.substr(0, i + 1);

}

std::string NoObj("");

sf::Color Gray(128, 128, 128, 255);
sf::Color DarkGray(64, 64, 64, 255);
sf::Color LightGray(196, 196, 196, 255);

sf::Event moveEvMousePos(const sf::Event& ev_, const gm::Vector& off) {
	sf::Event ev = ev_;
	if (ev_.type == sf::Event::MouseButtonPressed ||
		ev_.type == sf::Event::MouseButtonReleased
		) {
		ev.mouseButton.x += int(off.x);
		ev.mouseButton.y += int(off.y);
	} else if (ev.type == sf::Event::MouseMoved) {
		ev.mouseMove.x += int(off.x);
		ev.mouseMove.y += int(off.y);
	} else if (ev.type == sf::Event::MouseWheelScrolled) {
		ev.mouseWheelScroll.x += int(off.x);
		ev.mouseWheelScroll.y += int(off.y);
	}
	return ev;
}

const gm::Vector getMouseButPos(const sf::Event& ev) {
	return gm::Vector(ev.mouseButton.x, ev.mouseButton.y);
}

const gm::Vector getMouseMovPos(const sf::Event& ev) {
	return gm::Vector(ev.mouseMove.x, ev.mouseMove.y);
}

const gm::Vector getMousePos(const sf::Event& ev) {
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

void setMaxAbsVector(gm::Vector& l, const gm::Vector& r) {
	if (abs(l.x) < abs(r.x)) {
		l.x = r.x;
	}
	if (abs(l.y) < abs(r.y)) {
		l.y = r.y;
	}
}

gm::Rectangle jsonRect(json& jrect) {
	return { jsonVector(jrect), jsonSize(jrect) };
}

gm::Vector jsonVector(json& vec) {
	return gm::Vector(vec[Name::X].get<gm::real>(), vec[Name::Y].get<gm::real>());
}

gm::Vector jsonSize(json& size) {
	gm::Vector tmpsize = gm::NV;

	auto w = size[Name::W];
	auto widht = size[Name::Width];
	auto x = size[Name::X];
	if (w.type() != json::value_t::null) {
		tmpsize.x = w.get<double>();
	} else if (widht.type() != json::value_t::null) {
		tmpsize.x = widht.get<double>();
	} else if (x.type() != json::value_t::null) {
		tmpsize.x = x.get<double>();
	}

	auto h = size[Name::H];
	auto height = size[Name::Height];
	auto y = size[Name::Y];
	if (h.type() != json::value_t::null) {
		tmpsize.y = h.get<double>();
	} else if (height.type() != json::value_t::null) {
		tmpsize.y = height.get<double>();
	} else if (y.type() != json::value_t::null) {
		tmpsize.y = y.get<double>();
	}

	return tmpsize;
}