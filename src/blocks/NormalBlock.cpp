#include "NormalBlock.hpp"
#include <functional>

using namespace BCIEvent;

NormalBlock::NormalBlock(Block* prev, std::function<void()> action) : Block(prev){
    _action = action;
} 

Block* NormalBlock::run(Actor &callingActor){
    _action();
    return _next;
}
