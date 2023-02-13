// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "EventListener.hpp"
#include "Event.hpp"
#include <exception>
using namespace BCIEvent_N;

EventListener::EventListener(ProtoSequence seq) : _seq(seq), _timesTriggered(0) {}

std::unique_ptr<Sequence> EventListener::getSequence() {
    if (_timesTriggered == 0) {
        throw std::logic_error(std::string("EventListener::getNext() called on untriggered event listener.")
            + std::string(" This should never happen. If no modifications have been made to the source code outside of AppInitPartial.cpp, submit a bug report."));
    }
    _timesTriggered--;
    return _seq.genSequence();
}

