#ifndef TIMER_H
#define TIMER_H
#include <chrono>

namespace BCIEvent {
    typedef TimePoint std::chrono::time_point<std::chrono::high_resolution_clock>;
    class Timer {
	bool running;
	TimePoint startTime;
	TimePoint endTime;
	public: 				
	Timer() {
	    running = false;
	    startTime = std::chrono::high_resolution_clock::now();
	    endTime = std::chrono::high_resolution_clock::now();
	}
	void start() {
	    running = true;
	    startTime = std::chrono::high_resolution_clock::now();
	    endTime = std::chrono::high_resolution_clock::now();
	}
	void stop() {
	    running = false;
	    endTime = std::chrono::high_resolution_clock::now();
	}
	void reset() {
	    startTime = std::chrono::high_resolution_clock::now();
	    endTime = std::chrono::high_resolution_clock::now();
	}
	double time() {
	    if (running) {
		return ( (double) std::chrono::milliseconds((std::chrono::high_resolution_clock::now() - startTime)).count()) / 1000d;	
	    } else {
		return ((double) std::chrono::milliseconds(endTime - startTime).count()) / 1000d;
	    }
	}
    }
}

#endif
