// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "Sequence.hpp"
#include "Actor.hpp"
#include "EventListener.hpp"
#include "SequenceBuilder.hpp"
#include "Block.hpp"
#include "BCIEvent.h"
#include "HeadBlock.hpp"


using namespace BCIEvent_N;

Sequence::Sequence(HeadBlock* head) {
	_head = head;
	_currentBlock = static_cast<Block*>(_head);
}

Sequence::~Sequence() {
	delete _head;
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

void Sequence::addTimer(std::string name) {
	_timers.insert(std::make_pair(name, Timer()));
}

Timer& Sequence::getTimer(std::string name) {
	try {
		return _timers.at(name);
	}
	catch (std::out_of_range) {
		return _actor->getTimer(name);
	}
}

void Sequence::addVariable(std::string name) {
	_variables.insert(std::make_pair(name, std::nullopt));
}

void Sequence::addVariable(std::string name, BCIEValue value) {
	_variables.insert(std::make_pair(name, value));
}

void Sequence::setVariable(std::string name, BCIEValue val) {
	try {
		_variables.at(name) = val;
	}
	catch (std::out_of_range) {
		_actor->setVariable(name, val);
	}
}

BCIEValue Sequence::getVariable(std::string name){
	try {
		return _variables.at(name);
	}
	catch (std::out_of_range) {
		return _actor->getVariable(name);
	}
}

void Sequence::removeVariable(std::string name) {
	_variables.erase(name);
}

void Sequence::removeTimer(std::string name) {
	_timers.erase(name);
}



void Sequence::callBCI2000Event(std::string name, uint32_t value) {
	::bcievent << name << " " << value;
}

void Sequence::callProcedure(std::string name, std::vector<BCIEValue> params) {
	_subProcedure = _actor->getProcedure(name, params);
}

BCIEValue Sequence::callFunction(std::string name, std::vector<BCIEValue> params) {
	return _actor->callFunction(name, params);
}

void Sequence::actorMoveTo(double x, double y) {
	_actor->setPositionX(x);
	_actor->setPositionY(y);
}

void Sequence::actorMove(double x, double y) {
	_actor->setPositionX(_actor->positionX() + x);
	_actor->setPositionY(_actor->positionY() + y);
}


void Sequence::actorChangeGraphic(int graphic) {
	_actor->changeGraphic(graphic);
}

