#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include "HeadBlock.hpp"
#include "Event.hpp"
#include <memory>

namespace BCIEvent{
    /**
     * A block that waits for an event.
     */
    class EventListener{
	std::shared_ptr<Event> _listeningEvent;
	HeadBlock* _next;
	bool _isTriggered;
	public:
	void trigger() {_isTriggered = true; }
	bool isTriggered() { return _isTriggered; }
	HeadBlock* getNext() { return _next; _isTriggered = false; } //called by actor when it recognizes the listener as triggered
	EventListener(std::shared_ptr<Event> listeningEvent);
	~EventListener();
    };
}


#endif
