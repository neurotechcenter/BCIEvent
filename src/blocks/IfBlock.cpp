#include "IfBlock.hpp"

using namespace BCIEvent;

IfEndBlock::IfEndBlock(Block* previous) : Block(previous){}

Block* IfEndBlock::run(){
    return _next;
}

IfStartBlock::IfStartBlock(Block* previous, std::function<bool()> condition) : Block(previous){
    _condition = condition;
}

Block* IfStartBlock::run(){
    if (_condition())
	return _next;
    else
	return _endBlock;
}
