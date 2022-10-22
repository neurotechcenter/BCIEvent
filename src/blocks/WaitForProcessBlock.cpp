#include "WaitForProcessBlock.hpp"

using namespace BCIEvent;

WaitForProcessBlock::WaitForProcessBlock(Block* previous) : Block(previous) {}

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