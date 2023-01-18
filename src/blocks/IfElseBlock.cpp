#include "IfElseBlock.hpp"
#include "ActorUtil.hpp"

using namespace BCIEvent_N;

IfElseStartBlock::IfElseStartBlock(Block* previous, std::function<bool(const Sequence&)> condition, IfElseElseBlock* elseBlock, IfElseEndBlock* endBlock) : Block(previous) {
	   _condition = condition; 
	   _elseBlock = elseBlock;
	   _endBlock = endBlock;
}

Block* IfElseStartBlock::run(Sequence& sequence){
    if (_condition(sequence)){
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

Block* IfElseElseBlock::run(Sequence& sequence){
    if (_ifCondition){ //'if' branch already ran, go to end of if else statement
	return _endBlock;
    } else {
	return _next;
    }
}


Block* IfElseEndBlock::run(Sequence& sequence){
    return _next;
}
