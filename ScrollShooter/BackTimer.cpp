#include "pch.h"
#include "BackTimer.h"
using namespace std::chrono_literals;

BackTimer::BackTimer(Duration t, Clock* clock_) :
	maxTime(t),
	timerEnd(0),
	pauseTime(0),
	isRun(false),
	clock(clock_)
{
}

BackTimer& BackTimer::operator=(Duration i) {
	setMaxTime(i);
	timerEnd = 0ms;
	return *this;
}

void BackTimer::setClock(Clock* newClock) {
	clock = newClock;
}

Clock* BackTimer::getClock() const {
	return clock;
}

BackTimer::operator Duration() const {
	auto t = timerEnd - (isRun ? clock->getDuration() : pauseTime);
	if (t > 0ms) {
		return t;
	} else {
		return 0ms;
	}
}

Duration BackTimer::getMaxTime() const {
	return maxTime;
}

bool BackTimer::update() const {
	return (operator Duration()).count();
}

bool BackTimer::finish() const {
	return !update();
}

void BackTimer::setMaxTime(Duration t) {
	maxTime = t;
}

void BackTimer::restart() {
	timerEnd = maxTime + clock->getDuration();
	isRun = true;
}

void BackTimer::restart(Duration newTime) {
	maxTime = newTime;
	restart();
}

void BackTimer::pause() {
	if (isRun) {
		isRun = false;
		pauseTime = clock->getDuration();
	}
}

void BackTimer::resume() {
	if (!isRun) {
		isRun = true;
		timerEnd += clock->getDuration() - pauseTime;
	}
}

void BackTimer::throwOff() {
	timerEnd = 0ms;
}
