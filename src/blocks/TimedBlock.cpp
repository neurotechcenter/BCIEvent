#include "TimedBlock.hpp"
#include "blocks/Block.hpp"
#include <chrono>

using namespace BCIEvent;

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
