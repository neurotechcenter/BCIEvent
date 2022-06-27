#ifndef NORMALBLOCK_H
#define NORMALBLOCK_H
#include "Block.hpp"
#include <functional>
#include <memory>

namespace BCIEvent{
    /**
     * A block which does a single action
     */
    class NormalBlock : public Block {
	std::function<void()> _action; 
	public:
	    Block* run(Actor &callingActor);
	    NormalBlock(Block* prev, std::function<void()> action);
    };
}

#endif
