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
#include <QBitmap>
#include <QPainter>


using namespace BCIEvent;

    void Actor::update( const GenericSignal& signal ){

	//Set the signal for this cycle.
	_currentSignal = &signal;
	
	//Run and update blocks
	bciout << "Blocks: " << _currentBlocks.size();

	for(int i = 0; i < _currentBlocks.size(); i++){
	    Block* currentBlock = _currentBlocks.front();
	    Block* nextBlock = currentBlock->run(*this); //runs the block and gets a reference to the next block
	    _currentBlocks.pop_front();
	    if (nextBlock != nullptr){ //only add next block if it exists
		_currentBlocks.push_back(nextBlock);
	    }
	}


	//Handle events
	
	for (auto &&listener : _eventListeners){
	    if (listener->isTriggered()){
		_currentBlocks.push_back(listener->getNext());
	    }
	}
	_currentSignal = nullptr; //the signal should only ever be accessed during the update stage.
	Invalidate();
	Paint();
    }

Actor::Actor(GlobalVariables* globalVars, States* states, GUI::GraphDisplay& display) :
	GUI::GraphObject(display, 0), _states{states}, _globalVars{globalVars} 
{
    SetAlignment(GUI::Alignment::Center);
    SetScalingMode(GUI::ScalingMode::AdjustBoth);
    Show();
}

Actor::~Actor(){
    DestructorEntered();
}

Actor& Actor::addVariable(std::unique_ptr<Variable> var){
    _variables.insert(std::pair<std::string, std::unique_ptr<Variable>>(var->name(), std::move(var)));
    return *this;
}

Actor& Actor::addEventListener(std::unique_ptr<EventListener> listener){
    _eventListeners.push_back(std::move(listener));
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



