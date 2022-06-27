#include <memory>
#include "HeadBlock.hpp"
#include "NormalBlock.hpp"
#include "SequenceBuilder.hpp"
#include "StartEvent.hpp"
#include "IfBlock.hpp"
#include "TimerBlock.hpp"
#include "EndBlock.hpp"
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

void SequenceBuilder::addNormalBlock(std::function<void (Actor& callingActor)> action){
   _lastBlock = new NormalBlock(_lastBlock, action); 
}

void SequenceBuilder::addIfBlock(std::function<bool (Actor& callingActor)> condition){
    auto endBlk = new IfEndBlock();
    _lastBlock = new IfStartBlock(_lastBlock, endBlk, condition);
    _controlCloseBlocks.push(endBlk);
}

void SequenceBuilder::addTimerBlock(std::chrono::duration<std::chrono::high_resolution_clock> time, std::function<void (Actor &callingActor)> action) {
    _lastBlock = new TimerBlock(_lastBlock, time, action);
}



void SequenceBuilder::closeStatement(){
    if (_controlCloseBlocks.size() <= 0){
	throw std::out_of_range("closeStatement() called more times than necessary. Check how many multi-block statements you've added.");
    }
    Block* closeBlock = _controlCloseBlocks.top();
    _lastBlock->setNext(closeBlock);
    _lastBlock = closeBlock;
    _controlCloseBlocks.pop();
}
	
