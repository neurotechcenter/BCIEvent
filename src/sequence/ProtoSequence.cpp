// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#include "ProtoSequence.hpp"
#include "SequenceBuilder.hpp"
#include "HeadBlock.hpp"
using namespace BCIEvent_N;

ProtoSequence::ProtoSequence(std::vector<std::string> params) {
	for (auto&& p : params) {
	    _parameters.push_back(p);
	}
}

ProtoSequence::ProtoSequence(const ProtoSequence& other) {
	_parameters = other._parameters;
	for (const std::unique_ptr<Protoblock>& block : other._sequenceProto) {
		_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(*block))); //copy blocks from other sequence
	}
}

ProtoSequence::ProtoSequence(ProtoSequence&& other) {
	_parameters = other._parameters;
	for (auto&& block : other._sequenceProto) {
		_sequenceProto.push_back(std::move(block));
	}
}

ProtoSequence& ProtoSequence::addNormal(std::function<void(Sequence&)> action) {
	_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::Normal, action)));
	return *this;
}

ProtoSequence& ProtoSequence::addTimer(double timeSeconds, std::function<void(Sequence&)> action) {
	_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::Timer_m, timeSeconds, action)));
	return *this;
}

ProtoSequence& ProtoSequence::addTimer(double timeSeconds) {
	_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::Timer_m, timeSeconds)));
	return *this;
}

ProtoSequence& ProtoSequence::addTimed(double timeSeconds) {
	_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::Timed, timeSeconds)));
	return *this;
}

ProtoSequence& ProtoSequence::addWaitForProcess() {
	_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::WaitForProcess)));
	return *this;
}

ProtoSequence& ProtoSequence::closeStatement() {
	_sequenceProto.push_back(std::move(std::make_unique<Protoblock>(ProtoBlockType::CloseStatement)));
	return *this;
}

std::unique_ptr<Sequence> ProtoSequence::genSequence(std::vector<BCIEValue> parameter_values) {
	if (parameter_values.size() != _parameters.size()) {
		throw std::logic_error("genSequence called on procedure sequence with incorrect number of parameter values");
	}
	auto seq = genSequence();
	for (int i = 0; i < _parameters.size(); i++) {
		seq->addVariable(_parameters[i], parameter_values[i]);
	}
	return seq;
}


std::unique_ptr<Sequence> ProtoSequence::genSequence() {
	if (!_parameters.empty()) {
		throw std::logic_error("genSequence called without initial values for this sequences parameters. This would be caused by a sequence intended to be a procedure mistakenly being interpreted as an event response.");
	}
	SequenceBuilder builder = SequenceBuilder();
	for (auto& b : _sequenceProto) {
		switch (b->type) {
		case ProtoBlockType::CloseStatement:
			builder.closeStatement();
			break;
		case ProtoBlockType::WaitForProcess:
			builder.addWaitForProcessBlock();
			break;
		case ProtoBlockType::Normal:
			builder.addNormalBlock(b->action);
			break;
		case ProtoBlockType::If:
			builder.addIfBlock(b->condition);
			break;
		case ProtoBlockType::IfElse:
			builder.addIfElseBlock(b->condition);
			break;
		case ProtoBlockType::While:
			builder.addWhileLoopBlock(b->condition);
			break;
		case ProtoBlockType::Loop:
			builder.addLoopBlock(b->number);
			break;
		case ProtoBlockType::Timer_m:
			if (b->action) {
				builder.addTimerBlock(b->time, b->action);
				break;
			}
			builder.addTimerBlock(b->time);
			break;
		case ProtoBlockType::Timed:
			builder.addTimedBlock(b->time);
			break;
		}
	}
	return std::make_unique<Sequence>(builder.getSequenceStart());
}


