#ifndef PROTOSEQUENCE_H
#define PROTOSEQUENCE_H
#include "Protoblock.hpp"
#include "Sequence.hpp"
#include "IntegerExpression.hpp"
#include "BooleanExpression.hpp"
#include "NumberExpression.hpp"
#include "ActorUtil.hpp"

namespace BCIEvent {
	/*
	* A protoype for a sequence, which can generate an instance of type Sequence
	*/
	class ProtoSequence {
		std::vector<std::string> _parameters; //parameters for a protosequence which is a procedure
	public:
		std::vector<Protoblock*> _sequenceProto;
		/*
		* Generates a sequence from the list of prototype blocks
		*/
		Sequence* genSequence();
		Sequence* genSequence(std::vector<BCIEValue> initialValues);
		ProtoSequence() {}
		ProtoSequence(std::vector<std::string> parameters);
		~ProtoSequence();

		
		//Methods for making a sequence


		ProtoSequence& addNormal(std::function<void(Sequence&)> action);
		ProtoSequence& addTimer(double timeSeconds, std::function<void(Sequence &)> action);
		ProtoSequence& addTimer(double timeSeconds);
		ProtoSequence& addTimed(double timeSeconds);
		ProtoSequence& addWaitForProcess();
		ProtoSequence& closeStatement();

		template <BooleanExpression B>
		ProtoSequence& addIf(B condition) {
			_sequenceProto.push_back(new Protoblock(ProtoBlockType::If, getExpressionFn(condition)));
			return *this;
		}
		
		template <BooleanExpression B>
		ProtoSequence& addIfElse(B condition) {
			_sequenceProto.push_back(new Protoblock(ProtoBlockType::IfElse, getExpressionFn(condition)));
			return *this;
		}

		template <BooleanExpression B>
		ProtoSequence& addWhile(B condition) {
			_sequenceProto.push_back(new Protoblock(ProtoBlockType::While, getExpressionFn(condition)));
			return *this;
		}

		template <IntegerExpression I>
		ProtoSequence& addLoop(I loopAmt) {
			_sequenceProto.push_back(new Protoblock(ProtoBlockType::Loop, getExpressionFn(loopAmt)));
			return *this;
		}

	};
}

#endif