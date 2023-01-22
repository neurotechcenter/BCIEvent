// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef STARTEVENT_H
#define STARTEVENT_H

#include "Event.hpp"
#include <memory>
namespace BCIEvent_N{
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

