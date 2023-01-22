// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef SEQUENCEENVIRONMENTT_H
#define SEQUENCEENVIRONMENTT_H
#include <vector>
#include <string>
#include "BCIEValue.hpp"
#include "Timer.hpp"

namespace BCIEvent_N {
	class SequenceEnvironment {
	public: 
		virtual BCIEValue getVariable(std::string) = 0;
		virtual Timer& getTimer(std::string) = 0;
		virtual BCIEValue callFunction(std::string, std::vector<BCIEValue>) = 0;
	};
}


#endif
