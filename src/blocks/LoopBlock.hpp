// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef LOOPBLOCK_H
#define LOOPBLOCK_H

#include <functional>
#include "Block.hpp"
#include "StatementCloseBlock.hpp"
#include "Expression.hpp"

namespace BCIEvent_N{

    /**
     * Blocks for making a for loop
     * The function is evaluated once, at the start of the loop.
     */
    class LoopEndBlock;
    class LoopStartBlock : public Block{
	LoopEndBlock* _endBlock = nullptr;
	IntegerExpression _iterationGetter;
	int _iterations;
	int _currentIter;
	bool _isLooping = false;
	friend class LoopEndBlock;

	public:
		LoopStartBlock(Block* previous, IntegerExpression iterationGetter);
	
	void addEndBlock(LoopEndBlock* endBlock); //must be called
	Block* run (Sequence& sequence) override;
    };
    class LoopEndBlock : public StatementCloseBlock{
	LoopStartBlock* _startBlock;
	public:
	LoopEndBlock(LoopStartBlock* startBlock); //constructor which sets _next to itself. For use with a stack holding closing blocks.
	Block* run(Sequence& sequence) override;
    };
}



#endif

