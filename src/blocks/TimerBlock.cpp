#include "TimerBlock.hpp"
#include <chrono>

using namespace BCIEvent;


TimerBlock::TimerBlock(Block* previous, std::chrono::duration<std::chrono::high_resolution_clock> time, std::function<void()> action) : Block(previous){
    _time = time;
    _action = action;
}

Block* TimerBlock::run(){
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
    _action(); //time has not elapsed; execute action and return this block.
    return this; 
}
