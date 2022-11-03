#include "AppInitInclude.hpp"


void BCIEvent::BCIEventApplication::InitBCIEvent(){
    addState("aState", BCIState::u32);
    addActor(std::unique_ptr<Actor>(makeActor()
        .addVariable(std::make_unique<NumberVariable>("var2"))
        .addEventListener((std::make_unique<EventListener>(
            ProtoSequence()
            .addLoop()
            .addWaitForProcess()
            .addNormalBlock([](Sequence& callingSeq) {callingSeq.actorMoveTo(100, 200); })
            .addTimerBlock(std::chrono::seconds(0.2))
            .addNormalBlock([](Sequence& callingSeq{ callingSeq.actorMoveTo(200, 200); }))
            .closeStatement();
            )
        ))
    );
}
