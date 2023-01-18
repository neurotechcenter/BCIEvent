#include "Event.hpp"
#include "EventListener.hpp"


using namespace BCIEvent_N;


void Event::trigger(){
    for (EventListener* listener : _listeners){
	listener->trigger();
    }
}

void Event::addListener(EventListener* listener){
    _listeners.push_back(listener);
}
