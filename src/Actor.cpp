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

    //Add sequences of triggered events;
    for (EventListener& listener : _listeners) {
        if (listener.timesTriggered > 0) {
            _sequences.push_back(listener.getSequence());
        }
    }

	//Run and update blocks
    for (int i = 0; i < _sequences.size()){
        if (_sequences.front()->update()) { //If sequence is still running, append it to the back of the list
            _sequences.push_back(std::move(_sequences.front))
        }
        _sequences.pop_front() //remove sequence from the front of the list
           //This will either remove and delete a completed sequence, or remove the empty pointer to a still-running sequence that has been moved to the back of the list
        //After these operations, the list of sequences will be the same except without any completed sequences, which will have been deleted.
	}
	_currentSignal = nullptr; //the signal should only ever be accessed during the update stage.
	Invalidate();
	Paint();
    }

Actor::Actor(BCIEventApplication* app) :
	GUI::GraphObject(app->getDisplay(), 0)
{
	_app = app;
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

Actor& Actor::addEventListener(String name, EventListener listener){
    getEvent(name).addListener(listener);
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


int Actor::randInt(int lower, int upper) {
	return _app->randInt(lower, upper);
}

void Actor::addSequence(std::unique_ptr<Sequence> seq) {
    _sequences.push_back(seq.finalizeSeq());
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



