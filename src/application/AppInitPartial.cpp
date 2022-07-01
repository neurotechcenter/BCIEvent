#include "BCIEventApplication.hpp"
#include "BCIState.hpp"
#include "BoolVariable.hpp"
#include "SequenceBuilder.hpp"
#include <chrono>

void BCIEvent::BCIEventApplication::InitBCIEvent(){
    addState("aState", BCIState::u32);
    addActor(makeActor()
    ->addVariable(BoolVariable("testVar"))
    .addVariable(BoolVariable("antiTestVar"))
    .addEventListener(SequenceBuilder()
	.addLoopBlock(20)
	.addIfBlock("testVar")
	.addNormalBlock([](Actor& callingActor){ callingActor.setPositionX(25); callingActor.setPositionY(200); })
	.addNormalBlock([](Actor& callingActor) { callingActor.setVariable("antiTestVar", true); })
	.closeStatement()
	.addNormalBlock([](Actor& callingActor){ callingActor.setPositionX(0); callingActor.setPositionY(-100); })
	.addNormalBlock([](Actor& callingActor) { callingActor.setVariable("antiTestVar", false); })
	.closeStatement()
	.addNormalBlock([](Actor& callingActor){ callingActor.setVariable("testVar", callingActor.getVariable<bool>("antiTestVar")); })
	.addTimerBlock(std::chrono::milliseconds(500))
	.addNormalBlock([](Actor& callingActor){ callingActor.setState("aState", callingActor.getState<int>("aState")); })
	.closeStatement()
	.getSequence())
	    );
}
