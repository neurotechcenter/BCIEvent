// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
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

namespace BCIEvent_N {
    class SequenceBuilder {
	std::unique_ptr<HeadBlock> _head;
	Block* _lastBlock;
	//Holds the statement close blocks, which end statements like if or loop. Also holds blocks which remove scoped local variables. 
	//The boolean switch is true if the held block is a scope-ending block, as when closeStatement is called, all variable-removing blocks 
	//until a scope-ending block are added.
	std::stack<std::pair<Block*, bool>> _controlCloseBlocks;	
	
	public:
	SequenceBuilder();

	SequenceBuilder& addNormalBlock(std::function<void(Sequence &)> action);

	
	SequenceBuilder& addTimerBlock(std::chrono::duration<double> time, std::function<void(Sequence &)> action);
	SequenceBuilder& addTimerBlock(std::chrono::duration<double> time);
	SequenceBuilder& addTimedBlock(std::chrono::duration<double> time);
	SequenceBuilder& addWaitForProcessBlock();


	//Adds local variables and timers. These are deleted at the end of their scope, as each block adding one is paired with one removing it.
	SequenceBuilder& addLocalVariable(std::string name, BCIEValue value);
	SequenceBuilder& addLocalVariable(std::string name);

	SequenceBuilder& addLocalTimer(std::string name);

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

