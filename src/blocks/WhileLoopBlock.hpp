#ifndef WHILELOOP_H
#define WHILELOOP_H
#include "Block.hpp"
#include <string>
#include <functional>
#include "BooleanExpression.hpp"
namespace BCIEvent{

    /**
     * Blocks for while loops.
     * The condition for looping is evaluated every iteration of the loop.
     */
    

    class WhileLoopEndBlock;
    class WhileLoopStartBlock : public Block{
	WhileLoopEndBlock* _endBlock;
	bool _isLooping = false;
	friend class WhileLoopEndBlock;
	public:
	template<BooleanExpression T>
	WhileLoopStartBlock(Block* previous, WhileLoopEndBlock* endBlock, T condition);
	Block* run(Actor& callingActor);

	private:
	std::function<bool (const Actor&)> _condition;
	std::function<bool (const Actor&)> getCond(std::function<bool()>);
	std::function<bool (const Actor&)> getCond(std::function<bool(const Actor&)>);
	std::function<bool (const Actor&)> getCond(std::string variableName);
	std::function<bool (const Actor&)> getCond(bool);

    };
    

    class WhileLoopEndBlock : public Block{
	WhileLoopStartBlock* _startBlock;
	public:
	WhileLoopEndBlock(WhileLoopStartBlock* startBlock); //constructor which sets _next to itself. For use with a stack holding closing blocks
	WhileLoopEndBlock(Block* previous, WhileLoopStartBlock* startBlock); //constructor to be used when building sequences manually
	Block* run(Actor& callingActor);
    };
}


#endif
