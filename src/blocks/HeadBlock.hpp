// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef HEADBLOCK_H
#define HEADBLOCK_H
#include "Block.hpp"

namespace BCIEvent_N{
    class HeadBlock : public Block{
	public:
	/**
	 * Because head blocks are the first block in a series, they have no previous block.
	 * However, the Block constructor expects a previous block, so the HeadBlock
	 * passes itself.
	 * This means that _next will point to itself until more blocks are added.
	 */
	HeadBlock();
	~HeadBlock();
	Block* run(Sequence &sequence) override;
    };
}


#endif

