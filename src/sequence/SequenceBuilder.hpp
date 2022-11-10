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
	std::stack<Block*> _controlCloseBlocks;	
	
	public:
	SequenceBuilder();

	SequenceBuilder& addNormalBlock(std::function<void(Sequence &)> action);

	
	SequenceBuilder& addTimerBlock(std::chrono::duration<double> time, std::function<void(Sequence &)> action);
	SequenceBuilder& addTimerBlock(std::chrono::duration<double> time);
	SequenceBuilder& addTimedBlock(std::chrono::duration<double> time);
	SequenceBuilder& addWaitForProcessBlock();

	SequenceBuilder& addLoopBlock(std::function<int(const Sequence&)> iterations);
	SequenceBuilder& addWhileLoopBlock(std::function<bool(const Sequence&)> condition);

	SequenceBuilder& addIfBlock(std::function<bool(const Sequence&)> condition);
	SequenceBuilder& addIfElseBlock(std::function<bool(const Sequence&)> condition);

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
