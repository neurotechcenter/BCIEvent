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
		IfStartBlock(Block*, IfEndBlock*, std::function<bool(const Sequence&)> condition);
	Block* run(Sequence& sequence) override;
    };
}

#endif
