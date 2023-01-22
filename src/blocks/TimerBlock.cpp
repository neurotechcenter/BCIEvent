// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "TimerBlock.hpp"
#include <chrono>

using namespace BCIEvent_N;


TimerBlock::TimerBlock(Block* previous, std::chrono::duration<double> time, std::function<void(Sequence& sequence)> action) : Block(previous){
    _time = time;
    _action = action;
}

TimerBlock::TimerBlock(Block* previous, std::chrono::duration<double> time) : Block(previous){
    _time = time;
}

Block* TimerBlock::run(Sequence& sequence){
    auto now = std::chrono::high_resolution_clock::now();
    _timeElapsed = now - _startTime;
    if (!_isRunning){ //if clock is not running, start it.
       _isRunning=true;
       _startTime = now;
    }
    if (_timeElapsed >= _time){ //time has elapsed, stop the clock and return the next block
	_isRunning=false;
	return _next;
    }
    if(_action) //don't run action if there is no action
	_action(sequence); //time has not elapsed; execute action and return this block.
    return this; 
}

