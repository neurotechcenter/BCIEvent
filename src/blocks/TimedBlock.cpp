#include "TimedBlock.hpp"
#include "blocks/Block.hpp"
#include <chrono>

using namespace BCIEvent;

TimedBlockStart::TimedBlockStart(Block* previous, std::chrono::duration<std::chrono::high_resolution_clock> time) : Block(previous){
    _time = time;
}

Block* TimedBlockStart::run(Actor &callingActor){
    _startTime = std::chrono::high_resolution_clock::now();
    return _next;
}

TimedBlockEnd::TimedBlockEnd(Block* previous, TimedBlockStart* start) : Block(previous){
    _start = start;
}

Block* TimedBlockEnd::run(Actor &callingActor){
    if (std::chrono::high_resolution_clock::now() >= _start->startTime() + _start->time()){
	return _next;
    }
    return this; //wait until time has elapsed
}
