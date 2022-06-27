#ifndef ACTOR_H
#define ACTOR_H
#include <memory>
#include <vector>
#include "EventListener.hpp"
#include "GlobalVariables.hpp"
#include "Variable.hpp"
#include <list>

namespace BCIEvent{
    class Actor{
	std::shared_ptr<GlobalVariables> _globalVars;
	std::vector<std::unique_ptr<EventListener>> _eventListeners; 	
	std::map<std::string, std::unique_ptr<Variable>> _variables; 

	/**
	 * List of currently executing blocks.
	 */
	std::list<Block*> _currentBlocks;
	public:

	/**
	 * Main update function: called once every cycle of the main loop.
	 * Runs blocks and handles events.
	 */
	void update();

	Actor (std::shared_ptr<GlobalVariables> globals);
	void addVariable(Variable var);
	template<typename T>
	T getVariable(std::string name);
	template<typename T>
	void setVariable(std::string name, T value);
    };
}


#endif
