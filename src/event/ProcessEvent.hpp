// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef PROCESSEVENT_H
#define PROCESSEVENT_H

#include "Event.hpp"
#include <memory>
namespace BCIEvent_N{
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

