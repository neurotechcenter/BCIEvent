#ifndef PROCESSEVENT_H
#define PROCESSEVENT_H

#include "Event.hpp"
#include <memory>
namespace BCIEvent{
	class WaitForProcessBlock;
    /**
     * Singleton class representing the event triggered each run of BCI2000's processing loop
     */
    class ProcessEvent{
	public:
    	static std::shared_ptr<ProcessEvent> getInstance(){
			static std::shared_ptr<ProcessEvent> event{new ProcessEvent};
			return event;
	    }

	    ProcessEvent(ProcessEvent const&) = delete;
	    void operator=(ProcessEvent const&) = delete;
		
		std::vector<WaitForProcessBlock*> _processBlocks;
		void addWaitForProcess(WaitForProcessBlock*);
		void trigger();
	private:
		ProcessEvent() { _processBlocks = std::vector<WaitForProcessBlock*>(); };
    };

}


#endif
