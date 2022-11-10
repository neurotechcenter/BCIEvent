#include "ProtoSequence.hpp"
#include "SequenceBuilder.hpp"
#include "BooleanExpression.hpp"
#include "ActorUtil.hpp"
using namespace BCIEvent;


ProtoSequence& ProtoSequence::addNormal(std::function<void(Sequence&)> action) {
	_sequenceProto.emplace_back(ProtoBlockType::Normal, action);
	return *this;
}

ProtoSequence& ProtoSequence::addTimer(double timeSeconds, std::function<void(Sequence&)> action) {
	_sequenceProto.emplace_back(ProtoBlockType::Timer, time, action);
	return *this;
}

ProtoSequence& ProtoSequence::addTimer(double timeSeconds) {
	_sequenceProto.emplace_back(ProtoBlockType::Timer, time);
	return *this;
}

ProtoSequence& ProtoSequence::addTimed(double timeSeconds) {
	_sequenceProto.emplace_back(ProtoBlockType::Timed, time);
	return *this;
}

ProtoSequence& ProtoSequence::addWaitForProcess() {
	_sequenceProto.emplace_back(ProtoBlockType::WaitForProcess);
	return *this;
}

ProtoSequence& ProtoSequence::closeStatement() {
	_sequenceProto.emplace_back(ProtoBlockType::CloseStatement);
	return *this;
}


std::unique_ptr<Sequence> ProtoSequence::genSequence() {
	SequenceBuilder builder = SequenceBuilder();
	for (Protoblock const& b : _sequenceProto) {
		switch (b.type) {
		case ProtoBlockType::CloseStatement:
			builder.closeStatement();
			break;
		case ProtoBlockType::WaitForProcess:
			builder.addWaitForProcessBlock();
			break;
		case ProtoBlockType::Normal:
			builder.addNormalBlock(b.action);
			break;
		case ProtoBlockType::If:
			builder.addIfBlock(b.condition);
			break;
		case ProtoBlockType::IfElse:
			builder.addIfElseBlock(b.condition);
			break;
		case ProtoBlockType::While:
			builder.addWhileLoopBlock(b.condition);
			break;
		case ProtoBlockType::Loop:
			builder.addLoopBlock(b.number);
			break;
		case ProtoBlockType::Timer:
			if (b.action) {
				builder.addTimerBlock(b.time, b.action);
				break;
			}
			builder.addTimerBlock(b.time);
			break;
		case ProtoBlockType::Timed:
			builder.addTimedBlock(b.time);
			break;
		}
	}
	return std::make_unique<Sequence>(builder.getSequenceStart());
}

