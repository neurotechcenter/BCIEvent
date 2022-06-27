#ifndef STARTEVENT_H
#define STARTEVENT_H

#include "Event.hpp"
#include <memory>
namespace BCIEvent{
    /**
     * Singleton class representing the event which runs when the application starts.
     */
    class StartEvent : public Event{
	public:
    	    static std::shared_ptr<StartEvent> getInstance(){
		static std::shared_ptr<StartEvent> event{new StartEvent};
		return event;
	    }
	    StartEvent(StartEvent const&) = delete;
	    void operator=(StartEvent const&) = delete;

	private:
	    StartEvent(){};
    };

}


#endif
