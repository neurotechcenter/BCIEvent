#include "StatementCloseNormalBlock.hpp"

using namespace BCIEvent_N;

StatementCloseNormalBlock::StatementCloseNormalBlock(std::function<void(Sequence&)> action) {
	_action = action;
}

Block* StatementCloseNormalBlock::run(Sequence& callingSequence) {
	_action(callingSequence);
	return _next;
}