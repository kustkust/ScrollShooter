#include "pch.h"
#include "Timer.h"

Timer::Timer(Clock* clock) : 
	clock(clock), lastCheck(clock->getDuration()), elasped{}, isRun(true), pauseTime(0) {
}

duration Timer::sinceLast() {
	auto tmp = clock->getDuration();
	elasped = tmp - lastCheck;
	lastCheck = tmp;
	return elasped;
}

void Timer::restart() {
	lastCheck = clock->getDuration();
}

void Timer::pause() {
	isRun = false;
	pauseTime = clock->getDuration();
}

void Timer::resume() {
	isRun = true;
	lastCheck += clock->getDuration() - pauseTime;
}
