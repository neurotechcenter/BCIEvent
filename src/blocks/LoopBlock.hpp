#ifndef LOOPBLOCK_H
#define LOOPBLOCK_H

#include <functional>
#include "Block.hpp"
#include "ActorUtil.hpp"
#include "IntegerExpression.hpp"
#include "StatementCloseBlock.hpp"

namespace BCIEvent_N{

    /**
     * Blocks for making a for loop
     * The function is evaluated once, at the start of the loop.
     */
    class LoopEndBlock;
    class LoopStartBlock : public Block{
	LoopEndBlock* _endBlock = nullptr;
	std::function<int (const Sequence& sequence)> _iterationGetter;
	int _iterations;
	int _currentIter;
	bool _isLooping = false;
	friend class LoopEndBlock;

	public:
		LoopStartBlock(Block* previous, std::function<int(const Sequence&)> iterationGetter);
	
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
