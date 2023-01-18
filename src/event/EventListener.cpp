#include "EventListener.hpp"
#include "Event.hpp"
#include <exception>
using namespace BCIEvent_N;

EventListener::EventListener(ProtoSequence seq) {
    _seq = seq;
}

std::unique_ptr<Sequence> EventListener::getSequence() {
    if (_timesTriggered == 0) {
        throw std::logic_error(std::string("EventListener::getNext() called on untriggered event listener.")
            + std::string(" This should never happen. If no modifications have been made to the source code outside of AppInitPartial.cpp, submit a bug report."));
    }
    _timesTriggered--;
    return _seq.genSequence();
}
