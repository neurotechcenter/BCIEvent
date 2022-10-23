
using namespace BCIEvent;

void ProcessEvent::trigger() {
	Event::trigger();
	for (WaitForProcessBlock& b : _processBlocks) {
		b.trigger();
	}

}

void ProcessEvent::addWaitForProcess(WaitForProcessBlock* b) {
	_processBlocks.push_back(b);
}