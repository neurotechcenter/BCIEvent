#ifndef IFBLOCK_H
#define IFBLOCK_H

#include "Block.hpp"
#include <functional>
#include "BooleanExpression.hpp"
#include "StatementCloseBlock.hpp"
#include "ActorUtil.hpp"

namespace BCIEvent{
    class IfEndBlock : public StatementCloseBlock{
	public:
	Block* run(Sequence& sequence);
    };

    class IfStartBlock : public Block{
	std::function<bool(Sequence& sequence)> _condition;
	IfEndBlock* _endBlock;
	public:
	template <BooleanExpression T>
	IfStartBlock(Block* previous, IfEndBlock* endBlock, T condition) : Block(previous){
	    _condition = getExpressionFn<bool>(condition);
	    _endBlock = endBlock;
	}

	Block* run(Sequence& sequence);
    };
}

#endif
