#ifndef ACTOR_H
#define ACTOR_H
#include <memory>
#include <string>
#include <vector>
#include "EventListener.hpp"
#include "GUI.h"
#include "GlobalVariables.hpp"
#include "GraphDisplay.h"
#include "Variable.hpp"
#include "States.hpp"
#include <list>
#include "GraphObject.h"
#include <QPixmap>

namespace BCIEvent{
    class Actor : GUI::GraphObject{
	std::shared_ptr<GlobalVariables> _globalVars;
	std::vector<std::unique_ptr<EventListener>> _eventListeners; 	
	std::map<std::string, std::unique_ptr<Variable>> _variables; 
	std::shared_ptr<States> _states;
	std::vector<std::unique_ptr<QPixmap>> _graphics;
	int _currentGraphic = 0;

	/**
	 * List of currently executing blocks.
	 */
	std::list<Block*> _currentBlocks;

	const GenericSignal* _currentSignal;

	std::shared_ptr<Event> _clickEvent;

	public:

	/**
	 * Main update function: called once every cycle of the main loop.
	 * Runs blocks and handles events.
	 */
	void update( GenericSignal& input );

	Actor (std::shared_ptr<GlobalVariables> globalVars, std::shared_ptr<States> states, GUI::GraphDisplay& display);
	~Actor();
	void addVariable(Variable var);
	void addGraphic(std::string filename, bool transparent);

	template<typename T>
	T getVariable(std::string name) const;

	template<typename T>
	void setVariable(std::string name, T value);

	template<typename T> requires std::integral<T> || std::convertible_to<T,bool>
	void setState(std::string name, T value);

	template<typename T> requires std::integral<T> || std::convertible_to<T,bool>
	T getState(std::string name) const;

	/**
	 * The event which is triggered whenever this actor is clicked.
	 * Its possible to trigger the event from outside of this actor.
	 * Don't do that.
	 */
	std::shared_ptr<Event> clickEvent();


	/**
	 * Returns the value of the signal.
	 * This can only ever be called from inside the update() method,
	 * and will return zero otherwise, as _currentSignal is always null outside of update()
	 * It will also throw an exception if the element or channel is out of range.
	 */
	double getSignal(size_t channel, size_t element);
	

	float positionX() const{ return GUI::GraphObject::PositionX(); }
	float positionY() const{ return GUI::GraphObject::PositionY(); }
	void setPositionX(float x) { GUI::GraphObject::SetPositionX(x); Invalidate(); }
	void setPositionY(float y) { GUI::GraphObject::SetPositionY(y); Invalidate(); }
	int zOrder() { return GUI::GraphObject::ZOrder(); }
	void setZOrder(float zOrder) { GUI::GraphObject::SetZOrder(zOrder); Invalidate(); }
	bool visible() { return GUI::GraphObject::Visible(); }
	void setVisible(bool visible) { GUI::GraphObject::SetVisible(visible); Invalidate(); }
	/**
	 * This currently returns true when a point within the bounding box is clicked.
	 * I will change this when graphics are implemented
	 */
	bool OnClick(const GUI::Point&) override;
	void OnPaint(const GUI::DrawContext&) override;
    };
}


#endif
