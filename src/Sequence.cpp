#include "Sequence.hpp"
#include "Actor.hpp"
#include "EventListener.hpp"


using namespace BCIEvent;

Sequence::Sequence(Actor* actor, std::unique_ptr<EventListener> listener) {
	_parentActor = actor;
	_listener = std::move(listener);
}

Sequence::update() {
	if (_listener->isTriggered()) {
		_currentBlock = _listener->getNext();
	}
	if (_currentBlock) {
		_currentBlock = _currentBlock->run();
	}
}

