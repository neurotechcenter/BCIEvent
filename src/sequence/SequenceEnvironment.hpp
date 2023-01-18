#ifndef SEQUENCEENVIRONMENTT_H
#define SEQUENCEENVIRONMENTT_H
#include <vector>
#include <string>
#include "BCIEValue.hpp"
#include "Timer.hpp"

namespace BCIEvent {
	class SequenceEnvironment {
	public: 
		virtual BCIEValue getVariable(std::string) = 0;
		virtual Timer& getTimer(std::string) = 0;
		virtual BCIEValue callFunc(std::string, std::vector<BCIEValue>) = 0;
	};
}


#endif