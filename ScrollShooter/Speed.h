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

	gm::real operator*(std::chrono::milliseconds dur) const {
		return speed * dur.count() / 1000;
	}
	gm::real operator*(std::chrono::seconds dur) const {
		return speed * dur.count();
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

Speed operator""_ps(long double s) {
	return Speed(static_cast<gm::real>(s));
}

Speed operator""_ps(unsigned long long int s) {
	return Speed(static_cast<gm::real>(s));
}