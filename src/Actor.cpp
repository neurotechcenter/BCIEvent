#include "Actor.hpp"
#include "Event.hpp"

using namespace BCIEvent;

    void Actor::update(){

	//Run and update blocks
	
	std::vector<Block*> toRemove;
	toRemove.reserve(_currentBlocks.size());
	for(auto i = _currentBlocks.begin(); i != _currentBlocks.end(); i++){
	    Block* currentBlock = *i;
	    Block* nextBlock = currentBlock->run(); //runs the block and gets a reference to the next block
	    if (nextBlock == nullptr){ //remove end blocks
		toRemove.push_back(currentBlock);
	    } else {
		_currentBlocks.erase(i);
		_currentBlocks.insert(i, nextBlock);
	    }
	}
	for (int i = 0; i < toRemove.size(); i++){ //remove end blocks
		    _currentBlocks.remove(toRemove[i]);
	}

	//Handle events
	
	for (EventListener* listener : _eventListeners){
	    if (listener->isTriggered()){
		_currentBlocks.push_back(listener->getNext());
	    }
	}
    }


Actor::~Actor(){
    for (EventListener* listener : _eventListeners){
	delete listener; //deleting an event listener deletes all blocks after it.
    }
}
