// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "IfElseBlock.hpp"

using namespace BCIEvent_N;

IfElseStartBlock::IfElseStartBlock(Block* previous, BooleanExpression condition, IfElseElseBlock* elseBlock, IfElseEndBlock* endBlock) : Block(previous) {
	   _condition = condition; 
	   _elseBlock = elseBlock;
	   _endBlock = endBlock;
}

Block* IfElseStartBlock::run(Sequence& sequence){
    if (_condition(sequence)){
		_elseBlock->setCond(true);
	return _next;
    } else {
		_elseBlock->setCond(false);
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

