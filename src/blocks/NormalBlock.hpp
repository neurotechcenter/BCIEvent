// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef NORMALBLOCK_H
#define NORMALBLOCK_H
#include "Block.hpp"
#include <functional>
#include <memory>

namespace BCIEvent_N{
    /**
     * A block which does a single action
     */
    class NormalBlock : public Block {
	std::function<void(Sequence& sequence)> _action; 
	public:
	    Block* run(Sequence& sequence) override;
	    NormalBlock(Block* prev, std::function<void(Sequence& sequence)> action);
    };
}

#endif

