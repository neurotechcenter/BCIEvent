// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include <memory>
#include "ProtoSequence.hpp"

namespace BCIEvent_N{
    class Event;
    /**
     * This holds a sequence and tallies how many times it has been triggered.
	 * An EventListener is not created with a listening event, instead, it is registered to an event externally.
     */
    class EventListener{
	ProtoSequence _seq;
	int _timesTriggered;
	
	public:

	EventListener(ProtoSequence sequence);
	void trigger() { _timesTriggered++; }
	int timesTriggered() { return _timesTriggered; }
	std::unique_ptr<Sequence> getSequence(); //called by actor when it recognizes the listener as triggered

    };
}


#endif

