#ifndef EVENTCALLERBLOCK_H
#define EVENTCALLERBLOCK_H
#include "Block.hpp"
#include "Event.hpp"
#include <memory>

namespace BCIEvent{
    class EventCallerBlock : public Block{
	std::shared_ptr<Event> _event;
	public:
	EventCallerBlock(Block* previous, std::shared_ptr<Event> event);
	Block* run(Actor &callingActor);
    };
}
#endif
