// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef PROTOSEQUENCE_H
#define PROTOSEQUENCE_H
#include "Protoblock.hpp"
#include "Sequence.hpp"
#include "Expression.hpp"

namespace BCIEvent_N {
	/*
	* A protoype for a sequence, which can generate an instance of type Sequence
	*/
	class ProtoSequence {
		std::vector<std::string> _parameters; //parameters for a protosequence which is a procedure
		std::vector<std::unique_ptr<Protoblock>> _sequenceProto;
	public:
		/*
		* Generates a sequence from the list of prototype blocks
		*/
		std::unique_ptr<Sequence> genSequence();
		std::unique_ptr<Sequence> genSequence(std::vector<BCIEValue> initialValues);
		ProtoSequence() {}
		ProtoSequence(std::vector<std::string> parameters);
		ProtoSequence(const ProtoSequence&);
		ProtoSequence(ProtoSequence&&);

		
		//Methods for making a sequence


		ProtoSequence& addNormal(std::function<void(Sequence&)> action);
		ProtoSequence& addTimer(double timeSeconds, std::function<void(Sequence &)> action);
		ProtoSequence& addTimer(double timeSeconds);
		ProtoSequence& addTimed(double timeSeconds);
		ProtoSequence& addWaitForProcess();
		ProtoSequence& closeStatement();

		ProtoSequence& addIf(BooleanExpression cond) {
			_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::If, cond)));
			return *this;
		}

		ProtoSequence& addIfElse(BooleanExpression condition) {
			_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::IfElse, condition)));
			return *this;
		}

		ProtoSequence& addWhile(BooleanExpression condition) {
			_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::While, condition)));
			return *this;
		}

		ProtoSequence& addLoop(IntegerExpression loopAmt) {
			_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::Loop, loopAmt)));
			return *this;
		}

	};
}

#endif
