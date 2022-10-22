#include "WhileLoopBlock.hpp"
#include "BooleanExpression.hpp"
#include <stdexcept>

using namespace BCIEvent;


Block* WhileLoopStartBlock::run(Sequence& sequence){
    if (!_endBlock){
	throw std::runtime_error("Loop start block has no end block (call setEndBlock())");
    }
    if (!_isLooping){ //begin loop
	_isLooping = true;
    }
    if (!_condition(sequence)){ //loop is finished
	_isLooping = false;
	return _endBlock;
    }
    return _next;
}

void WhileLoopStartBlock::setEndBlock(WhileLoopEndBlock* endBlock){
    _endBlock = endBlock;
}

Block* WhileLoopEndBlock::run(Sequence& sequence){
    if (!_startBlock->_isLooping){ //loop has finished
	return _next;
    }
    return _startBlock;
}

WhileLoopEndBlock::WhileLoopEndBlock(WhileLoopStartBlock* startBlock){
    _startBlock = startBlock;
}


