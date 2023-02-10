#pragma once
#include "Clock.h"

class BackTimer {
public:
	Clock* clock;
	Duration maxTime;
	Duration timerEnd;
	Duration pauseTime;
	bool isRun;

	BackTimer(Duration t = Duration(1), Clock* clock = &Clock::clock);
	BackTimer(const BackTimer&) = default;
	BackTimer&operator=(Duration i);
	BackTimer&operator=(const BackTimer&) = default;

	void setClock(Clock*newClock);
	Clock*getClock()const;

	operator Duration() const;
	Duration getMaxTime()const;
	void setMaxTime(Duration t);

	bool update() const;
	bool finish() const;
	void restart();
	void restart(Duration newTime);
	void pause();
	void resume();

	//сбрасывает время
	void throwOff();

	~BackTimer() = default;
};
