#ifndef NORMALBLOCK_H
#define NORMALBLOCK_H
#include "Block.hpp"
#include <functional>
#include <memory>

namespace BCIEvent_N{
    /**
     * A block which does a single action
     */
    class NormalBlock : public Block {
	std::function<void(Sequence& sequence)> _action; 
	public:
	    Block* run(Sequence& sequence) override;
	    NormalBlock(Block* prev, std::function<void(Sequence& sequence)> action);
    };
}

#endif
