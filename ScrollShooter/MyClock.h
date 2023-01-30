#pragma once
using namespace std::chrono_literals;
using time_point = std::chrono::steady_clock::time_point;
using duration = std::chrono::milliseconds;

class MyClock {
	time_point lastTime;
	duration savedTime;
	bool isRun;
	template<class T>
	duration to_duration(T);
public:
	static MyClock*defaultClock;
	MyClock();
	void update();
	void restart();
	void stop();
	void start();
	bool switchTimer();
	duration getDuration();
	int64_t getTime();
	static MyClock clock;
};

template<class T>
inline duration MyClock::to_duration(T timePoint) {
	return std::chrono::duration_cast<duration>(timePoint);
}
