#include "WaitForProcessBlock.hpp"
#include "ProcessEvent.hpp"

using namespace BCIEvent;

WaitForProcessBlock::WaitForProcessBlock(Block* previous) : Block(previous) {
	ProcessEvent::getInstance()->addWaitForProcess(this);
}

void WaitForProcessBlock::process() {
	_waiting = false;
}

Block* WaitForProcessBlock::run(Sequence& sequence) {
	if (_waiting) {
		return this;
	}
	else {
		_waiting = true;
		return _next;
	}
}