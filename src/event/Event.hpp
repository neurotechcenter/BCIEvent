#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <vector>


namespace BCIEvent{
    class EventListener;
    class Event{
	std::vector<EventListener*> _listeners;
	bool _isTriggered;
	public:
	Event();
	void trigger();
	void addListener(EventListener*);

    };
}

#endif
