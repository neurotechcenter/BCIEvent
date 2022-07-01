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

namespace BCIEvent{
    class SequenceBuilder{
	std::unique_ptr<EventListener> _listener;
	Block* _lastBlock;
	std::stack<StatementCloseBlock*> _controlCloseBlocks;	
	
	public:
	SequenceBuilder(std::shared_ptr<Event> listeningEvent);
	SequenceBuilder() : SequenceBuilder(StartEvent::getInstance()) {};

	SequenceBuilder& addNormalBlock(std::function<void(Actor &)> action);
	template<BooleanExpression B>
	SequenceBuilder& addIfBlock(B condition);
	template<BooleanExpression B>
	SequenceBuilder& addIfElseBlock(B condition);
	
	SequenceBuilder& addTimerBlock(std::chrono::duration<std::chrono::high_resolution_clock> time, std::function<void(Actor &)> action);
	SequenceBuilder& addTimerBlock(std::chrono::duration<std::chrono::high_resolution_clock> time);
	SequenceBuilder& addTimedBlock(std::chrono::duration<std::chrono::high_resolution_clock> time);
	SequenceBuilder& addEventCallerBlock(std::shared_ptr<Event> calledEvent);

	template<IntegerExpression I>
	SequenceBuilder& addLoopBlock(I iterations);

	template<BooleanExpression B>
	SequenceBuilder& addWhileLoopBlock(B condition);

	/**
	 * Control elements which contain multiple blocks, such as if statements or loops,
	 * consist of two individual blocks. When a control block is added,
	 * its associated closing blocks are placed in a stack. 
	 * closeStatement() adds the most recently added control closing element to the sequence.
	 * If there are any unclosed statements when the sequence is completed,
	 * or if closeStatement is called too many times, an exception is thrown.
	 */
	SequenceBuilder& closeStatement();

	std::unique_ptr<EventListener> getSequence();

    };
}

#endif
