// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef TIMEDBLOCK_H
#define TIMEDBLOCK_H
#include <chrono>
#include "Block.hpp"
#include "StatementCloseBlock.hpp"

namespace BCIEvent_N{
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

