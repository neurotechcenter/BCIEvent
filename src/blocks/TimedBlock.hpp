#ifndef TIMEDBLOCK_H
#define TIMEDBLOCK_H
#include <chrono>
#include "Block.hpp"

namespace BCIEvent{
    /**
     *	Blocks which ensure a certain amount of time has passed before moving on.
     *	Similar to TimerBlock, but these enclose multiple blocks.
     *	Once the end Block is reached, it will wait until its timer has completed before returning the next block
     */

    class TimedBlockStart : public Block{
	std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
	public:
	Block* run();
	TimedBlockStart(Block* previous, std::chrono::duration<std::chrono::high_resolution_clock> time);
	inline std::chrono::time_point<std::chrono::high_resolution_clock> startTime() {return _startTime;}
    };

    class TimedBlockEnd : public Block{
	TimedBlockStart* _start;
	public:
	Block* run;
	TimedBlockEnd(Block* previous, TimedBlockStart* start);
    };
}


#endif
