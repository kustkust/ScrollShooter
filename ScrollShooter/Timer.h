#pragma once
#include "Clock.h"

class Timer {
	Clock* clock;
	Duration lastCheck;
	Duration pauseTime;
	Duration elasped;
	bool isRun;
public:
	Timer(Clock* clock = &Clock::clock);
	Duration sinceLast();
	void restart();
	void pause();
	void resume();
};

