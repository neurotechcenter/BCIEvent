#include "Event.hpp"



using namespace BCIEvent;

Event::Event(std::string name){
    _name = name;
}

void Event::trigger(){
    for (EventListener* listener : _listeners){
	listener->trigger();
    }
}

void Event::addListener(EventListener* listener){
    _listeners.push_back(listener);
}
