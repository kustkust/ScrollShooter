#pragma once
using namespace std::chrono_literals;
using time_point = std::chrono::steady_clock::time_point;
using duration = std::chrono::milliseconds;

class Clock {
	time_point lastTime;
	duration savedTime;
	bool isRun;
	template<class T>
	duration to_duration(T);
public:
	Clock();
	void update();
	void restart();
	void stop();
	void start();
	bool switchClock();
	duration getDuration();
	int64_t getTime();
	static Clock clock;
};

template<class T>
inline duration Clock::to_duration(T timePoint) {
	return std::chrono::duration_cast<duration>(timePoint);
}
