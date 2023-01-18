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
