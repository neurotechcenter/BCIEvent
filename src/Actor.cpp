#include "Actor.hpp"
#include "Event.hpp"
#include "GUI.h"
#include "GlobalVariables.hpp"
#include "GraphDisplay.h"
#include "GraphObject.h"
#include "Variable.hpp"
#include "NumberVariable.hpp"
#include <stdexcept>
#include <type_traits>

using namespace BCIEvent;

    void Actor::update( GenericSignal& signal ){

	//Set the signal for this cycle.
	_currentSignal = &signal;
	
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
	_currentSignal = nullptr; //the signal should only ever be accessed during the update stage.
    }

Actor::Actor(std::shared_ptr<GlobalVariables> globalVars, std::shared_ptr<States> states, GUI::GraphDisplay& display) : GUI::GraphObject(display, 0){
    _globalVars = globalVars;
    _states = states;
    SetAlignment(GUI::Alignment::Center);
    SetScalingMode(GUI::ScalingMode::AdjustBoth);

}

Actor::~Actor(){
    DestructorEntered();
}

void Actor::addVariable(Variable var){
    _variables.insert(var.name(), std::unique_ptr<Variable>(&var));
}

void Actor::addGraphic(std::string filename, bool transparent){
    std::unique_ptr<QPixmap> pixmap = std::make_unique<QPixmap>(filename);
    if (pixmap->isNull()){
	throw std::invalid_argument("Could not load file " + filename);
    }
    if (transparent && !pixmap->hasAlphaChannel){ //tries to make image transparent
	pixmap->setMask(pixmap.createHeuristicMask());
    }
    _graphics.push_back(std::move(pixmap));
}

template<typename ReqType>
ReqType Actor::getVariable(std::string name) const{
    static_assert(std::is_convertible<ReqType, bool>::value || std::is_floating_point<ReqType>::value || std::is_integral<ReqType>::value,
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
	    "Template argument for setVariable must be Variable, boolean, integral, or floating point");
    try {
	_variables.at(name) = value;
    } catch (std::out_of_range e) {
	_globalVars->setVariable(name, value);
    }
}

template <typename T> requires std::integral<T> || std::convertible_to<T, bool>
void Actor::setState(std::string name, T value){
    _states->getState(name).set(value);
}


template <typename T> requires std::integral<T> || std::convertible_to<T, bool>
T Actor::getState(std::string name) const{
    return static_cast<T>(_states->at(name).get());
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

std::shared_ptr<Event> Actor::clickEvent(){
    auto ret = _clickEvent;
    return ret;
}

bool Actor::OnClick(const GUI::Point& clickPoint){
    /**
     * Returns true whenever the bounding box ic clicked.
     * Will change this when graphics are implemented.
     */
    _clickEvent->trigger();
    return true;
}

void Actor::OnPaint(const GUI::DrawContext& context){
    QPixmap *imgBuffer = &*_graphics.get(_currentGraphic);
    int width = ::Floor(context.rect.Width()), height = ::Floor(context.rect.Height());
    if (width == imgBuffer->width() && height == imgBuffer->height())
	context.handle.dc->drawPixmap(::Floor(context.rect.left), ::Floor(context.rect.top), *imgBuffer);
    else
	context.handle.dc->drawPixmap(::Floor(context.rect.left), ::Floor(context.rect.top), width, height, *imgBuffer);
}



