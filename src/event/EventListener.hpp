#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include <memory>
#include "ProtoSequence.hpp"

namespace BCIEvent{
    class Event;
	class HeadBlock;
    /**
     * This holds a sequence and tallies how many times it has been triggered.
	 * An EventListener is not created with a listening event, instead, it is registered to an event externally.
     */
    class EventListener{
	ProtoSequence _seq;
	int _timesTriggered;
	
	public:

	EventListener(ProtoSequence sequence);
	void trigger() { _timesTriggered++; }
	int timesTriggered() { return _timesTriggered; }
	Sequence* getSequence(); //called by actor when it recognizes the listener as triggered

    };
}


#endif
