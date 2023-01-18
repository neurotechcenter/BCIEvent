#include <memory>
#include "HeadBlock.hpp"
#include "LoopBlock.hpp"
#include "NormalBlock.hpp"
#include "SequenceBuilder.hpp"
#include "StartEvent.hpp"
#include "IfBlock.hpp"
#include "IfElseBlock.hpp"
#include "TimerBlock.hpp"
#include "TimedBlock.hpp"
#include "EndBlock.hpp"
#include "WhileLoopBlock.hpp"
#include "StatementCloseNormalBlock.hpp"
#include <stdexcept>

using namespace BCIEvent_N;


SequenceBuilder::SequenceBuilder(){
   _head  = std::make_unique<HeadBlock>();
   _lastBlock = static_cast<Block*>(_head.get());
}

HeadBlock* SequenceBuilder::getSequenceStart(){
    _lastBlock = new EndBlock(_lastBlock);

    if (_controlCloseBlocks.size() != 0){
	    throw std::runtime_error("Statements were left unclosed. There are " + std::to_string(_controlCloseBlocks.size()) + " statements left to close.");
    }
    return _head.release();
}

SequenceBuilder& SequenceBuilder::addLocalVariable(std::string name, BCIEValue value) {
	_lastBlock = new NormalBlock(_lastBlock, [&](Sequence& callingSequence) {callingSequence.addVariable(name, value);  });
	auto rmvarblock = new StatementCloseNormalBlock([&](Sequence& callingSequence) {callingSequence.removeVariable(name); });
	_controlCloseBlocks.push(std::make_pair(rmvarblock, false));
	return *this;
}

SequenceBuilder& SequenceBuilder::addLocalVariable(std::string name) {
	return addLocalVariable(name, std::nullopt);
}

SequenceBuilder& SequenceBuilder::addLocalTimer(std::string name) {
	_lastBlock = new NormalBlock(_lastBlock, [&](Sequence& callingSequence) {callingSequence.addTimer(name); });
	auto rmtimerblock = new StatementCloseNormalBlock([&](Sequence& callingSequence) {callingSequence.removeTimer(name); });
	_controlCloseBlocks.push(std::make_pair(rmtimerblock, false));
	return *this;
}

SequenceBuilder& SequenceBuilder::addNormalBlock(std::function<void (Sequence& callingActor)> action){
   _lastBlock = new NormalBlock(_lastBlock, action); 
   return *this;
}


SequenceBuilder& SequenceBuilder::addTimerBlock(std::chrono::duration<double> time, std::function<void (Sequence& callingSequence)> action) {
    _lastBlock = new TimerBlock(_lastBlock, std::chrono::duration_cast<std::chrono::seconds>(time), action);
    return *this;
}
SequenceBuilder& SequenceBuilder::addTimerBlock(std::chrono::duration<double> time) {
    _lastBlock = new TimerBlock(_lastBlock, time);
    return *this;
}

SequenceBuilder& SequenceBuilder::addTimedBlock(std::chrono::duration<double> time) {
    TimedBlockStart* startBlk = new TimedBlockStart(_lastBlock, time);
    Block* endBlk = new TimedBlockEnd(startBlk);
    _lastBlock = static_cast<Block*>(startBlk);
    _controlCloseBlocks.push(std::make_pair(endBlk, true));
    return *this;
}

SequenceBuilder& SequenceBuilder::addWaitForProcessBlock() {
    _lastBlock = new WaitForProcessBlock(_lastBlock);
    return *this;
}

//Adds all non-sequence-terminating blocks(those which remove scoped variables) up to the first sequence-terminating block (those which end if/loop/other statements)
SequenceBuilder& SequenceBuilder::closeStatement(){
    if (_controlCloseBlocks.size() <= 0){
	throw std::out_of_range("closeStatement() called more times than necessary. Check how many multi-block statements you've added.");
    }
    auto closeBlockPair = _controlCloseBlocks.top();
    _lastBlock->setNext(std::get<0>(closeBlockPair));
    _lastBlock = std::get<0>(closeBlockPair);
    _controlCloseBlocks.pop();
	if (std::get<1>(closeBlockPair)) { //this is a terminating block, return
		return *this;
	}
	else { //this is a non-terminating block, pop and add the next block.
		return closeStatement();
	}
}
	

SequenceBuilder& SequenceBuilder::addIfBlock(std::function<bool (const Sequence &)> condition) {
	    auto endBlk = new IfEndBlock();
	    _lastBlock = new IfStartBlock(_lastBlock, endBlk, condition);
	    _controlCloseBlocks.push(std::make_pair(endBlk, true));
	    return *this;
}

	
SequenceBuilder& SequenceBuilder::addIfElseBlock(std::function<bool(const Sequence &)> condition){
	    auto endBlk = new IfElseEndBlock();
	    auto elseBlk = new IfElseElseBlock(endBlk);
	    _lastBlock = new IfElseStartBlock(_lastBlock, condition, elseBlk, endBlk);
	    _controlCloseBlocks.push(std::make_pair(endBlk, true));//these work with scoped variables because adding of blocks to
	    _controlCloseBlocks.push(std::make_pair(elseBlk, true));//the else branch happens after the else block is popped.
	    return *this;
}

SequenceBuilder& SequenceBuilder::addLoopBlock(std::function<int(const Sequence&)> iterations) {
	    auto startBlk = new LoopStartBlock(_lastBlock, iterations);
	    auto endBlk = new LoopEndBlock(startBlk);
	    startBlk->addEndBlock(endBlk);
	    _lastBlock = startBlk;
	    _controlCloseBlocks.push(std::make_pair(endBlk, true));
	    return *this;
}

SequenceBuilder& SequenceBuilder::addWhileLoopBlock(std::function<bool (const Sequence&)> condition){
	    auto startBlk = new WhileLoopStartBlock(_lastBlock, condition);
	    auto endBlk = new WhileLoopEndBlock(startBlk);
	    startBlk->setEndBlock(endBlk);
	    _lastBlock = startBlk;
	    _controlCloseBlocks.push(std::make_pair(endBlk, true));
	    return *this;
}
