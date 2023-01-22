// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef IFBLOCK_H
#define IFBLOCK_H

#include "Block.hpp"
#include <functional>
#include "BooleanExpression.hpp"
#include "StatementCloseBlock.hpp"
#include "ActorUtil.hpp"

namespace BCIEvent_N{
    class IfEndBlock : public StatementCloseBlock{
	public:
	Block* run(Sequence& sequence);
    };

    class IfStartBlock : public Block{
	std::function<bool(Sequence& sequence)> _condition;
	IfEndBlock* _endBlock;
	public:
		IfStartBlock(Block*, IfEndBlock*, std::function<bool(const Sequence&)> condition);
	Block* run(Sequence& sequence) override;
    };
}

#endif

