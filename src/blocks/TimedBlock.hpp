#ifndef TIMEDBLOCK_H
#define TIMEDBLOCK_H
#include <chrono>
#include "Block.hpp"
#include "StatementCloseBlock.hpp"

namespace BCIEvent{
    /**
     *	Blocks which ensure a certain amount of time has passed before moving on.
     *	Similar to TimerBlock, but these enclose multiple blocks.
     *	Once the end Block is reached, it will wait until its timer has completed before returning the next block
     */

    class TimedBlockStart : public Block{
	std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
	std::chrono::duration<std::chrono::high_resolution_clock> _time;
	public:
	Block* run(Actor &callingActor);
	TimedBlockStart(Block* previous, std::chrono::duration<std::chrono::high_resolution_clock> time);
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime() {return _startTime;}
	std::chrono::duration<std::chrono::high_resolution_clock> time() {return _time;}
    };

    class TimedBlockEnd : public StatementCloseBlock{
	TimedBlockStart* _start;
	public:
	Block* run(Actor &callingActor);
	TimedBlockEnd(TimedBlockStart* start);
    };
}


#endif
