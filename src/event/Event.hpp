#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <vector>


namespace BCIEvent{
    class EventListener;
    class Event{
	std::string _name;
	std::vector<EventListener*> _listeners;
	bool _isTriggered;
	public:
	Event(std::string name);
	void trigger();
	void addListener(EventListener*);

    };
}

#endif
