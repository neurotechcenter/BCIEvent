#include "TimerBlock.hpp"
#include <chrono>

using namespace BCIEvent;


TimerBlock::TimerBlock(Block* previous, std::chrono::duration<double> time, std::function<void(Actor& callingActor)> action) : Block(previous){
    _time = time;
    _action = action;
}

TimerBlock::TimerBlock(Block* previous, std::chrono::duration<double> time) : Block(previous){
    _time = time;
}

Block* TimerBlock::run(Actor& callingActor){
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
	_action(callingActor); //time has not elapsed; execute action and return this block.
    return this; 
}
