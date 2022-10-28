#ifndef PROTOSEQUENCE_H
#define PROTOSEQUENCE_H
#include <tuple>
#include "Sequence.hpp"
#include "IntegerExpression.hpp"

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
		enum ProtoBlockType {CloseStatement, WaitForProcess, Normal, CallEvent, If, IfElse, While, Loop, Timed, Timer};
		/*Holds type and all possible parameters, those being a void procedure(for normal blocksand timer blocks with action),
		 * a pointer to an event (for event call blocks), a boolean function(for If, IfElse and While blocks), an int function(for Loop blocks),
		 * and a duration(for timed and timer blocks)
		 * For any given block prototype, only the fields that are relevant to the block will not be null.
		 */
		typedef Protoblock = std::tuple<
			ProtoBlockType,
			std::function<void, (Sequence&)>,
			std::string,
			std::function<bool, (const Sequence&)>,
			std::function<int, (const Sequence&)>,
			std::chrono::duration<double>>;
	
		std::vector<Protoblock> _sequenceProto;
		/*
		* Generates a sequence from the list of prototype blocks
		*/
		std::unique_ptr<Sequence> genSequence();

		
		//Methods for making a sequence


		ProtoSequence& addNormal(std::function<void(Actor&)> action);
		ProtoSequence& addTimer(std::chrono::duration<double> time, std::function<void(Sequence &)> action);
		ProtoSequence& addTimer(std::chrono::duration<double> time);
		ProtoSequence& addTimed(std::chrono::duration<double> time);
		ProtoSequence& addEventCaller(std::string eventName);
		ProtoSequence& addWaitForProcess();
		ProtoSequence& closeStatement();

		template <BooleanExpression B>
		ProtoSequence& addIf(B condition) {
			_sequenceProto.emplace_back(If, nullptr, nullptr, getExpressionFn(condition), nullptr, nullptr);
			return *this;
		}
		
		template <BooleanExpression B>
		ProtoSequence& addIfElse(B condition) {
			_sequenceProto.emplace_back(IfElse, nullptr, nullptr, getExpressionFn(condition), nullptr, nullptr);
			return *this;
		}

		template <BooleanExpression B>
		ProtoSequence& addWhile(B condition) {
			_sequenceProto.emplace_back(While, nullptr, nullptr, getExpressionFn(condition), nullptr, nullptr);
			return *this;
		}

		template <IntegerExpression I>
		ProtoSequence& addLoop(I loopAmt) {
			_sequenceProto.emplace_back(Loop, nullptr, nullptr, nullptr, getExpressionFn(loopAmt), nullptr);
			return *this;
		}

	};
}

#endif