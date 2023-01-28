// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
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
#include "BCIEValue.hpp"
#include "BCIEventApplication.hpp"
#include "WavePlayer.h"
#include "SequenceEnvironment.hpp"

namespace BCIEvent_N{
	class ProtoSequence;
	class Sequence;
	class Event;
	class EventListener;
    class Actor : public GUI::GraphObject, public SequenceEnvironment{
		friend class Sequence;
		
	BCIEventApplication* _app;
	std::vector<std::unique_ptr<QPixmap>> _graphics;
	int _currentGraphic = 0;

	std::vector<std::unique_ptr<EventListener>> _listeners;
	std::list<Sequence*> _sequences; //Currently running sequences, no smart pointers because they dont work for some reason
	std::map<std::string, ProtoSequence> _procedures; //procedures defined for this actor
	std::map<std::string, Event> _events;
	std::map<std::string, BCIEValue> _variables;
	std::priority_queue<VarInitializer, std::deque<VarInitializer>, VarInitCmp> _varInits;
	std::map<std::string, Timer> _timers;
	std::vector<std::unique_ptr<WavePlayer>> _sounds;
	std::map < std::string, std::function < BCIEValue(SequenceEnvironment&, std::vector<BCIEValue>)>> _functions ;
	
	//Actor's text box
	RGBColor _textColor;
	std::string text;
	TextField _textField;
	Timer _textTimer;
	double _textTimeSeconds;
	bool _textIsTimed;



	const GenericSignal* _currentSignal;

	Event* _clickEvent;


	public:

		enum DisplayMode {Image, Text};

	void initialize();
	/**
	 * Main update function: called once every cycle of the main loop.
	 * Runs blocks and handles events.
	 */
	void update( const GenericSignal& input );

	Actor(BCIEventApplication* app);
	~Actor();
	Actor& addVariable(std::string name);
	Actor& addVariable(std::string name, BCIEValue value);
	Actor& addVariable(std::string name, std::function<BCIEValue(SequenceEnvironment&)> value, int initPriority);
	Actor& addGraphic(std::string filename, bool transparent);
	Actor& addSound(std::string filename);
	Actor& addEventListener(std::unique_ptr<EventListener>);
	Actor& addEventListener(std::string, std::unique_ptr<EventListener>);
	Actor& addProcedure(std::string name, ProtoSequence sequence);
	Actor& addEvent(std::string name);
	Actor& addFunction(std::string name, std::function<BCIEValue(SequenceEnvironment&, std::vector<BCIEValue>)>);
	Actor& addTimer(std::string name);
	Actor& self() { return *this; }



	void callEvent(std::string);

	std::unique_ptr<Sequence> getProcedure(std::string name, std::vector<BCIEValue> parameters);

	int randInt(int lowerBound, int upperBound);

	BCIEValue callFunction(std::string name, std::vector<BCIEValue> parameters);

	Timer& getTimer(std::string name);

	/**
	 * Returns the value of the signal.
	 * This can only ever be called from inside the update() method,
	 * and will return zero otherwise, as _currentSignal is always null outside of update()
	 * It will also throw an exception if the element or channel is out of range.
	 */
	double getSignal(size_t channel, size_t element);
	

	float positionX() const{ return GUI::GraphObject::PositionX(); }
	float positionY() const{ return GUI::GraphObject::PositionY(); }
	void setPositionX(float x) { GUI::GraphObject::SetPositionX(x); Change(); }
	void setPositionY(float y) { GUI::GraphObject::SetPositionY(y); Change(); }
	double positionX() { return GUI::GraphObject::PositionX(); }
	double positionY() { return GUI::GraphObject::PositionY(); }
	int zOrder() { return GUI::GraphObject::ZOrder(); }
	void setZOrder(float zOrder) { GUI::GraphObject::SetZOrder(zOrder); Change(); }
	bool visible() { return GUI::GraphObject::Visible(); }
	void setVisible(bool visible) { GUI::GraphObject::SetVisible(visible); Change(); }
	void playSound(int sound);
	void changeGraphic(int graphic);

	void setBackgroundColor(int r, int g, int b) { _app->setBackgroundColor(r, g, b); }
	
	//Actor's text box controls
	void setTextColor(int r, int g, int b);
	void setTextVisible(bool isVisible) { _textField.SetVisible(isVisible); }
	void say(std::string text) { setTextVisible(true); _text = text; _textIsTimed = false; }
	void sayFor(std::string text, double timeSeconds) { setTextVisible(true); _text = text; _textTimeSeconds = timeSeconds; _textTimer.reset(); _textTimer.start(); _textIsTimed = true; }

	/**
	 * This currently returns true when a point within the bounding box is clicked.
	 * I will change this when graphics are implemented
	 */
	bool OnClick(const GUI::Point&) override;
	void OnPaint(const GUI::DrawContext&) override;
	        

    BCIEValue getVariable(std::string name);

	void setVariable(std::string name, BCIEValue value);
	
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

