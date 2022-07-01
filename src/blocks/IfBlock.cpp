#include "IfBlock.hpp"
#include "ActorUtil.hpp"

using namespace BCIEvent;


Block* IfEndBlock::run(Actor &callingActor){
    return _next;
}

template <BooleanExpression T>
IfStartBlock::IfStartBlock(Block* previous, IfEndBlock* endBlock, T condition) : Block(previous){
    _condition = getExpressionFn<bool>(condition);
    _endBlock = endBlock;
}

Block* IfStartBlock::run(Actor &callingActor){
    if (_condition( callingActor ))
	return _next;
    else
	return _endBlock;
}
