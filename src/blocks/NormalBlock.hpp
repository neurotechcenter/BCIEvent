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
	std::function<void(Sequence& sequence)> _action; 
	public:
	    Block* run(Sequence& sequence);
	    NormalBlock(Block* prev, std::function<void(Sequence& sequence)> action);
    };
}

#endif
