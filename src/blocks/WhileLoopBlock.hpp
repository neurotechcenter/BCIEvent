#ifndef WHILELOOP_H
#define WHILELOOP_H
#include "Block.hpp"
#include <string>
#include <functional>
#include "BooleanExpression.hpp"
#include "StatementCloseBlock.hpp"
#include "ActorUtil.hpp"
namespace BCIEvent_N{

    /**
     * Blocks for while loops.
     * The condition for looping is evaluated every iteration of the loop.
     */
    

    class WhileLoopEndBlock;
    class WhileLoopStartBlock : public Block{
	WhileLoopEndBlock* _endBlock = nullptr;
	bool _isLooping = false;
	friend class WhileLoopEndBlock;
	public:
		WhileLoopStartBlock(Block* previous, std::function<bool(const Sequence&)> condition);
	Block* run(Sequence& sequence) override;
	void setEndBlock(WhileLoopEndBlock* endBlock); //sets the end block. This must be called.

	private:
	std::function<bool (const Sequence&)> _condition;

    };
    

    class WhileLoopEndBlock : public StatementCloseBlock{
	WhileLoopStartBlock* _startBlock;
	public:
	WhileLoopEndBlock(WhileLoopStartBlock* startBlock); //constructor which sets _next to itself. For use with a stack holding closing blocks
	Block* run(Sequence& sequence) override;
    };
}


#endif
