#include "WhileLoopBlock.hpp"
#include "BooleanExpression.hpp"
#include <stdexcept>

using namespace BCIEvent;


Block* WhileLoopStartBlock::run(Actor& callingActor){
    if (!_endBlock){
	throw std::runtime_error("Loop start block has no end block (call setEndBlock())");
    }
    bool b = callingActor.getVariable<bool>("e");
    if (!_isLooping){ //begin loop
	_isLooping = true;
    }
    if (!_condition(callingActor)){ //loop is finished
	_isLooping = false;
	return _endBlock;
    }
    return _next;
}

void WhileLoopStartBlock::setEndBlock(WhileLoopEndBlock* endBlock){
    _endBlock = endBlock;
}

Block* WhileLoopEndBlock::run(Actor& callingActor){
    if (!_startBlock->_isLooping){ //loop has finished
	return _next;
    }
    return _startBlock;
}

WhileLoopEndBlock::WhileLoopEndBlock(WhileLoopStartBlock* startBlock){
    _startBlock = startBlock;
}


