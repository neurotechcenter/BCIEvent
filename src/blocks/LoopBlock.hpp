#ifndef LOOPBLOCK_H
#define LOOPBLOCK_H

#include <functional>
#include "Block.hpp"
#include "IntegerExpression.hpp"

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

	//tag dispatch because all the different inputs need to be converted to an int function	
	std::function<int (const Actor&)> getIterFn(std::function<int (const Actor& callingActor)>);
	std::function<int (const Actor&)> getIterFn(std::function<int ()>);
	std::function<int (const Actor&)> getIterFn(std::string variableName);
	std::function<int (const Actor&)> getIterFn(int number);


	public:
	template<IntegerExpression T>
	LoopStartBlock(Block* previous, LoopEndBlock* endBlock, T iterationGetter);
	Block* run (Actor& callingActor);
    };
    class LoopEndBlock : public Block{
	LoopStartBlock* _startBlock;
	public:
	LoopEndBlock(LoopStartBlock* startBlock); //constructor which sets _next to itself. For use with a stack holding closing blocks.
	LoopEndBlock(Block* previous, LoopStartBlock* startBlock); //avoid this constructor unless you are building sequences manually
	Block* run(Actor& callingActor);
    };
}



#endif
