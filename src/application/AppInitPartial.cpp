#include "AppInitInclude.hpp"

using namespace BCIEvent_N;

void BCIEvent_N::BCIEventApplication::InitBCIEvent(){
	addEvent("go");
	addEvent("buttonClicked");
	addStateEvent("timing_start");
	addStateEvent("button_clicked");
	addVariable("late", false);
	addTimer("reactionTime");
	auto button = makeActor();
	button->self()
		.addGraphic("green.png", true)
		.addGraphic("red.png", true)
		.addEventListener(std::make_unique<EventListener>(ProtoSequence()
			.addNormal([&](Sequence& callingSequence) {callingSequence.actorChangeGraphic(1);  })
			.addNormal([&](Sequence& callingSequence) {callingSequence.actorMoveTo(200, 200);  })
			.addTimer(2)
			.addNormal([&](Sequence& callingSequence) {callingSequence.callEvent("go");  })
			))
		.addEventListener("go", std::make_unique<EventListener>(ProtoSequence()
			.addNormal([&](Sequence& callingSequence) {callingSequence.callBCI2000Event("timing_start", 0); })
			.addNormal([&](Sequence& callingSequence) {callingSequence.setVariable("late", false); })
			.addNormal([&](Sequence& callingSequence) {callingSequence.getTimer("reactionTime").reset();  })
			.addNormal([&](Sequence& callingSequence) {callingSequence.setVariable("ready", true); })
			.addNormal([&](Sequence& callingSequence) {callingSequence.actorChangeGraphic(0);  })
			.addNormal([&](Sequence& callingSequence) {callingSequence.getTimer("reactionTime").start(); })
			.addTimer(1)
			.addNormal([&](Sequence& callingSequence) {callingSequence.setVariable("late", true); })
			.addNormal([&](Sequence& callingSequence) {callingSequence.callEvent("buttonClicked"); })
			))
		.addEventListener("click", std::make_unique<EventListener>(ProtoSequence()
			.addIf([&](Sequence& callingSequence) {return std::get<bool>(callingSequence.getVariable("ready")); })
			.addNormal([&](Sequence& callingSequence) {callingSequence.setVariable("ready", false); })
			.addNormal([&](Sequence& callingSequence) {callingSequence.getTimer("reactionTime").stop();  })
			.addNormal([&](Sequence& callingSequence) {callingSequence.callEvent("buttonClicked"); })
			.addNormal([&](Sequence& callingSequence) {callingSequence.callBCI2000Event("button_clicked", static_cast<int>(callingSequence.getTimer("reactionTime").time() * 1000)); })
			.closeStatement()
			.addTimer(3)
			.addNormal([&](Sequence& callingSequence) {callingSequence.callEvent("go"); })
			))
		.addVariable("ready", false);
	addActor(std::move(button));
}
