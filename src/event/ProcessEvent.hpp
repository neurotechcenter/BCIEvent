#ifndef STARTEVENT_H
#define STARTEVENT_H

#include "Event.hpp"
#include <memory>
namespace BCIEvent{
	class 
    /**
     * Singleton class representing the event triggered each run of BCI2000's processing loop
     */
    class ProcessEvent : public Event{
	public:
    	    static std::shared_ptr<StartEvent> getInstance(){
		static std::shared_ptr<StartEvent> event{new StartEvent};
		return event;
	    }
	    StartEvent(StartEvent const&) = delete;
	    void operator=(StartEvent const&) = delete;
		
		std::vector<WaitForProcessBlock*> _processBlocks;
		void addWaitForProcess(WaitForProcessBlock*);
	private:
	    StartEvent(){};
    };

}


#endif
