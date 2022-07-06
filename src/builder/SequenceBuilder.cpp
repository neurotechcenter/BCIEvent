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


SequenceBuilder::SequenceBuilder(std::shared_ptr<Event> listeningEvent){
   _listener = std::make_unique<EventListener> (listeningEvent); 
   HeadBlock* head  = new HeadBlock();
   _lastBlock = head;
   _listener->setNext(head);
}

std::unique_ptr<EventListener> SequenceBuilder::getSequence(){
    _lastBlock = new EndBlock(_lastBlock);

    if (_controlCloseBlocks.size() != 0){
	throw std::out_of_range("Statements were left unclosed. There are " + std::to_string(_controlCloseBlocks.size()) + " statements left to close.");
    }
    return std::move(_listener);
}

SequenceBuilder& SequenceBuilder::addNormalBlock(std::function<void (Actor& callingActor)> action){
   _lastBlock = new NormalBlock(_lastBlock, action); 
   return *this;
}

template <BooleanExpression B>
SequenceBuilder& SequenceBuilder::addIfBlock(B condition){
    auto endBlk = new IfEndBlock();
    _lastBlock = new IfStartBlock(_lastBlock, endBlk, condition);
    _controlCloseBlocks.push(endBlk);
    return *this;
}

template<BooleanExpression B>
SequenceBuilder& SequenceBuilder::addIfElseBlock(B condition){
    auto endBlk = new IfElseEndBlock();
    auto elseBlk = new IfElseElseBlock(endBlk);
    _lastBlock = new IfElseStartBlock(_lastBlock, condition, elseBlk, endBlk);
    _controlCloseBlocks.push(endBlk);
    _controlCloseBlocks.push(elseBlk);
    return *this;
}

SequenceBuilder& SequenceBuilder::addTimerBlock(std::chrono::duration<double> time, std::function<void (Actor &callingActor)> action) {
    _lastBlock = new TimerBlock(_lastBlock, time, action);
    return *this;
}
SequenceBuilder& SequenceBuilder::addTimerBlock(std::chrono::duration<double> time) {
    _lastBlock = new TimerBlock(_lastBlock, time);
    return *this;
}

template <IntegerExpression I>
SequenceBuilder& SequenceBuilder::addLoopBlock(I iterations){
    auto startBlk = new LoopStartBlock(_lastBlock, iterations);
    auto endBlk = new LoopEndBlock(startBlk);
    startBlk->addEndBlock(endBlk);
    _lastBlock = startBlk;
    _controlCloseBlocks.push(endBlk);
    return *this;
}

template <BooleanExpression B>
SequenceBuilder& SequenceBuilder::addWhileLoopBlock(B condition){
    auto startBlk = new WhileLoopStartBlock(_lastBlock, condition);
    auto endBlk = new WhileLoopEndBlock(startBlk);
    startBlk->setEndBlock(endBlk);
    _lastBlock = startBlk;
    _controlCloseBlocks.push(endBlk);
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
	
