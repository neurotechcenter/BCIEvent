#ifndef EVENTCALLERBLOCK_H
#define EVENTCALLERBLOCK_H
#include "Block.hpp"
#include "Event.hpp"
#include <memory>

namespace BCIEvent{
    class EventCallerBlock : public Block{
	std::string _event;
	public:
	EventCallerBlock(Block* previous, std::string event);
	Block* run(Sequence &sequence);
    };
}
#endif
