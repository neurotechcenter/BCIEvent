#include "BCIEventApplication.hpp"
#include "BCIState.hpp"
#include "BoolVariable.hpp"
#include "SequenceBuilder.hpp"
#include <chrono>

void BCIEvent::BCIEventApplication::InitBCIEvent(){
    addState("aState", BCIState::u32);
    Actor* actor1 = &makeActor()
        ->addVariable(std::move(std::make_unique<NumberVariable>("var2")))
        .addEventListener(SequenceBuilder(this)
            .addWaitForProcessBlock()
            .addNormalBlock([](Actor& callingActor) {callingActor.randomCostume()})
            .addTimerBlock(std::chrono::seconds(0.2))
            .getSequence());
    addActor(std::unique_ptr<Actor>(actor1));	
}
