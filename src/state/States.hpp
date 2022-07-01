#ifndef STATES_H
#define STATES_H
#include "BCIState.hpp"
#include <map>
#include <memory>
#include <vector>

namespace BCIEvent{
    class BCIEventApplication;
    class States{
	std::map<std::string, std::unique_ptr<BCIState>> _states;
	BCIEventApplication* _app;
	public:
	States(BCIEventApplication* app);
	void addState(std::string name, BCIState::StateType type);
	BCIState& getState(std::string name) const;
	std::vector<const BCIState*> getStates();
    };
}


#endif
