// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "WaitForProcessBlock.hpp"
#include "ProcessEvent.hpp"

using namespace BCIEvent_N;

WaitForProcessBlock::WaitForProcessBlock(Block* previous) : Block(previous) {
	ProcessEvent::getInstance()->addWaitForProcess(this);
}

void WaitForProcessBlock::process() {
	_waiting = false;
}

Block* WaitForProcessBlock::run(Sequence& sequence) {
	if (_waiting) {
		return this;
	}
	else {
		_waiting = true;
		return _next;
	}
}
