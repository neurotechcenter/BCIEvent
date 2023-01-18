#ifndef BCIEVENT_BLOCK_H
#define BCIEVENT_BLOCK_H

#include "Sequence.hpp"

namespace BCIEvent_N{
    class Block{
	protected:
	    Block* _next;
	public:

	    Block(Block* previous){
		previous->setNext(this);
	    };

	    /**
	     * A chain of blocks is deleted sequentially, with each block deleting the next.
	     * For this reason, next must always point to the next block in line.
	     */
	    virtual ~Block(){
		delete _next;
	    }

	    /**
	     * Runs the block's main code and returns the next block to run on the next cycle of the event loop
	     * May return the same block in the case of a timer which has not finished.
	     */
	    virtual Block* run(Sequence& sequence) = 0;
	    void setNext(Block* newNext) { _next = newNext; }
    };    
}
#endif
