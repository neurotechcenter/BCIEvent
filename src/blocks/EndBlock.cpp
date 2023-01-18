#include "EndBlock.hpp"
#include "Block.hpp"

using namespace BCIEvent_N;

EndBlock::EndBlock(Block* previous) : Block(previous){
    _next = nullptr;
}

EndBlock::~EndBlock() {}

Block* EndBlock::run(Sequence &sequence){return _next;}


