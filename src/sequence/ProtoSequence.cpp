#include "ProtoSequence.hpp"
using namespace BCIEvent;

ProtoSequence& ProtoSequence::addNormal(std::function<void(Sequence&)>* action) {
	_sequenceProto.emplace_back(ProtoSequence::Normal, action, nullptr, nullptr, nullptr, nullptr);
	return *this;
}

ProtoSequence& ProtoSequence::addTimer(double timeSeconds, std::function<void(Sequence&)>* action) {
	_sequenceProto.emplace_back(ProtoSequence::Timer, action, nullptr, nullptr, nullptr, time);
	return *this;
}

ProtoSequence& ProtoSequence::addTimer(double timeSeconds) {
	_sequenceProto.emplace_back(ProtoSequence::Timer, nullptr, nullptr, nullptr, nullptr, time);
	return *this;
}

ProtoSequence& ProtoSequence::addTimed(double timeSeconds) {
	_sequenceProto.emplace_back(ProtoSequence::Timer, nullptr, nullptr, nullptr, nullptr, time);
	return *this;
}

ProtoSequence& ProtoSequence::addEventCaller(std::string* name) {
	_sequenceProto.emplace_back(ProtoSequence::CallEvent, nullptr, name, nullptr, nullptr, nullptr);
	return *this;
}

ProtoSequence& ProtoSequence::addWaitForProcess() {
	_sequenceProto.emplace_back(ProtoSequence::WaitForProcess, nullptr, nullptr, nullptr, nullptr, nullptr);
	return *this;
}

ProtoSequence& ProtoSequence::closeStatement() {
	_sequenceProto.emplace_back(ProtoSequence::CloseStatement, nullptr, nullptr, nullptr, nullptr, nullptr);
	return *this;
}

std::unique_ptr<Sequence> ProtoSequence::genSequence() {
	auto builder = new SequenceBuilder()
	for (Protoblock const& b : _sequenceProto) {
		switch *b.type {
		case ProtoBlockType::CloseStatement:
			builder.closeStatement();
			break;
		case ProtoBlockType::WaitForProcess:
			builder.addWaitForProcessBlock();
			break;
		case ProtoBlockType::Normal:
			builder.addNormalBlock(*b.action);
			break;
		case ProtoBlockType::CallEvent:
			builder.addEventCallerBlock(*b.eventName); //TODO: redo how events work because not all sequences need events
			break;
		case ProtoBlockType::If:
			builder.addIfBlock(*b.condition);
			break;
		case ProtoBlockType::IfElse:
			builder.addIfElseBlock(*b.condition);
			break;
		case ProtoBlockType::While:
			builder.addWhileLoopBlock(*b.condition);
			break;
		case ProtoBlockType::Loop:
			builder.addLoopBlock(*b.number);
			break;
		case ProtoBlockType::Timer:
			if (b.action) {
				builder.addTimerBlock(*b.time, *b.action);
				break;
			}
			builder.addTimerBlock(*b.time);
			break;
		case ProtoBlockType::Timed:
			builder.addTimedBlock(*b.time);
			break;
		}
	}
	return std::make_unique<Sequence>(builder.getSequenceStart());
}

