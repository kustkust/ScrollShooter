#pragma once
#include "MyClock.h"

class BackTimer {
public:
	MyClock* clock;
	duration maxTime;
	duration timerEnd;
	duration pauseTime;
	bool isRun;

	BackTimer(duration t = duration(1), MyClock* clock = &MyClock::clock);
	BackTimer(const BackTimer&) = default;
	BackTimer&operator=(duration i);
	BackTimer&operator=(const BackTimer&) = default;

	void setClock(MyClock*newClock);
	MyClock*getClock()const;

	operator duration() const;
	duration getMaxTime()const;
	void setMaxTime(duration t);

	bool update() const;
	void restart();
	void restart(duration newTime);
	void pause();
	void resume();

	//сбрасывает время
	void throwOff();

	~BackTimer() = default;
};