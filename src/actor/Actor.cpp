// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "Actor.hpp"
#include "Event.hpp"
#include "GUI.h"
#include "GraphDisplay.h"
#include "GraphObject.h"
#include "EventListener.hpp"
#include "StartEvent.hpp"
#include <stdexcept>
#include <type_traits>
#include <QBitmap>
#include <QPainter>


using namespace BCIEvent_N;

    void Actor::update( const GenericSignal& signal ){

	//Set the signal for this cycle.
	_currentSignal = &signal;

    //Add sequences of triggered events;
    for (auto& listener : _listeners) {
        if (listener->timesTriggered() > 0) {
            auto seq = listener->getSequence();
            seq->setActor(this);
            _sequences.push_back(seq.release());
        }
    }

	//Run and update blocks
    for (int i = 0; i < _sequences.size(); i++) {
        if (_sequences.front()->update()) { //If sequence is still running, append it to the back of the list
            _sequences.push_back(_sequences.front());
            _sequences.pop_front();
        }
        else { //else delete the finished sequence
            delete _sequences.front();
            _sequences.pop_front();
        }
           //This will either remove and delete a completed sequence or move the next sequence to the end of the list 
        //After these operations, the list of sequences will be the same except without any completed sequences, which will have been deleted.
	}
	_currentSignal = nullptr; //the signal should only ever be accessed during the update stage.
    }

void Actor::initialize() {
    while (!_varInits.empty()) {
        VarInitializer vi = _varInits.top();
        _variables.insert(std::make_pair(std::get<0>(vi), std::get<1>(vi)(*this)));
        _varInits.pop();
    }
}

Actor::Actor(BCIEventApplication* app) :
	GUI::GraphObject(app->getDisplay(), 0)
{
	_app = app;
    SetAlignment(GUI::Alignment::Center);
    SetScalingMode(GUI::ScalingMode::AdjustBoth);
    Show();
    _events.insert(std::make_pair("click", Event()));
    _clickEvent = &_events.at("click");
}

Actor::~Actor(){
    DestructorEntered();
    for (auto s : _sequences) {
        delete s;
    }
}

Actor& Actor::addVariable(std::string name){
    _variables.insert(std::make_pair(name, std::nullopt));
    return *this;
}

Actor& Actor::addVariable(std::string name, BCIEValue value) {
    _variables.insert(std::make_pair(name, value));
    return *this;
}

Actor& Actor::addVariable(std::string name, std::function<BCIEValue(SequenceEnvironment&)> value, int priority) {
    _varInits.push(std::make_tuple(name, value, priority));
    return *this;
}

Actor& Actor::addEventListener(std::string name, std::unique_ptr<EventListener> listener){
    try {
        _events.at(name).addListener(listener.get()); //free pointer is given to event listener,
    }
    catch (std::out_of_range) {
        _app->subscribeEvent(name, listener.get());
    }
    _listeners.push_back(std::move(listener)); //ownership given to actor
    return *this;
}

Actor& Actor::addEventListener(std::unique_ptr<EventListener> listener) {
    StartEvent::getInstance()->addListener(listener.get());
    _listeners.push_back(std::move(listener));
    return *this;
}

Actor& Actor::addGraphic(std::string filename, bool transparent){
    filename = "../src/custom/BCIEvent/assets/graphics/" + filename;
    std::unique_ptr<QPixmap> pixmap = std::make_unique<QPixmap>(QString(filename.c_str()));
    if (pixmap->isNull()){
	throw std::invalid_argument("Could not load file " + filename);
    }
    //Qt is weird, will try later
    
    if (transparent && !pixmap->hasAlphaChannel()){ //tries to make image transparent
	pixmap->setMask(pixmap->createHeuristicMask());
    }
    
    _graphics.push_back(std::move(pixmap));
    return *this;
}

Actor& Actor::addSound(std::string filename) {
    std::string filepath = "../src/custom/BCIEvent/assets/sounds/" + filename;
    auto wp = new WavePlayer();
    wp->SetFile(filepath);
    _sounds.push_back(std::unique_ptr<WavePlayer>(wp));
    return *this;
}

Actor& Actor::addTimer(std::string name) {
    _timers.insert(std::make_pair(name, Timer()));
    return *this;
}

std::unique_ptr<Sequence> Actor::getProcedure(std::string name, std::vector<BCIEValue> parameters) {
    return _procedures.at(name).genSequence(parameters);
}

BCIEValue Actor::getVariable(std::string name) {
    try {
        return _variables.at(name);
    }
    catch (std::out_of_range) {
        return _app->getVariable(name);
    }
}

void Actor::callEvent(std::string name) {
    try {
        _events.at(name).trigger();
    }
    catch (std::out_of_range) {
        _app->callEvent(name);
    }
}


int Actor::randInt(int lower, int upper) {
	return _app->randInt(lower, upper);
}

Timer& Actor::getTimer(std::string name) {
    try {
        return _timers.at(name);
    }
    catch (std::out_of_range) {
        return _app->getTimer(name);
    }
}


double Actor::getSignal(size_t channel, size_t element){
	    if (_currentSignal){
		if (channel >= _currentSignal->Channels()){
		    throw std::out_of_range("Requested channel index " + std::to_string(channel) + " is greater than the number of channels in the signal (" + std::to_string(_currentSignal->Channels()) + ")");
		}
		if (element >= _currentSignal->Elements()){
		    throw std::out_of_range("Requested element index " + std::to_string(element) + " is greater than the number of elements in the signal (" + std::to_string(_currentSignal->Elements()) + ")");
		}
		return _currentSignal->Value(channel, element);
	    }
	    return 0;
}

bool Actor::OnClick(const GUI::Point& clickPoint){
    /**
     * Returns true whenever the bounding box is clicked.
     * Will change this when graphics are implemented.
     */
    _clickEvent->trigger();
    return true;
}

void Actor::OnPaint(const GUI::DrawContext& context){
    bciout << "PAINTING";
    QPixmap *imgBuffer = &*_graphics.at(_currentGraphic);
    bciout << "2";
    int width = ::Floor(context.rect.Width()), height = ::Floor(context.rect.Height());
    bciout << "3";
    if (width == imgBuffer->width() && height == imgBuffer->height()){
    bciout << "4";
	context.handle.dc->drawPixmap(::Floor(context.rect.left), ::Floor(context.rect.top), *imgBuffer);
    } else {
    	bciout << "5";
	context.handle.dc->drawPixmap(::Floor(context.rect.left), ::Floor(context.rect.top), width, height, *imgBuffer);
	bciout << "6";
    }
}


Actor& Actor::addFunction(std::string name, std::function<BCIEValue (SequenceEnvironment&, std::vector<BCIEValue>)> fn) {
    _functions.insert(std::make_pair(name, fn));
    return *this;
}

BCIEValue Actor::callFunction(std::string name, std::vector<BCIEValue> params) {
    try {
        return _functions.at(name)(*this, params);
    }
    catch (const std::out_of_range&) {
        return _app->callFunction(name, params);
    }
}

void Actor::playSound(int snd) {
    _sounds.at(snd)->Play();
}

void Actor::setVariable(std::string name, BCIEValue value) {
    try {
        _variables.at(name) = value;
    }
    catch (std::out_of_range) {
        _app->setVariable(name, value);
    }

}

void Actor::changeGraphic(int graphic) {
    _currentGraphic = graphic;
}

