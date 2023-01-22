// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "NormalBlock.hpp"
#include <functional>

using namespace BCIEvent_N;

NormalBlock::NormalBlock(Block* prev, std::function<void(Sequence& sequence)> action) : Block(prev){
    _action = action;
} 

Block* NormalBlock::run(Sequence& sequence){
    _action(sequence);
    return _next;
}

