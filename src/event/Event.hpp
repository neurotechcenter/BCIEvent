#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <vector>


namespace BCIEvent_N{
    class EventListener;
    class Event{
	std::vector<EventListener*> _listeners;
	public:
	virtual void trigger();
	void addListener(EventListener*);

    };
}

#endif
