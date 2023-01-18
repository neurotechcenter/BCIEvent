#ifndef TIMER_H
#define TIMER_H
#include <chrono>

namespace BCIEvent {
	class Timer {
		bool running;
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
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
				return ((double)std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::high_resolution_clock::now() - startTime)).count()) / 1000.0;
			}
			else {
				return ((double)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) / 1000.0;
			}
		}
	};
}

#endif
