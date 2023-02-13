// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "TimedBlock.hpp"
#include "blocks/Block.hpp"
#include <chrono>

using namespace BCIEvent_N;

TimedBlockStart::TimedBlockStart(Block* previous, double timeSeconds) : Block(previous){
    _time = timeSeconds;
}

Block* TimedBlockStart::run(Sequence& sequence){
    _timer.reset();
    _timer.start();
    return _next;
}

TimedBlockEnd::TimedBlockEnd(TimedBlockStart* start){
    _start = start;
}

Block* TimedBlockEnd::run(Sequence& sequence){
    if (_start->timer().time() >= _start->time()) {
	return _next;
    }
    return this; //wait until time has elapsed
}

