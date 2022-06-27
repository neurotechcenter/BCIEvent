#include "IfBlock.hpp"

using namespace BCIEvent;

IfEndBlock::IfEndBlock(Block* previous) : Block(previous){}

IfEndBlock::IfEndBlock() : Block(this){}

Block* IfEndBlock::run(Actor &callingActor){
    return _next;
}

IfStartBlock::IfStartBlock(Block* previous, IfEndBlock* endBlock, std::function<bool(Actor &callingActor)> condition) : Block(previous){
    _condition = condition;
    _endBlock = endBlock;
}

Block* IfStartBlock::run(Actor &callingActor){
    if (_condition( callingActor ))
	return _next;
    else
	return _endBlock;
}
