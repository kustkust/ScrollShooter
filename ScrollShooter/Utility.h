#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Names.h"
#include "Rectangle.h"

extern sf::Font Arial;

using json = nlohmann::json;

extern const gm::Vector winSize;
template <class T>
using matrix = std::vector<std::vector<T>>;

template<class T>
bool setMin(T& val, const T& n) {
	if (val > n) {
		val = n;
		return true;
	}
	return false;
}

template<class T>
bool setMax(T& val, const T& n) {
	if (val < n) {
		val = n;
		return true;
	}
	return false;
}

template<class T>
bool setAbsMax(T& val, const T& n) {
	if (abs(val) < abs(n)) {
		val = n;
		return true;
	}
	return false;
}

template<class T>
bool setAbsMin(T& val, const T& n) {
	if (abs(val) > abs(n)) {
		val = n;
		return true;
	}
	return false;
}

template<class T>
const T& absMin(const T& l, const T& r) {
	if (abs(l) > abs(r)) return r;
	return l;
}

template<class T>
const T& absMax(const T& l, const T& r) {
	if (abs(l) < abs(r)) return r;
	return l;
}

template<class T>
bool compearFor(const T& l, const std::vector<T>& r) {
	for (auto& i : r) if (l == i) return true;
	return false;
}

int random(int l, int r);

sf::Color strToColor(std::string color);

std::string dropExt(const std::string& file);
std::wstring dropExt(const std::wstring& file);
std::string extractName(const std::string& file);
std::wstring extractName(const std::wstring& file);
std::string extractPath(const std::string& file);
std::wstring extractPath(const std::wstring& file);

template <class T>
const std::string toStr(const T& val) {
	std::stringstream buf;
	buf << val;
	std::string s;
	std::getline(buf, s);
	return s;
}

int fStub0(void*);
int fStub1(void*);

extern std::string NoObj;

extern sf::Color Gray;
extern sf::Color DarkGray;
extern sf::Color LightGray;

template<class T>
const sf::Vector2<T> getRectPosSF(const sf::Rect<T>& rect) {
	return sf::Vector2<T>{ rect.left, rect.top };
}

template<class T>
const gm::Vector getRectPos(const sf::Rect<T>& rect) {
	return { rect.left, rect.top };
}

sf::Event moveEvMousePos(const sf::Event& ev, const gm::Vector& off);

const gm::Vector getMouseButPos(const sf::Event& ev);
const gm::Vector getMouseMovPos(const sf::Event& ev);
const gm::Vector getMousePos(const sf::Event& ev);


double sgn(double val);

template<typename T>
void limit(T& val, const T& botom, const T& top) {
	if (val < botom) {
		val = botom;
	} else if (val > top) {
		val = top;
	}
}

template<typename T>
void limitTop(T& val, const T& top) {
	if (val > top) {
		val = top;
	}
}

template<typename T>
void absLimitTop(T& val, const T& lim) {
	if (abs(val) > lim) {
		val = lim * sgn(val);
	}
}

void setMaxAbsVector(gm::Vector& l, const gm::Vector& r);

template <class T>
gm::Vector getSizeTempl(const T& trans) {
	auto tmp = trans.getGlobalBounds();
	return { tmp.width,tmp.height };
}

template <class T>
void matrixInit(
	matrix<T>& m,
	int w,
	int h,
	const std::function<void(T&, int, int)>& initF = [](T&, int, int)->void {}
) {
	m.resize(w);
	int x_ = 0;
	for (auto& k : m) {
		k.resize(h);
		int y_ = 0;
		for (auto& l : k) {
			initF(l, x_, y_);
			y_++;
		}
		x_++;
	}
}

template <class T>
void matrixExecute(
	matrix<T>& m,
	const std::function<void(T&, int, int)>& initF
) {
	int x_ = 0;
	for (auto& k : m) {
		int y_ = 0;
		for (auto& l : k) {
			initF(l, x_, y_);
			y_++;
		}
		x_++;
	}
}

template <class T>
void matrixExecute(
	matrix<T>& m,
	const std::function<void(T&)>& initF
) {
	int x_ = 0;
	for (auto& k : m) {
		int y_ = 0;
		for (auto& l : k) {
			initF(l);
			y_++;
		}
		x_++;
	}
}

template <class T>
const T sqr(const T& val) {
	return val * val;
}
template <typename T>
std::vector<T> concat(const std::vector<T>& a, const std::vector<T>& b) {
	std::vector<T>ret(a);
	ret.insert(ret.end(), b.begin(), b.end());
	return ret;
}
template <typename T>
inline void vecRemove(std::vector<T>& v, const typename std::vector<T>::iterator& i) {
	v.erase(i, i + 1);
}
template <typename T>
inline void vecRemove(std::vector<T>& v, int i) {
	vecRemove(v, v.begin() + i);
}

template<class T, class IndT>
void removeByInd(std::vector<T>& cont, IndT& ind) {
	cont.erase(cont.begin() + ind);
	--ind;
}

gm::Rectangle jsonRect(json& jrect);
gm::Vector jsonVector(json& vec);
gm::Vector jsonSize(json& size);
