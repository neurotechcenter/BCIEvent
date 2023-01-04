#ifndef ACTOR_H
#define ACTOR_H
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <QPixmap>
#include "GUI.h"
#include "GenericSignal.h"
#include "GraphDisplay.h"
#include "GraphObject.h"
#include "BCIEventApplication.hpp"
#include "GlobalVariables.hpp"
#include "States.hpp"
#include "BCIEVariable.hpp"

namespace BCIEvent{
	class ProtoSequence;
	class Sequence;
	class Event;
	class EventListener;
    class Actor : public GUI::GraphObject{
		friend class Sequence;
		
	BCIEventApplication* _app;
	std::map<std::string, std::unique_ptr<BCIEVariable>> _variables; 
	std::vector<std::unique_ptr<QPixmap>> _graphics;
	int _currentGraphic = 0;

	std::vector<std::unique_ptr<EventListener>> _listeners;
	std::list<Sequence*> _sequences; //Currently running sequences, no smart pointers because they dont work for some reason
	std::map<std::string, ProtoSequence> _procedures; //procedures defined for this actor
	std::map<std::string, Event> _events;
	std::map<std::string, BCIEVariable> _variables;


	const GenericSignal* _currentSignal;

	std::shared_ptr<Event> _clickEvent;

	public:

	/**
	 * Main update function: called once every cycle of the main loop.
	 * Runs blocks and handles events.
	 */
	void update( const GenericSignal& input );

	Actor(BCIEventApplication* app);
	~Actor();
	Actor& addVariable(std::string name);
	Actor& addVariable(std::string name, BCIEValue value);
	Actor& addGraphic(std::string filename, bool transparent);
	Actor& addEventListener(std::unique_ptr<EventListener>);
	Actor& addEventListener(std::string, std::unique_ptr<EventListener>);
	Actor& addProcedure(std::string name, ProtoSequence sequence);
	Actor& addEvent(std::string name);



	void callEvent(std::string);

	Sequence* getProcedure(std::string name, std::vector<BCIEValue> parameters);

	int randInt(int lowerBound, int upperBound);

	void addFunction(std::string name, std::function<(Sequence&, std::vector<BCIEValue>), BCIEValue>);
	BCIEValue callFunction(std::string name, Sequence& callingSequence, std::vector<BCIEValue> parameters);


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
	double positionX() { return GUI::GraphObject::PositionX(); }
	double positionY() { return GUI::GraphObject::PositionY(); }
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
	        

    BCIEValue getVariable(std::string name) const{
        try {
			return _variables.at(name);
        } catch (std::out_of_range e) {
        	return _app->getVariable(name);
        }
    }

	template <typename SetType>
	void setVariable(std::string name, SetType value){
	    static_assert(std::is_same<SetType, bool>::value || std::is_same<SetType, BCIEVariable>::value || std::is_floating_point<SetType>::value || std::is_integral<SetType>::value,
		    "Template argument for setVariable must be Variable, boolean, integral, or floating point");
	    try {
		*_variables.at(name) = value;
	    } catch (std::out_of_range e) {
		_app->setVar(name, value);
	    }
	}
	
	template <typename T> requires std::integral<T> || std::convertible_to<T, bool>
	void setState(std::string name, T value){
	    _app->getBCIState(name).set(value);
	}

	template <typename T> requires std::integral<T> || std::convertible_to<T, bool>
	T getState(std::string name) const{
	    return static_cast<T>(_app->getBCIState(name).get());
	}
    };
}


#endif
