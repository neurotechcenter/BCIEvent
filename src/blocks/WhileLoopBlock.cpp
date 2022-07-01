#include "WhileLoopBlock.hpp"
#include "BooleanExpression.hpp"

using namespace BCIEvent;

template <BooleanExpression T>
WhileLoopStartBlock::WhileLoopStartBlock(Block* previous, WhileLoopEndBlock* endBlock, T condition) : Block(previous){
    _endBlock = endBlock;
    _condition = getExpressionFn<int>(condition);
}

Block* WhileLoopStartBlock::run(Actor& callingActor){
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


