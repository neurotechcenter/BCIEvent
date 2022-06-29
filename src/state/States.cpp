#include "States.hpp"
#include <stdexcept>

using namespace BCIEvent;

States::States(BCIEventApplication* app){
    _app = app;
}

void States::addState(std::string name, StateType type){
    _states.insert(std::make_unique<State>(_app, type, name));
}

State& States::getState(std::string name) const{
    try{
	return _states.at(name);
    } catch (std::out_of_range e) {
	throw std::out_of_range("Could not find state " + name);
    }
};
