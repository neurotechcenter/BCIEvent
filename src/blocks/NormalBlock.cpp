#include "NormalBlock.hpp"
#include <functional>

using namespace BCIEvent_N;

NormalBlock::NormalBlock(Block* prev, std::function<void(Sequence& sequence)> action) : Block(prev){
    _action = action;
} 

Block* NormalBlock::run(Sequence& sequence){
    _action(sequence);
    return _next;
}
