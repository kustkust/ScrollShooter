#include "pch.h"
#include "MyClock.h"
using namespace std::chrono_literals;

MyClock::MyClock() :
	isRun(false),
	lastTime(std::chrono::steady_clock::now()),
	savedTime(0ms)
{}

void MyClock::update() {
	if (isRun) {
		auto t = std::chrono::steady_clock::now();
		savedTime += to_duration(t - lastTime);
		lastTime = t;
	}
}

void MyClock::restart() {
	savedTime = 0ms;
	lastTime = std::chrono::steady_clock::now();
}

void MyClock::stop() {
	if (isRun) {
		update();
		isRun = false;
	}
}

void MyClock::start() {
	if (!isRun) {
		lastTime = std::chrono::steady_clock::now();
		isRun = true;
	}
}
bool MyClock::switchTimer() {
	if (isRun) {
		stop();
		return false;
	}
	else {
		start();
		return true;
	}
}

duration MyClock::getDuration() {
	update();
	return savedTime;
}

int64_t MyClock::getTime() {
	return getDuration().count();
}

MyClock MyClock::clock = MyClock();
