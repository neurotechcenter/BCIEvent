#ifndef SEQUENCEBUILDER_H
#define SEQUENCEBUILDER_H

#include <memory>
#include <vector>
#include <stack>
#include <functional>
#include <chrono>
#include "Block.hpp"
#include "Event.hpp"
#include "EventListener.hpp"
#include "StartEvent.hpp"
#include "BooleanExpression.hpp"
#include "IntegerExpression.hpp"
#include "StatementCloseBlock.hpp"
#include "IfBlock.hpp"
#include "IfElseBlock.hpp"
#include "LoopBlock.hpp"
#include "WhileLoopBlock.hpp"
#include "WaitForProcessBlock.hpp"

namespace BCIEvent {
    class SequenceBuilder {
	HeadBlock* _head;
	Block* _lastBlock;
	std::stack<StatementCloseBlock*> _controlCloseBlocks;	
	
	public:
	SequenceBuilder();

	SequenceBuilder& addNormalBlock(std::function<void(Sequence &)> action);
	template <BooleanExpression B>
	SequenceBuilder& addIfBlock(B condition){
	    auto endBlk = new IfEndBlock();
	    _lastBlock = new IfStartBlock(_lastBlock, endBlk, condition);
	    _controlCloseBlocks.push(endBlk);
	    return *this;
	}

	
	template<BooleanExpression B>
	SequenceBuilder& addIfElseBlock(B condition){
	    auto endBlk = new IfElseEndBlock();
	    auto elseBlk = new IfElseElseBlock(endBlk);
	    _lastBlock = new IfElseStartBlock(_lastBlock, condition, elseBlk, endBlk);
	    _controlCloseBlocks.push(endBlk);
	    _controlCloseBlocks.push(elseBlk);
	    return *this;
	}
	
	SequenceBuilder& addTimerBlock(std::chrono::duration<double> time, std::function<void(Actor &)> action);
	SequenceBuilder& addTimerBlock(std::chrono::duration<double> time);
	SequenceBuilder& addTimedBlock(std::chrono::duration<double> time);
	SequenceBuilder& addEventCallerBlock(std::string);
	SequenceBuilder& addWaitForProcessBlock();

	template<IntegerExpression I>
	SequenceBuilder& addLoopBlock(I iterations){
	    auto startBlk = new LoopStartBlock(_lastBlock, iterations);
	    auto endBlk = new LoopEndBlock(startBlk);
	    startBlk->addEndBlock(endBlk);
	    _lastBlock = startBlk;
	    _controlCloseBlocks.push(endBlk);
	    return *this;
	}


	template <BooleanExpression B>
	SequenceBuilder& addWhileLoopBlock(B condition){
	    auto startBlk = new WhileLoopStartBlock(_lastBlock, condition);
	    auto endBlk = new WhileLoopEndBlock(startBlk);
	    startBlk->setEndBlock(endBlk);
	    _lastBlock = startBlk;
	    _controlCloseBlocks.push(endBlk);
	    return *this;
	}


	/**
	 * Control elements which contain multiple blocks, such as if statements or loops,
	 * consist of two individual blocks. When a control block is added,
	 * its associated closing blocks are placed in a stack. 
	 * closeStatement() adds the most recently added control closing element to the sequence.
	 * If there are any unclosed statements when the sequence is completed,
	 * or if closeStatement is called too many times, an exception is thrown.
	 */
	SequenceBuilder& closeStatement();

	HeadBlock* getSequenceStart();

    };
}

#endif
