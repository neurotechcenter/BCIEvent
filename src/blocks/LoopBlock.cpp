#include "LoopBlock.hpp"
#include "ActorUtil.hpp"
#include "IntegerExpression.hpp"

using namespace BCIEvent;

template<IntegerExpression T>
LoopStartBlock::LoopStartBlock(Block* previous, T iterationGetter) : Block(previous){
    _iterationGetter = getExpressionFn<int>(iterationGetter);
}

Block* LoopStartBlock::run(Actor& callingActor){
    if (!_endBlock){
	throw std::runtime_error("Loop start block has no end block (call setEndBlock())");
    }
    if (!_isLooping){ // begin loop
	_isLooping = true;
	_iterations = _iterationGetter(callingActor);
	_currentIter = 0;
    }
    if (_currentIter >= _iterations){ //when looping is done, skip directly to the closing block
	_isLooping = false;
	return _endBlock;
    }
    return _next;
}
void LoopStartBlock::addEndBlock(LoopEndBlock* endBlock){
    _endBlock = endBlock;
}

Block* LoopEndBlock::run(Actor &callingActor){
    _startBlock->_currentIter++; //iterate loop
    if (!_startBlock->_isLooping){ //if loop is done, return the next block outside the loop
	return _next;
    }
    return _startBlock; //else return the start block of the loop
}

LoopEndBlock::LoopEndBlock(LoopStartBlock* startBlock) {
    _startBlock = startBlock;
}



