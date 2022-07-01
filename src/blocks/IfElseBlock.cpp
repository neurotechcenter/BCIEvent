#include "IfElseBlock.hpp"
#include "ActorUtil.hpp"

using namespace BCIEvent;

template<BooleanExpression B>
IfElseStartBlock::IfElseStartBlock(Block* previous, B condition, IfElseElseBlock* elseBlock, IfElseEndBlock* endBlock) : Block(previous){
   _condition = getExpressionFn<bool>(condition); 
   _elseBlock = elseBlock;
   _endBlock = endBlock;
}

Block* IfElseStartBlock::run(Actor& callingActor){
    if (_condition(callingActor)){
	_elseBlock->_ifCondition = true;
	return _next;
    } else {
	_elseBlock->_ifCondition = false;
	return _elseBlock;
    }
}

IfElseElseBlock::IfElseElseBlock(IfElseEndBlock* endBlock){
    _endBlock = endBlock;
}

Block* IfElseElseBlock::run(Actor& callingActor){
    if (_ifCondition){ //'if' branch already ran, go to end of if else statement
	return _endBlock;
    } else {
	return _next;
    }
}


Block* IfElseEndBlock::run(Actor& callingActor){
    return _next;
}
