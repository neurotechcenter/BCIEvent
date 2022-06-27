#include "Actor.hpp"
#include "Event.hpp"
#include "GlobalVariables.hpp"
#include "Variable.hpp"
#include <stdexcept>

using namespace BCIEvent;

    void Actor::update(){

	//Run and update blocks
	
	std::vector<Block*> toRemove;
	toRemove.reserve(_currentBlocks.size());
	for(auto i = _currentBlocks.begin(); i != _currentBlocks.end(); i++){
	    Block* currentBlock = *i;
	    Block* nextBlock = currentBlock->run(*this); //runs the block and gets a reference to the next block
	    if (nextBlock == nullptr){ //remove end blocks
		toRemove.push_back(currentBlock);
	    } else {
		_currentBlocks.erase(i);
		_currentBlocks.insert(i, nextBlock);
	    }
	}
	for (int i = 0; i < toRemove.size(); i++){ //remove end blocks
		    _currentBlocks.remove(toRemove[i]);
	}

	//Handle events
	
	for (auto &&listener : _eventListeners){
	    if (listener->isTriggered()){
		_currentBlocks.push_back(listener->getNext());
	    }
	}

    }

Actor::Actor(std::shared_ptr<GlobalVariables> globals){
    _globalVars = globals;
}

void Actor::addVariable(Variable var){
    _variables.insert(std::pair<std::string, std::unique_ptr<Variable>> (var.name(), std::unique_ptr<Variable>(&var)));
}

bool Actor::getBooleanVariable(std::string name){
   try {
	return _variables.at(name)->getAsBool();
   } catch (std::out_of_range e) {
	return _globalVars->getBoolVariable(name);
   }
}

int Actor::getIntVariable(std::string name){
    try {
	return _variables.at(name)->getAsInt();
    } catch (std::out_of_range e) {
	return _globalVars->getIntVariable(name);
    }
}

double Actor::getNumberVariable(std::string name){
    try {
	return _variables.at(name)->getAsDouble();
    } catch (std::out_of_range e) {
	return _globalVars->getNumberVariable(name);
    }
}


template<typename ReqType>
ReqType Actor::getVariable(std::string name){
    static_assert(std::is_same<ReqType, bool>::value || std::is_floating_point<ReqType>::value || std::is_integral<ReqType>::value,
	    "Template argument for getVariable must be boolean, integral, or floating point");
    try {
        if(std::is_same<ReqType, bool>::value){
	    return _variables.at(name)->getAsBool();
	}
	else if (std::is_integral<ReqType>::value){
	    return static_cast<ReqType>(_variables.at(name)->getAsInt());
	}
	else{
	    return static_cast<ReqType>(_variables.at(name)->getAsDouble());
	}
    } catch (std::out_of_range e) {
	return _globalVars->getVariable<ReqType>(name);
    }
}
template <typename SetType>
void Actor::setVariable(std::string name, SetType value){
    static_assert(std::is_same<SetType, bool>::value || std::is_same<SetType, Variable>::value || std::is_floating_point<SetType>::value || std::is_integral<SetType>::value,
	    "Template argument for setVariable must be boolean, integral, or floating point");
    try {
	_variables.at(name) = value;
    } catch (std::out_of_range e) {
	_globalVars->setVariable(name, value);
    }
}
