#ifndef IFELSEBLOCK_H
#define IFELSEBLOCK_H

#include "Actor.hpp"
#include "BooleanExpression.hpp"
#include "StatementCloseBlock.hpp"
#include "ActorUtil.hpp"
namespace BCIEvent{

class IfElseEndBlock : public StatementCloseBlock{
    public:
    Block* run(Actor& callingActor);
};

class IfElseElseBlock : public StatementCloseBlock{
    IfElseEndBlock* _endBlock;
    bool _ifCondition;
    friend class IfElseStartBlock;
    public:
    IfElseElseBlock(IfElseEndBlock* endBlock);
    Block* run(Actor& callingActor);

};

class IfElseStartBlock : public Block{
    IfElseElseBlock* _elseBlock;
    IfElseEndBlock* _endBlock;
    std::function<bool (Actor&)> _condition;

    public:
	template<BooleanExpression B>
	IfElseStartBlock(Block* previous, B condition, IfElseElseBlock* elseBlock, IfElseEndBlock* endBlock) : Block(previous){
	   _condition = getExpressionFn<bool>(condition); 
	   _elseBlock = elseBlock;
	   _endBlock = endBlock;
	}
    Block* run(Actor& callingActor);
};



}


#endif
