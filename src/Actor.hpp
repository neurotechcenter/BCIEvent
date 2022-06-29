#ifndef ACTOR_H
#define ACTOR_H
#include <memory>
#include <vector>
#include "EventListener.hpp"
#include "GlobalVariables.hpp"
#include "GraphDisplay.h"
#include "Variable.hpp"
#include "States.hpp"
#include <list>
#include "GraphObject.h"

namespace BCIEvent{
    class Actor : GUI::GraphObject{
	std::shared_ptr<GlobalVariables> _globalVars;
	std::vector<std::unique_ptr<EventListener>> _eventListeners; 	
	std::map<std::string, std::unique_ptr<Variable>> _variables; 
	std::shared_ptr<States> _states;

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

	Actor (std::shared_ptr<GlobalVariables> globalVars, std::shared_ptr<States> states, GUI::GraphDisplay& display);
	~Actor();
	void addVariable(Variable var);
	template<typename T>
	T getVariable(std::string name) const;

	template<typename T>
	void setVariable(std::string name, T value);

	template<typename T> requires std::integral<T> || std::convertible_to<T,bool>
	void setState(std::string name, T value);

	template<typename T> requires std::integral<T> || std::convertible_to<T,bool>
	T getState(std::string name) const;

	float positionX() const{ return GUI::GraphObject::PositionX(); }
	float positionY() const{ return GUI::GraphObject::PositionY(); }
	void setPositionX(float x) { GUI::GraphObject::SetPositionX(x); Invalidate(); }
	void setPositionY(float y) { GUI::GraphObject::SetPositionY(y); Invalidate(); }
	int zOrder() { return GUI::GraphObject::ZOrder(); }
	void setZOrder(float zOrder) { GUI::GraphObject::SetZOrder(zOrder); Invalidate(); }
	bool visible() { return GUI::GraphObject::Visible(); }
	void setVisible(bool visible) { GUI::GraphObject::SetVisible(visible); Invalidate(); }

    };
}


#endif
