#include "EventListener.hpp"
#include "Event.hpp"
#include <exception>
using namespace BCIEvent;



std::unique_ptr<Sequence> EventListener::getSequence() {
    if (timesTriggered == 0) {
        throw std::logic_error("EventListener::getNext() called on untriggered event listener."
            + " This should never happen. If no modifications have been made to the source code outside of AppInitPartial.cpp, submit a bug report.");
    }
    timesTriggered--;
    return _seq.genSequence()
}
