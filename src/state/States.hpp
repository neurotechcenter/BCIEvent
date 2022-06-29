#ifndef STATES_H
#define STATES_H
#include "State.hpp"

namespace BCIEvent{
    class BCIEventApplication;
    class States{
	std::map<std::string, std::unique_ptr<State>> _states;
	BCIEventApplication* _app;
	public:
	States(BCIEventApplication* app);
	void addState(std::string name, StateType type);
	State& getState(std::string name) const;
    };
}


#endif
