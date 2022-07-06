#include "States.hpp"
#include "BCIState.hpp"
#include <stdexcept>

using namespace BCIEvent;

States::States(BCIEventApplication* app){
    _app = app;
}

void States::addState(std::string name, BCIState::StateType type){
    _states.insert(std::pair<std::string, std::unique_ptr<BCIState>>(name, std::make_unique<BCIState>(_app, type, name)));
}

BCIState& States::getState(std::string name) const{
    try{
	return *_states.at(name);
    } catch (std::out_of_range e) {
	throw std::out_of_range("Could not find state " + name);
    }
};


std::vector<const BCIState*> States::getStates(){
    std::vector<const BCIState*> ret;
    ret.reserve(_states.size());
    for ( auto const& [name, state] : _states ){
	ret.push_back(&*state);
    }
    return std::move(ret);
}
