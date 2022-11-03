#ifndef PROTOSEQUENCE_H
#define PROTOSEQUENCE_H
#include "Protoblock.hpp"
#include "Sequence.hpp"
#include "IntegerExpression.hpp"
#include "BooleanExpression.hpp"
#include "NumberExpression.hpp"

namespace BCIEvent {
	/*
	* A protoype for a sequence, which can generate an instance of type Sequence
	*/
	class ProtoSequence {
	public:
		std::vector<Protoblock> _sequenceProto;
		/*
		* Generates a sequence from the list of prototype blocks
		*/
		std::unique_ptr<Sequence> genSequence();

		
		//Methods for making a sequence


		ProtoSequence& addNormal(std::function<void(Actor&)> action);
		ProtoSequence& addTimer(double timeSeconds, std::function<void(Sequence &)> action);
		ProtoSequence& addTimer(double timeSeconds);
		ProtoSequence& addTimed(double timeSeconds);
		ProtoSequence& addEventCaller(std::string eventName);
		ProtoSequence& addWaitForProcess();
		ProtoSequence& closeStatement();

		template <BooleanExpression B>
		ProtoSequence& addIf(B condition) {
			_sequenceProto.emplace_back(Protoblock::ProtoBlockType::If, nullptr, nullptr, getExpressionFn(condition), nullptr, nullptr);
			return *this;
		}
		
		template <BooleanExpression B>
		ProtoSequence& addIfElse(B condition) {
			_sequenceProto.emplace_back(Protoblock::ProtoBlockType::IfElse, nullptr, nullptr, getExpressionFn(condition), nullptr, nullptr);
			return *this;
		}

		template <BooleanExpression B>
		ProtoSequence& addWhile(B condition) {
			_sequenceProto.emplace_back(Protoblock::ProtoBlockType::While, nullptr, nullptr, getExpressionFn(condition), nullptr, nullptr);
			return *this;
		}

		template <IntegerExpression I>
		ProtoSequence& addLoop(I loopAmt) {
			_sequenceProto.emplace_back(Protoblock::ProtoBlockType::Loop, nullptr, nullptr, nullptr, getExpressionFn(loopAmt), nullptr);
			return *this;
		}

	};
}

#endif