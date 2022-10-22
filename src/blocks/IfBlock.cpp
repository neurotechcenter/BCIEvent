#include "IfBlock.hpp"

using namespace BCIEvent;


Block* IfEndBlock::run(Sequence& sequence){
    return _next;
}


Block* IfStartBlock::run(Sequence& sequence){
    if (_condition( callingActor ))
	return _next;
    else
	return _endBlock;
}
