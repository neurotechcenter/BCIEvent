#ifndef STATEMENTCLOSENORMAL_HPP
#define STATEMENTCLOSENORMAL_HPP

#include "StatementCloseBlock.hpp"

namespace BCIEvent {
	/*
	* A normal block whose next value is set to itself initally, as it is only used for deleting 
	* variables and timers as they go out of scope. As such, it is placed on the closeBlock stack and has its
	* nextblock field set after initialization.
	*/
	class StatementCloseNormalBlock : public StatementCloseBlock {
		std::function<void(Sequence&)> _action;

	public:
		StatementCloseNormalBlock(std::function<void(Sequence&)> action);

		Block* run(Sequence& callingSequence) override;

	};

}

#endif