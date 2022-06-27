#include "EventCallerBlock.hpp"


using namespace BCIEvent;

EventCallerBlock::EventCallerBlock(Block* previous, std::shared_ptr<Event> event) : Block(previous){
    _event = event;
}

Block* EventCallerBlock::run(Actor &callingActor){
    _event->trigger();
    return _next;
}
