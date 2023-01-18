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
	std::chrono::duration<double> _time;
	public:
	Block* run(Sequence& sequence) override;
	TimedBlockStart(Block* previous, std::chrono::duration<double> time);
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime() {return _startTime;}
	std::chrono::duration<double> time() {return _time;}
    };

    class TimedBlockEnd : public StatementCloseBlock{
	TimedBlockStart* _start;
	public:
	Block* run(Sequence& sequence);
	TimedBlockEnd(TimedBlockStart* start);
    };
}


#endif
