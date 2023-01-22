// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "HeadBlock.hpp"

using namespace BCIEvent_N;

HeadBlock::HeadBlock() : Block(this){}
HeadBlock::~HeadBlock(){
    if (_next == this){
 //just in case this is the only block in a series, so that it doesnt try to delete itself
	_next = nullptr;
    }
}
Block* HeadBlock::run(Sequence &sequence){
    return _next;
}

