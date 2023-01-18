#include "ProcessEvent.hpp"
#include "WaitForProcessBlock.hpp"
using namespace BCIEvent_N;

void ProcessEvent::trigger() {
	for (WaitForProcessBlock* b : _processBlocks) {
		b->process();
	}

}

void ProcessEvent::addWaitForProcess(WaitForProcessBlock* b) {
	_processBlocks.push_back(b);
}