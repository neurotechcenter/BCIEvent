#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include "HeadBlock.hpp"
#include <memory>

namespace BCIEvent{
    /**
     * A block that waits for an event.
     */
    class Event;
    class EventListener{
	HeadBlock* _next;
	bool _isTriggered;
	
	public:

	void trigger() {_isTriggered = true; }
	bool isTriggered() { return _isTriggered; }
	HeadBlock* getNext() { return _next; _isTriggered = false; } //called by actor when it recognizes the listener as triggered
	void setNext(HeadBlock* next) {_next = next; }
	EventListener(std::shared_ptr<Event> listeningEvent);
	~EventListener();
    };
}


#endif
