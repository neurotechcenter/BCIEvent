#ifndef IFBLOCK_H
#define IFBLOCK_H

#include "Block.hpp"
#include <functional>

namespace BCIEvent{
    class IfEndBlock : public Block{
	public:
	    IfEndBlock(Block* previous);
	Block* run;
    };

    class IfStartBlock : public Block{
	std::function<bool()> _condition;
	IfEndBlock* _endBlock;
	public:
	    IfStartBlock(Block* previous, std::function<bool()> condition);
	Block* run;
    };
}

#endif
