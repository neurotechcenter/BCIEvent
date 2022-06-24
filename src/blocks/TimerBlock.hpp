#ifndef TIMERBLOCK_H
#define TIMERBLOCK_H
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
       std::chrono::duration<std::chrono::high_resolution_clock> _time;
       std::chrono::duration<std::chrono::high_resolution_clock> _timeElapsed;
       std::function<void()> _action;
    public:
	TimerBlock(Block* previous, std::chrono::duration<std::chrono::high_resolution_clock> time, std::function<void> action);
	Block* run;
   }; 
}

#endif
