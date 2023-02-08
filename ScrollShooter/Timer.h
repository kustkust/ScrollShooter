#pragma once
#include "Clock.h"

class Timer {
	Clock* clock;
	duration lastCheck;
	duration pauseTime;
	duration elasped;
	bool isRun;
public:
	Timer(Clock* clock = &Clock::clock);
	duration sinceLast();
	void restart();
	void pause();
	void resume();
};

