#include "ProtoSequence.hpp"
using namespace BCIEvent;



std::unique_ptr<Sequence> ProtoSequence::genSequence() {
	auto builder = new SequenceBuilder()
	for (Protoblock const& b : _sequenceProto) {
		switch std::get<0>(b) {
		case ProtoBlockType::End:
			builder.addEndBlock();
			break;
		case ProtoBlockType::CloseStatement:
			builder.closeStatement();
			break;
		case ProtoBlockType::WaitForProcess:
			builder.addWaitForProcessBlock();
			break;
		case ProtoBlockType::Normal:
			builder.addNormalBlock(std::get<1>(b));
			break;
		case ProtoBlockType::CallEvent:
			builder.addEventCallerBlock(std::get<2>(b)); //TODO: redo how events work because not all sequences need events
			break;
		case ProtoBlockType::If:
			builder.addIfBlock(std::get<3>(b));
			break;
		case ProtoBlockType::IfElse:
			builder.addIfElseBlock(std::get<3>(b));
			break;
		case ProtoBlockType::While:
			builder.addWhileLoopBlock(std::get<3>(b));
			break;
		case ProtoBlockType::Loop:
			builder.addLoopBlock(std::get<4>(b));
			break;
		case ProtoBlockType::Timer:
			if (std::get<1>(b)) {
				builder.addTimerBlock(std::get<5>(b), std::get<1>(b));
				break;
			}
			builder.addTimerBlock(std::get<1>(b));
			break;
		case ProtoBlockType::Timed:
			builder.addTimedBlock(std::get<5>(b));
			break;
		}
	}
	return std::make_unique<Sequence>(builder.getSequence());
}

