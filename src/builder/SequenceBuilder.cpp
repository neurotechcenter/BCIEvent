#include <memory>
#include "HeadBlock.hpp"
#include "NormalBlock.hpp"
#include "SequenceBuilder.hpp"
#include "StartEvent.hpp"
#include "IfBlock.hpp"
#include "TimerBlock.hpp"

using namespace BCIEvent;

SequenceBuilder::SequenceBuilder(){
   SequenceBuilder(std::make_shared<EventListener> (StartEvent::getInstance())); 
}

SequenceBuilder::SequenceBuilder(std::shared_ptr<Event> listeningEvent){
   _listener = std::make_shared<EventListener> (listeningEvent); 
   HeadBlock* head  = new HeadBlock();
   _lastBlock = head;
   _listener.lock()->setNext(head);
}

void SequenceBuilder::addNormalBlock(std::function<void ()> action){
   new NormalBlock(_lastBlock, action); 
}

void SequenceBuilder::addIfBlock(std::function<bool ()> condition){
    auto endBlk = new IfEndBlock();
    new IfStartBlock(_lastBlock, endBlk, condition);
    _controlCloseBlocks.push(endBlk);
}

void SequenceBuilder::addTimerBlock(std::chrono::duration<std::chrono::high_resolution_clock> time, std::function<void (Actor&)> action) {
    new TimerBlock(_lastBlock, time, action);
}

void closeStatement(){
    
}
	
