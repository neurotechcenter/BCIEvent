set(SOURCES_EVENT
  	src/application/BCIEventApplication.cpp
	src/actor/Actor.cpp
	src/application/AppInitPartial.cpp
	src/blocks/EndBlock.cpp
	src/blocks/HeadBlock.cpp
	src/blocks/IfBlock.cpp
	src/blocks/IfElseBlock.cpp
	src/blocks/LoopBlock.cpp
	src/blocks/NormalBlock.cpp
	src/blocks/StatementCloseNormalBlock.cpp
	src/blocks/TimedBlock.cpp
	src/blocks/TimerBlock.cpp
	src/blocks/WhileLoopBlock.cpp
	src/blocks/WaitForProcessBlock.cpp
	src/sequence/SequenceBuilder.cpp
	src/sequence/Sequence.cpp
	src/sequence/ProtoSequence.cpp
	src/state/BCIState.cpp
	src/event/EventListener.cpp
	src/event/Event.cpp
	src/event/ProcessEvent.cpp
    )
set(INCLUDE_EVENT 
    src
	src/actor
    src/blocks
    src/event
    src/sequence
    src/variable
    src/state
	src/timer
    src/expression
    src/application
	src/param
)
