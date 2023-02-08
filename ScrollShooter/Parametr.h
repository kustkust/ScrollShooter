#pragma once
#include <functional>

template<class T>
class Parametr {
	T initParamter;
	T curParametr;
	int initCost;
	int curCost;
	std::function<void(T&)> upgrade;
	std::function<void(int&)> incraceCost;
public:
	Parametr() {}
	Parametr(
		const T& parametr,
		int cost,
		const std::function<void(T&)>& upgrade = [](T&) {},
		const std::function<void(int&)>& incraceCost = [](int&) {}
	) :
		initParamter(parametr), curParametr(parametr), initCost(cost), curCost(cost), upgrade(upgrade), incraceCost(incraceCost) {

	}
	Parametr& operator=(Parametr&& other) noexcept {
		std::swap(initParamter, other.initParamter);
		std::swap(curParametr, other.curParametr);
		std::swap(initCost, other.initCost);
		std::swap(curCost, other.curCost);
		std::swap(upgrade, other.upgrade);
		std::swap(incraceCost, other.incraceCost);
		return *this;
	}
	Parametr& operator=(const T& other) noexcept {
		curParametr = other;
		return *this;
	}
	operator T() const {
		return curParametr;
	}
	virtual bool tryUpgrade(int& score) {
		if (score >= curCost) {
			upgrade(curParametr);
			incraceCost(curCost);
			return true;
		}
		return false;
	}
	virtual void reset() {
		curParametr = initParamter;
		curCost = initCost;
	}
	virtual void reset(const T& newParametr) {
		curParametr = newParametr;
		initParamter = newParametr;
		curCost = initCost;
	}

	T& get() {
		return curParametr;
	}

	const T& get() const {
		return curParametr;
	}

	T& operator*() {
		return curParametr;
	}

	const T& operator*() const {
		return curParametr;
	}

	T* operator->() {
		return &curParametr;
	}
	const T* operator->() const {
		return &curParametr;
	}

	int getCost() {
		return curCost;
	}

	virtual ~Parametr() {

	}
};

