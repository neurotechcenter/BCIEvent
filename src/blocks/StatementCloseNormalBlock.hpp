// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef STATEMENTCLOSENORMAL_HPP
#define STATEMENTCLOSENORMAL_HPP

#include "StatementCloseBlock.hpp"

namespace BCIEvent_N {
	/*
	* A normal block whose next value is set to itself initally, as it is only used for deleting 
	* variables and timers as they go out of scope. As such, it is placed on the closeBlock stack and has its
	* nextblock field set after initialization.
	*/
	class StatementCloseNormalBlock : public StatementCloseBlock {
		std::function<void(Sequence&)> _action;

	public:
		StatementCloseNormalBlock(std::function<void(Sequence&)> action);

		Block* run(Sequence& callingSequence) override;

	};

}

#endif
