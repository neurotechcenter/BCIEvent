// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef PROTOBLOCK_H
#define PROTOBLOCK_H
#include <chrono>
#include "Expression.hpp"
#include <functional>

namespace BCIEvent_N {
	class Sequence;
		/*
		 * Holds type and all possible parameters, those being a void procedure(for normal blocksand timer blocks with action),
		 * a pointer to an event (for event call blocks), a boolean function(for If, IfElse and While blocks), an int function(for Loop blocks),
		 * and a duration(for timed and timer blocks)
		 * For any given block prototype, only the fields that are relevant to the block will not be null.
		 */
	enum ProtoBlockType {CloseStatement, WaitForProcess, Normal, If, IfElse, While, Loop, Timed, Timer_m};
	class Protoblock {
	public:

		Protoblock(const Protoblock& other) :
			type(other.type),
			action(other.action),
			eventName(other.eventName),
			condition(other.condition),
			number(other.number),
			time(other.time)
		{};

		/*
		* These next fields are for defining a prototype sequence which is used to generate an actual sequence of blocks. This is to allow cloning of a sequence.
		* The type Protoblock essentially holds any possible block type alongside its parameters.
		* That way one object can represent any block and can be used to contruct a new instance of that block.
		* This is essentially my way of implementing some form of algebraic data type that represents any type of block.
		*/
		ProtoBlockType type;
		std::function<void (Sequence&)> action;
		std::string eventName;
		BooleanExpression condition;
		IntegerExpression number;
		double time = 0;

		Protoblock(ProtoBlockType _type, std::function<void(Sequence&)> _action) : type(_type), action(_action) {}
		Protoblock(ProtoBlockType _type, double _time) : type(_type), time(_time) {}
		Protoblock(ProtoBlockType _type, double _time, std::function<void(Sequence&)> _action) : type(_type), time(_time), action(_action) {}
		Protoblock(ProtoBlockType _type) : type(_type) {}
		Protoblock(ProtoBlockType _type, BooleanExpression _condition) : type(_type), condition(_condition) {}
		Protoblock(ProtoBlockType _type, IntegerExpression _number) : type(_type), number(_number) {}
	};
}


#endif
