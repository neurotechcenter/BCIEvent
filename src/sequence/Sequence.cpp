#include "Sequence.hpp"
#include "Actor.hpp"
#include "EventListener.hpp"
#include "SequenceBuilder.hpp"
#include "Block.hpp"
#include "BCIEvent.h"
#include "HeadBlock.hpp"


using namespace BCIEvent;

Sequence::Sequence(HeadBlock* head) {
	_head = head;
	_currentBlock = static_cast<Block*>(head);
}

Sequence::~Sequence() {
	delete _head; //deleting the head of a sequence of blocks will sequentially delete all other blocks in the sequence.
}

bool Sequence::update() {
	if (_subProcedure) { //if there is a subprocedure currently running
		if (_subProcedure->update()) {
			return true; 
		}
		else {
			_subProcedure.reset(); //subprocedure has terminated, continue on to main procedure 
		}
	}
	_currentBlock = _currentBlock->run(*this);
	//Check for a next block occurs after run, to avoid the extraneous cycle that would be caused by checking beforehand
	//This is why sequences ending with an EndBlock is important, as otherwise the sequence would be deleted before the effect
	//of any block called at the end of the sequence could take effect
	if (!_currentBlock) { //End block's run() method returns a nullptr
		return false; //This sequence has finished, return false;
	}
	return true; //current block has run and next block exists; return true
}

void Sequence::addVariable(std::string name) {
	_variables.insert(name, std::nullopt);
}

void Sequence.addVariable(std::string name, BCIEValue value) {
	_variables.insert(name, value);
}

void Sequence::callBCI2000Event(std::string name, uint32_t value) {
	bcievent << name << " " << value;
}

void Sequence::callProcedure(std::string name, std::vector<BCIEValue> params) {
	_subprocedure = std::unique_ptr<Sequence>(_actor.getProcedure());
}

BCIEValue Sequence::callFunction(std::string name, std::vector<BCIEValue> params) {
	return _actor.callFunction(name, *this, params);
}

void Sequence::actorMoveTo(double x, double y) {
	_actor->setPositionX(x);
	_actor->setPositionY(y);
}

void Sequence::actorMove(double x, double y) {
	_actor->setPositionX(_actor->positionX() + x);
	_actor->setPositionY(_actor->positionY() + y);
}

