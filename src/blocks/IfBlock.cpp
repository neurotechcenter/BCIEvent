// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "IfBlock.hpp"

using namespace BCIEvent_N;

IfStartBlock::IfStartBlock(Block* previous, IfEndBlock* endBlock, std::function<bool(const Sequence&)> condition) : Block(previous), _condition{ condition } {
	    _endBlock = endBlock;
	}

Block* IfEndBlock::run(Sequence& sequence){
    return _next;
}


Block* IfStartBlock::run(Sequence& sequence){
    if (_condition( sequence ))
	return _next;
    else
	return _endBlock;
}

