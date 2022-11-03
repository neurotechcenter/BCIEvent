#ifndef PROTOBLOCK_H
#define PROTOBLOCK_H
#include <chrono>
#include <functional>

namespace BCIEvent {
	class Sequence;
		/*
		 * Holds type and all possible parameters, those being a void procedure(for normal blocksand timer blocks with action),
		 * a pointer to an event (for event call blocks), a boolean function(for If, IfElse and While blocks), an int function(for Loop blocks),
		 * and a duration(for timed and timer blocks)
		 * For any given block prototype, only the fields that are relevant to the block will not be null.
		 */
	class Protoblock {
	public:
		/*
		* These next fields are for defining a prototype sequence which is used to generate an actual sequence of blocks. This is to allow cloning of a sequence.
		* The type Protoblock essentially holds any possible block type alongside its parameters.
		* That way one object can represent any block and can be used to contruct a new instance of that block.
		* This is essentially my way of implementing some form of algebraic data type that represents any type of block.
		*/
		enum ProtoBlockType {CloseStatement, WaitForProcess, Normal, CallEvent, If, IfElse, While, Loop, Timed, Timer};
		const ProtoBlockType type;
		const std::unique_ptr<std::function<void (Sequence&)>> action;
		const std::unique_ptr<std::string> eventName;
		const std::unique_ptr<std::function<bool (Sequence&)>> condition;
		const std::unique_ptr<std::function<int (Sequence&)>> number;
		const std::unique_ptr<std::chrono::seconds> timeSeconds;

		Protoblock(
			ProtoBlockType blockType,
			std::function<void(Sequence&)>* blockAction,
			std::string* blockEventName,
			std::function<bool(Sequence&)>* blockCondition,
			std::function<int(Sequence&)>* blockNumber,
			double blockTimeSeconds) :
			type(blockType),
			action(std::unique_ptr<std::function<void(Sequence&)>>(blockAction)),
			eventName(std::unique_ptr<std::string>(blockEventName)),
			condition(std::unique_ptr<std::function<bool(Sequence&)>>(blockCondition)),
			number(std::unique_ptr<std::function<int(Sequence&)>>(blockNumber)),
			timeSeconds(std::make_unique<std::chrono::seconds>(blockTimeSeconds)) {}
		
	};
}


#endif