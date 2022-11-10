#include <memory>
#include "HeadBlock.hpp"
#include "LoopBlock.hpp"
#include "NormalBlock.hpp"
#include "SequenceBuilder.hpp"
#include "StartEvent.hpp"
#include "IfBlock.hpp"
#include "IfElseBlock.hpp"
#include "TimerBlock.hpp"
#include "EndBlock.hpp"
#include "WhileLoopBlock.hpp"
#include <stdexcept>

using namespace BCIEvent;


SequenceBuilder::SequenceBuilder(){
   _head  = new HeadBlock();
   _lastBlock = _head;
}

HeadBlock* SequenceBuilder::getSequenceStart(){
    _lastBlock = new EndBlock(_lastBlock);

    if (_controlCloseBlocks.size() != 0){
	    throw std::runtime_error("Statements were left unclosed. There are " + std::to_string(_controlCloseBlocks.size()) + " statements left to close.");
    }
    return _head;
}

SequenceBuilder& SequenceBuilder::addNormalBlock(std::function<void (Sequence& callingActor)> action){
   _lastBlock = new NormalBlock(_lastBlock, action); 
   return *this;
}


SequenceBuilder& SequenceBuilder::addTimerBlock(std::chrono::duration<double> time, std::function<void (Sequence& callingSequence)> action) {
    _lastBlock = new TimerBlock(_lastBlock, time, action);
    return *this;
}
SequenceBuilder& SequenceBuilder::addTimerBlock(std::chrono::duration<double> time) {
    _lastBlock = new TimerBlock(_lastBlock, time);
    return *this;
}

SequenceBuilder& SequenceBuilder::addWaitForProcessBlock() {
    _lastBlock = new WaitForProcessBlock(_lastBlock);
    return *this;
}

SequenceBuilder& SequenceBuilder::closeStatement(){
    if (_controlCloseBlocks.size() <= 0){
	throw std::out_of_range("closeStatement() called more times than necessary. Check how many multi-block statements you've added.");
    }
    Block* closeBlock = _controlCloseBlocks.top();
    _lastBlock->setNext(closeBlock);
    _lastBlock = closeBlock;
    _controlCloseBlocks.pop();
    return *this;
}
	

SequenceBuilder& SequenceBuilder::addIfBlock(std::function<bool (const Sequence &)> condition) {
	    auto endBlk = new IfEndBlock();
	    _lastBlock = new IfStartBlock(_lastBlock, endBlk, condition);
	    _controlCloseBlocks.push(endBlk);
	    return *this;
}

	
SequenceBuilder& SequenceBuilder::addIfElseBlock(std::function<bool(const Sequence &)> condition){
	    auto endBlk = new IfElseEndBlock();
	    auto elseBlk = new IfElseElseBlock(endBlk);
	    _lastBlock = new IfElseStartBlock(_lastBlock, condition, elseBlk, endBlk);
	    _controlCloseBlocks.push(endBlk);
	    _controlCloseBlocks.push(elseBlk);
	    return *this;
}

SequenceBuilder& SequenceBuilder::addLoopBlock(std::function<int(const Sequence&)> iterations) {
	    auto startBlk = new LoopStartBlock(_lastBlock, iterations);
	    auto endBlk = new LoopEndBlock(startBlk);
	    startBlk->addEndBlock(endBlk);
	    _lastBlock = startBlk;
	    _controlCloseBlocks.push(endBlk);
	    return *this;
}

SequenceBuilder& SequenceBuilder::addWhileLoopBlock(std::function<bool (const Sequence&)> condition){
	    auto startBlk = new WhileLoopStartBlock(_lastBlock, condition);
	    auto endBlk = new WhileLoopEndBlock(startBlk);
	    startBlk->setEndBlock(endBlk);
	    _lastBlock = startBlk;
	    _controlCloseBlocks.push(endBlk);
	    return *this;
}
