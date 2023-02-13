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
		double _time;
		Timer _timer;
	public:
	Block* run(Sequence& sequence) override;
	TimedBlockStart(Block* previous, double timeSeconds);
	double time() {return _time;}
	Timer& timer() { return _timer; }
    };

    class TimedBlockEnd : public StatementCloseBlock{
	TimedBlockStart* _start;
	public:
	Block* run(Sequence& sequence);
	TimedBlockEnd(TimedBlockStart* start);
    };
}


#endif

