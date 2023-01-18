#ifndef TIMERBLOCK_H
#define TIMERBLOCK_H
#include "Actor.hpp"
#include "Block.hpp"
#include <chrono>
#include <functional>

namespace BCIEvent{
    /**
     * A block with a timer.
     * waits until time has elapsed before returning the next block.
     * If given an action, it will run the action every cycle of the event loop until time has elapsed
     */
   class TimerBlock : public Block{
       bool _isRunning = false;
       std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
       std::chrono::duration<double> _time;
       std::chrono::duration<double> _timeElapsed;
       std::function<void(Sequence& sequence)> _action;
    public:
	TimerBlock(Block* previous, std::chrono::duration<double> time, std::function<void (Sequence&)> action);
	TimerBlock(Block* previous, std::chrono::duration<double> time); //treated as wait block
	Block* run(Sequence& sequence) override;
   }; 
}

#endif
