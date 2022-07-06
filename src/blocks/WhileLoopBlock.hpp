#ifndef WHILELOOP_H
#define WHILELOOP_H
#include "Block.hpp"
#include <string>
#include <functional>
#include "BooleanExpression.hpp"
#include "StatementCloseBlock.hpp"
#include "ActorUtil.hpp"
namespace BCIEvent{

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
	template <BooleanExpression T>
	WhileLoopStartBlock(Block* previous, T condition) : Block(previous){
	    _condition = getExpressionFn<int>(condition);
	}
	Block* run(Actor& callingActor);
	void setEndBlock(WhileLoopEndBlock* endBlock); //sets the end block. This must be called.

	private:
	std::function<bool (const Actor&)> _condition;

    };
    

    class WhileLoopEndBlock : public StatementCloseBlock{
	WhileLoopStartBlock* _startBlock;
	public:
	WhileLoopEndBlock(WhileLoopStartBlock* startBlock); //constructor which sets _next to itself. For use with a stack holding closing blocks
	Block* run(Actor& callingActor);
    };
}


#endif
