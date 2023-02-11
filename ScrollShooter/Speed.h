#pragma once
#include "Utility.h"
#include "Clock.h"

/*
* Represent speed in unit per second
*/
class Speed {
	gm::real speed = 0.;
public:
	DEFAULT_CLASS(Speed);
	Speed(gm::real speed) :speed(speed) {}
	Speed(int speed) :speed(static_cast<gm::real>(speed)) {}

	template<class T>
	gm::real operator*(std::chrono::duration<T> dur) const {
		return (speed * std::chrono::duration_cast<Duration>(dur).count()) / 1000;
	}

	Speed operator*(gm::real a) const {
		return Speed(speed * a);
	}
	
	Speed& operator*=(gm::real a) {
		speed *= a;
		return *this;
	}
	
	Speed operator/(gm::real a) const {
		return Speed(speed / a);
	}
	
	Speed& operator/=(gm::real a) {
		speed /= a;
		return *this;
	}
	
	Speed operator+(Speed s) const {
		return Speed(speed + s.speed);
	}
	
	Speed& operator+=(Speed s) {
		speed += s.speed;
		return *this;
	}
	
	Speed operator-(Speed s) const {
		return Speed(speed - s.speed);
	}
	
	Speed& operator-=(Speed s) {
		speed -= s.speed;
		return *this;
	}

	Speed operator-() const {
		return Speed(-speed);
	}
};

Speed operator""ps(long double s) {
	return Speed(static_cast<gm::real>(s));
}

Speed operator""ps(unsigned long long int s) {
	return Speed(static_cast<gm::real>(s));
}