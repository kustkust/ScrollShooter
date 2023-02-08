#include "pch.h"
#include "Clock.h"
using namespace std::chrono_literals;

Clock::Clock() :
	isRun(false),
	lastTime(std::chrono::steady_clock::now()),
	savedTime(0ms)
{}

void Clock::update() {
	if (isRun) {
		auto t = std::chrono::steady_clock::now();
		savedTime += to_duration(t - lastTime);
		lastTime = t;
	}
}

void Clock::restart() {
	savedTime = 0ms;
	lastTime = std::chrono::steady_clock::now();
}

void Clock::stop() {
	if (isRun) {
		update();
		isRun = false;
	}
}

void Clock::start() {
	if (!isRun) {
		lastTime = std::chrono::steady_clock::now();
		isRun = true;
	}
}
bool Clock::switchClock() {
	if (isRun) {
		stop();
		return false;
	}
	else {
		start();
		return true;
	}
}

duration Clock::getDuration() {
	update();
	return savedTime;
}

int64_t Clock::getTime() {
	return getDuration().count();
}

Clock Clock::clock = Clock();
