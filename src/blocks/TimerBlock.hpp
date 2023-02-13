// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef TIMERBLOCK_H
#define TIMERBLOCK_H
#include "Actor.hpp"
#include "Block.hpp"
#include <chrono>
#include <functional>

namespace BCIEvent_N{
    /**
     * A block with a timer.
     * waits until time has elapsed before returning the next block.
     * If given an action, it will run the action every cycle of the event loop until time has elapsed
     */
   class TimerBlock : public Block{
       bool _isRunning = false;
       Timer _timer;
       double _time;
       std::function<void(Sequence& sequence)> _action;
    public:
	TimerBlock(Block* previous, double timeSeconds, std::function<void (Sequence&)> action);
	TimerBlock(Block* previous, double timeSeconds); //treated as wait block
	Block* run(Sequence& sequence) override;
   }; 
}

#endif

