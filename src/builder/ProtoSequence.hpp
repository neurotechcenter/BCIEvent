#ifndef PROTOSEQUENCE_H
#define PROTOSEQUENCE_H
#include <tuple>
#include "Sequence.hpp"

namespace BCIEvent {
	/*
	* A protoype for a sequence, which can generate an instance of type Sequence
	*/
	class ProtoSequence {
		


	public:
		/*
		* These next fields are for defining a prototype sequence which is used to generate an actual sequence of blocks. This is to allow cloning of a sequence.
		* The type Protoblock essentially holds any possible block type alongside its parameters.
		* That way one object can represent any block and can be used to contruct a new instance of that block.
		* This is essentially my way of implementing some form of algebraic data type that represents any type of block.
		*/
		enum ProtoBlockType {End, CloseStatement, WaitForProcess, Normal, CallEvent, If, IfElse, While, Loop, Timed, Timer};
		/*Holds type and all possible parameters, those being a void procedure(for normal blocksand timer blocks with action),
		 * a pointer to an event (for event call blocks), a boolean function(for If, IfElse and While blocks), an int function(for Loop blocks),
		 * and a duration(for timed and timer blocks)
		 * For any given block prototype, only the fields that are relevant to the block will not be null.
		 */
		typedef Protoblock = std::tuple<ProtoBlockType,
			std::function<void, (Sequence&)>,
			std::string,
			std::function<bool, (const Sequence&)>,
			std::function<int, (const Sequence&)>,
			std::chrono::duration<double>>
	
		std::vector<Protoblock> _sequenceProto;
		/*
		* Generates a sequence from the list of prototype blocks
		*/
		std::unique_ptr<Sequence> genSequence();

		
		//Methods for making a sequence


		Sequence& addNormal(std::function<void(Actor&)> action)
		Sequence& addTimerBlock(std::chrono::duration<double> time, std::function<void(Sequence &)> action);
		Sequence& addTimerBlock(std::chrono::duration<double> time);
		Sequence& addTimedBlock(std::chrono::duration<double> time);
		Sequence& addEventCallerBlock(std::shared_ptr<Event> calledEvent);
		Sequence& addWaitForProcessBlock();

		template <BooleanExpression B>
		Sequence& addIf(B condition) {

			return *this;
		}

	};
}

#endif