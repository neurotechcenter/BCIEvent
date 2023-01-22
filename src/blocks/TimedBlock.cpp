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

TimedBlockStart::TimedBlockStart(Block* previous, std::chrono::duration<double> time) : Block(previous){
    _time = time;
}

Block* TimedBlockStart::run(Sequence& sequence){
    _startTime = std::chrono::high_resolution_clock::now();
    return _next;
}

TimedBlockEnd::TimedBlockEnd(TimedBlockStart* start){
    _start = start;
}

Block* TimedBlockEnd::run(Sequence& sequence){
    if (std::chrono::high_resolution_clock::now() >= _start->startTime() + _start->time()){
	return _next;
    }
    return this; //wait until time has elapsed
}

