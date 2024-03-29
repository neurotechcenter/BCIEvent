// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef BCIEVENT_TIMER_H
#define BCIEVENT_TIMER_H
#include <chrono>

namespace BCIEvent_N {
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

