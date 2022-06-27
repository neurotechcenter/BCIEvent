#include "EndBlock.hpp"
#include "Block.hpp"

using namespace BCIEvent;

EndBlock::EndBlock(Block* previous) : Block(previous){
    _next = nullptr;
}

Block* EndBlock::run(Actor &callingActor){return _next;}
