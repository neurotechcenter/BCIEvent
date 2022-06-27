#ifndef IFBLOCK_H
#define IFBLOCK_H

#include "Block.hpp"
#include <functional>

namespace BCIEvent{
    class IfEndBlock : public Block{
	public:
	    IfEndBlock(Block* previous);
	    IfEndBlock();
	Block* run(Actor &callingActor);
    };

    class IfStartBlock : public Block{
	std::function<bool(Actor &callingActor)> _condition;
	IfEndBlock* _endBlock;
	public:
	    IfStartBlock(Block* previous, IfEndBlock* endBlock, std::function<bool(Actor &callingActor)> condition);
	Block* run(Actor &callingActor);
    };
}

#endif
