#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <vector>


namespace BCIEvent{
    class EventListener;
    class Event{
	std::vector<EventListener*> _listeners;
	public:
	void trigger();
	void addListener(EventListener*);

    };
}

#endif
