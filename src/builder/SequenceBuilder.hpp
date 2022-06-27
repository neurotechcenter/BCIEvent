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

namespace BCIEvent{
    class SequenceBuilder{
	std::weak_ptr<EventListener> _listener;
	Block* _lastBlock;
	std::stack<Block*> _controlCloseBlocks;	
	
	public:
	SequenceBuilder();
	SequenceBuilder(std::shared_ptr<Event> listeningEvent);

	void addNormalBlock(std::function<void()> action);
	void addIfBlock(std::function<bool()> condition);
	void addTimerBlock(std::chrono::duration<std::chrono::high_resolution_clock> time, std::function<void()> action);
	void addTimedBlock(std::chrono::duration<std::chrono::high_resolution_clock> time);
	void addEventCallerBlock(std::shared_ptr<Event> calledEvent);


	/**
	 * Control elements which contain multiple blocks, such as if statements or loops,
	 * consist of two individual blocks. When a control block is added,
	 * its associated closing blocks are placed in a stack. 
	 * closeStatement() adds the most recently added control closing element to the sequence.
	 * If there are any unclosed statements when the sequence is completed,
	 * or if closeStatement is called too many times, an exception is thrown.
	 */
	void closeStatement();



    };
}

#endif
