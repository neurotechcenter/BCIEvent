#include "AppInitInclude.hpp"


void BCIEvent::BCIEventApplication::InitBCIEvent(){
    addActor(std::unique_ptr<Actor>(&(Actor(this)
        .addVariable(std::make_unique<NumberVariable>("var2"))
        .addEventListener((std::make_unique<EventListener>(
            ProtoSequence()
            .addLoop(8)
            .addWaitForProcess()
            .addNormal([](Sequence& callingSeq){ callingSeq.actorMoveTo(100, 200); })
            .addTimer(0.2)
            .addNormal([](Sequence& callingSeq){ callingSeq.actorMoveTo(200, 200); })
            .closeStatement()
            )
        ))
    )));
}
