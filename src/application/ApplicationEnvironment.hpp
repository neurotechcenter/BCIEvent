#ifndef APPLICATIONENVIRONMENT_H
#define APPLICATIONENVIRONMENT_H
#include <string>
#include "SequenceEnvironment.hpp"
#include "BCIEventApplication.hpp"

namespace BCIEvent {
	class ApplicationEnvironment : public SequenceEnvironment {
		ApplicationEnvironment* _app;
	public: 
			ApplicationEnvironment(BCIEventApplication* app) {
				_app = app
			}

			BCIEValue getVariable(std::string name) {
				return _app->getVariable(name);
			}

			Timer& getTimer(std::string name) {
				return _app->getTimer(name);
			}

			BCIEValue callFunc(std::string name, std::vector<BCIEValue> args) {
				return _app->callFunc(name, args);
			}


	};
}

#endif