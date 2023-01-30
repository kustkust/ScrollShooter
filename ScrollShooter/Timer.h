#pragma once
#include "MyClock.h"

class Timer {
	MyClock* clock;
	duration lastCheck;
	duration pauseTime;
	duration elasped;
	bool isRun;
public:
	Timer(MyClock* clock = &MyClock::clock);
	duration sinceLast();
	void restart();
	void pause();
	void resume();
};

