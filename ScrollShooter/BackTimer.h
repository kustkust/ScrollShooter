#pragma once
#include "Clock.h"

class BackTimer {
public:
	Clock* clock;
	duration maxTime;
	duration timerEnd;
	duration pauseTime;
	bool isRun;

	BackTimer(duration t = duration(1), Clock* clock = &Clock::clock);
	BackTimer(const BackTimer&) = default;
	BackTimer&operator=(duration i);
	BackTimer&operator=(const BackTimer&) = default;

	void setClock(Clock*newClock);
	Clock*getClock()const;

	operator duration() const;
	duration getMaxTime()const;
	void setMaxTime(duration t);

	bool update() const;
	bool finish() const;
	void restart();
	void restart(duration newTime);
	void pause();
	void resume();

	//сбрасывает время
	void throwOff();

	~BackTimer() = default;
};
