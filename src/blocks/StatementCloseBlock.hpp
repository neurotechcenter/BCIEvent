// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef STATEMENTCLOSE_H
#define STATEMENTCLOSE_H

#include "Block.hpp"
namespace BCIEvent_N{

    /**
     * Any block which closes a statement.
     * When created, it sets its _next value to itself.
     * It is meant to initialized alongside its opening block, but added to the sequence later.
     */
    class StatementCloseBlock : public Block{
	public:
	    StatementCloseBlock() : Block(this) {};
    };
}

#endif

