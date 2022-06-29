#include "LoopBlock.hpp"
#include "IntegerExpression.hpp"

using namespace BCIEvent;

template<IntegerExpression T>
LoopStartBlock::LoopStartBlock(Block* previous, LoopEndBlock* endBlock, T iterationGetter) : Block(previous){
    _iterationGetter = getIterFn(iterationGetter);
    _endBlock = endBlock;
}

Block* LoopStartBlock::run(Actor& callingActor){
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

Block* LoopEndBlock::run(Actor &callingActor){
    _startBlock->_currentIter++; //iterate loop
    if (!_startBlock->_isLooping){ //if loop is done, return the next block outside the loop
	return _next;
    }
    return _startBlock; //else return the start block of the loop
}

LoopEndBlock::LoopEndBlock(LoopStartBlock* startBlock) : Block(this){
    _startBlock = startBlock;
}

LoopEndBlock::LoopEndBlock(Block* previous, LoopStartBlock* startBlock) : Block(previous){
    _startBlock = startBlock;
}


std::function<int (const Actor&)> getIterFn(std::function<int (const Actor&)> iterFn){
    return iterFn;
}
std::function<int (const Actor&)> getIterFn(std::function<int ()> iterFn){
    return [&](const Actor&){ return iterFn();};
}
std::function<int (const Actor&)> getIterFn(std::string varName){
    return [&](const Actor& callingActor){
	return callingActor.getVariable<int>(varName);	
    };
}
std::function<int (const Actor&)> getIterFn(int iterations){
    return [=](const Actor&){return iterations;};
}
