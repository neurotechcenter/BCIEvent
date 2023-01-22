// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "WhileLoopBlock.hpp"
#include "BooleanExpression.hpp"
#include <stdexcept>

using namespace BCIEvent_N;


WhileLoopStartBlock::WhileLoopStartBlock(Block* previous, std::function<bool(const Sequence&)> condition) : Block(previous) {
	    _condition = condition;
}

Block* WhileLoopStartBlock::run(Sequence& sequence){
    if (!_endBlock){
	throw std::runtime_error("Loop start block has no end block (call setEndBlock())");
    }
    if (!_isLooping){ //begin loop
	_isLooping = true;
    }
    if (!_condition(sequence)){ //loop is finished
	_isLooping = false;
	return _endBlock;
    }
    return _next;
}

void WhileLoopStartBlock::setEndBlock(WhileLoopEndBlock* endBlock){
    _endBlock = endBlock;
}

Block* WhileLoopEndBlock::run(Sequence& sequence){
    if (!_startBlock->_isLooping){ //loop has finished
	return _next;
    }
    return _startBlock;
}

WhileLoopEndBlock::WhileLoopEndBlock(WhileLoopStartBlock* startBlock){
    _startBlock = startBlock;
}



