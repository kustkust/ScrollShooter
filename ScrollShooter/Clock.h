#pragma once
using namespace std::chrono_literals;
using time_point = std::chrono::steady_clock::time_point;
using Duration = std::chrono::milliseconds;

class Clock {
	time_point lastTime;
	Duration savedTime;
	bool isRun;
	template<class T>
	Duration to_duration(T);
public:
	Clock();
	void update();
	void restart();
	void stop();
	void start();
	bool switchClock();
	Duration getDuration();
	int64_t getTime();
	static Clock clock;
};

template<class T>
inline Duration Clock::to_duration(T timePoint) {
	return std::chrono::duration_cast<Duration>(timePoint);
}
