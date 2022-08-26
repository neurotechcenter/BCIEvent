#include "BCIEventApplication.hpp"
#include "BCIState.hpp"
#include "BoolVariable.hpp"
#include "SequenceBuilder.hpp"
#include <chrono>

void BCIEvent::BCIEventApplication::InitBCIEvent(){
    addState("aState", BCIState::u32);
    Actor* actor1 = &makeActor()
    ->addVariable(std::move(std::make_unique<BoolVariable>("testVar")))
    .addVariable(std::move(std::make_unique<BoolVariable>("antiTestVar")))
    .addGraphic("redthing.png", false)
    .addEventListener(SequenceBuilder(this)
	.addNormalBlock([&](Actor& callingActor){ bciout << "Amogus"; })
	.addNormalBlock([&](Actor& callingActor){ State("aState") = 85; })
	.addLoopBlock(20)
	.addIfElseBlock("testVar")
	.addNormalBlock([](Actor& callingActor){ callingActor.setPositionX(25); callingActor.setPositionY(200); })
	.addNormalBlock([](Actor& callingActor) { callingActor.setVariable("antiTestVar", true); })
	.addNormalBlock([](Actor& callingActor) { printf("a"); })
	.closeStatement()
	.addNormalBlock([](Actor& callingActor){ callingActor.setPositionX(0); callingActor.setPositionY(-100); })
	.addNormalBlock([](Actor& callingActor) { callingActor.setVariable("antiTestVar", false); })
	.closeStatement()
	.addNormalBlock([](Actor& callingActor){ callingActor.setVariable("testVar", callingActor.getVariable<bool>("antiTestVar")); })
	.addTimerBlock(std::chrono::milliseconds(500))
	//.addNormalBlock([](Actor& callingActor){ callingActor.setState("aState", callingActor.getState<int>("aState") + 1); })
	.closeStatement()
	.getSequence());
    addActor(std::unique_ptr<Actor>(actor1));	
}
