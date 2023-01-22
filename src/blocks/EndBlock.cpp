// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "EndBlock.hpp"
#include "Block.hpp"

using namespace BCIEvent_N;

EndBlock::EndBlock(Block* previous) : Block(previous){
    _next = nullptr;
}

EndBlock::~EndBlock() {}

Block* EndBlock::run(Sequence &sequence){return _next;}



