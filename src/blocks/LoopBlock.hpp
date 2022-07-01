#ifndef LOOPBLOCK_H
#define LOOPBLOCK_H

#include <functional>
#include "Block.hpp"
#include "IntegerExpression.hpp"
#include "StatementCloseBlock.hpp"

namespace BCIEvent{

    /**
     * Blocks for making a for loop
     * The function is evaluated once, at the start of the loop.
     */
    class LoopEndBlock;
    class LoopStartBlock : public Block{
	LoopEndBlock* _endBlock;
	std::function<int (const Actor& callingActor)> _iterationGetter;
	int _iterations;
	int _currentIter;
	bool _isLooping = false;
	friend class LoopEndBlock;

	public:
	template<IntegerExpression T>
	LoopStartBlock(Block* previous, T iterationGetter);
	void addEndBlock(LoopEndBlock* endBlock); //must be called
	Block* run (Actor& callingActor);
    };
    class LoopEndBlock : public StatementCloseBlock{
	LoopStartBlock* _startBlock;
	public:
	LoopEndBlock(LoopStartBlock* startBlock); //constructor which sets _next to itself. For use with a stack holding closing blocks.
	Block* run(Actor& callingActor);
    };
}



#endif
