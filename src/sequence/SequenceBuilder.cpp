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

SequenceBuilder& SequenceBuilder::addNormalBlock(std::function<void (Actor& callingActor)> action){
   _lastBlock = new NormalBlock(_lastBlock, action); 
   return *this;
}

SequenceBuilder& SequenceBuilder::addEventCallerBlock(std::string) {
    _lastBlock = new EventCallerBlock()

}

SequenceBuilder& SequenceBuilder::addTimerBlock(std::chrono::duration<double> time, std::function<void (Actor &callingActor)> action) {
    _lastBlock = new TimerBlock(_lastBlock, time, action);
    return *this;
}
SequenceBuilder& SequenceBuilder::addTimerBlock(std::chrono::duration<double> time) {
    _lastBlock = new TimerBlock(_lastBlock, time);
    return *this;
}

SequenceBuilder& SequenceBuilder::addWaitForProcessBlock() {
    _lastBlock = new WaitForProcessBlock();
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
	
