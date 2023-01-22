// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef ENDBLOCK_H
#define ENDBLOCK_H
#include "Block.hpp"
namespace BCIEvent_N{

    /**
     * A block that is meant to be at the end of a series of blocks.
     * It is a normal block without any action but its _next is the null pointer.
     * Calling run will return a null pointer so handle it accordingly.
     */
    class EndBlock : public Block {
	public:
	EndBlock(Block* prev);
	~EndBlock();
	Block* run(Sequence &sequence) override;
    };
}
#endif

