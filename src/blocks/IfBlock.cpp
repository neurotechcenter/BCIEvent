#include "IfBlock.hpp"

using namespace BCIEvent;

IfStartBlock::IfStartBlock(Block* previous, IfEndBlock* endBlock, std::function<bool(const Sequence&)> condition) : Block(previous) {
	    _condition = condition;
	    _endBlock = endBlock;
	}

Block* IfEndBlock::run(Sequence& sequence){
    return _next;
}


Block* IfStartBlock::run(Sequence& sequence){
    if (_condition( sequence ))
	return _next;
    else
	return _endBlock;
}
