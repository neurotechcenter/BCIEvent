#include "WhileLoopBlock.hpp"
#include "BooleanExpression.hpp"

using namespace BCIEvent;

template <BooleanExpression T>
WhileLoopStartBlock::WhileLoopStartBlock(Block* previous, WhileLoopEndBlock* endBlock, T condition) : Block(previous){
    _endBlock = endBlock;
    _condition = getCond(condition);
}

template <BooleanExpression T> 
Block* WhileLoopStartBlock::run(Actor& callingActor){
    bool b = callingActor.getVariable<bool>("e");
    if (!_isLooping){ //begin loop
	_isLooping = true;
    }
    if (!_condition()){ //loop is finished
	_isLooping = false;
	return _endBlock;
    }
    return _next;
}

Block* WhileLoopEndBlock::run(Actor& callingActor){
    if (!_startBlock->_isLooping){ //loop has finished
	return _next;
    }
    return _startBlock;
}

WhileLoopEndBlock::WhileLoopEndBlock(WhileLoopStartBlock* startBlock) : Block(this){
    _startBlock = startBlock;
}

WhileLoopEndBlock::WhileLoopEndBlock(Block* previous, WhileLoopStartBlock* startBlock) : Block(previous) {
    _startBlock = startBlock;
}


std::function<bool (const Actor&)> WhileLoopStartBlock::getCond(std::function<bool (const Actor& callingActor)> condition){
    return condition;
}
std::function<bool (const Actor&)> WhileLoopStartBlock::getCond(std::function<bool ()> condition){
    return [&](const Actor& callingActor){return condition();}; 
}
std::function<bool (const Actor&)> WhileLoopStartBlock::getCond(std::string varName){
    return [&](const Actor& callingActor){
        bool b = callingActor.getVariable<bool>("e");
	return b;    
    };
}
std::function<bool (const Actor&)> WhileLoopStartBlock::getCond(bool condition){
    return [&](const Actor& callingActor){return condition;};
}
