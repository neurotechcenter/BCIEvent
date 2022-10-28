#ifndef STARTEVENT_H
#define STARTEVENT_H

#include "Event.hpp"
#include <memory>
namespace BCIEvent{
	class WaitForProcessBlock;
    /**
     * Singleton class representing the event triggered each run of BCI2000's processing loop
     */
    class ProcessEvent : public Event{
	public:
    	static std::shared_ptr<ProcessEvent> getInstance(){
			static std::shared_ptr<ProcessEvent> event{new ProcessEvent};
			return event;
	    }

	    ProcessEvent(ProcessEvent const&) = delete;
	    void operator=(ProcessEvent const&) = delete;
		
		std::vector<WaitForProcessBlock*> _processBlocks;
		void addWaitForProcess(WaitForProcessBlock*);
	private:
	    StartEvent(){};
    };

}


#endif
