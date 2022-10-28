#include "AppInitInclude.hpp"


void BCIEvent::BCIEventApplication::InitBCIEvent(){
    addState("aState", BCIState::u32);
    addActor(std::unique_ptr<Actor>(makeActor()
        .addVariable(std::make_unique<NumberVariable>("var2"))
        .addEventListener((std::make_unique<EventListener>(
            ProtoSequence()
            .addWaitForProcessBlock()
            .addLoop
            .addNormalBlock([](Sequence& callingSeq) {callingSeq.})
            .addTimerBlock(std::chrono::seconds(0.2))
            )
        ))
    );
}
