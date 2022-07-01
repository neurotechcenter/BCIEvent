#ifndef IFBLOCK_H
#define IFBLOCK_H

#include "Block.hpp"
#include <functional>
#include "BooleanExpression.hpp"
#include "StatementCloseBlock.hpp"

namespace BCIEvent{
    class IfEndBlock : public StatementCloseBlock{
	public:
	Block* run(Actor &callingActor);
    };

    class IfStartBlock : public Block{
	std::function<bool(Actor &callingActor)> _condition;
	IfEndBlock* _endBlock;
	public:

	    template <BooleanExpression T>
	    IfStartBlock(Block* previous, IfEndBlock* endBlock, T condition);
	Block* run(Actor &callingActor);
    };
}

#endif
