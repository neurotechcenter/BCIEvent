// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "LoopBlock.hpp"
#include "ActorUtil.hpp"
#include "IntegerExpression.hpp"

using namespace BCIEvent_N;

LoopStartBlock::LoopStartBlock(Block* previous, std::function<int(const Sequence&)> iterationGetter) : Block(previous) {
	    _iterationGetter = iterationGetter;
}

Block* LoopStartBlock::run(Sequence& sequence){
    if (!_endBlock){
	throw std::runtime_error("Loop start block has no end block (call setEndBlock())");
    }
    if (!_isLooping){ // begin loop
	_isLooping = true;
	_iterations = _iterationGetter(sequence);
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

Block* LoopEndBlock::run(Sequence& sequence){
    _startBlock->_currentIter++; //iterate loop
    if (!_startBlock->_isLooping){ //if loop is done, return the next block outside the loop
	return _next;
    }
    return _startBlock; //else return the start block of the loop
}

LoopEndBlock::LoopEndBlock(LoopStartBlock* startBlock) {
    _startBlock = startBlock;
}




