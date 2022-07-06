#include "IfBlock.hpp"

using namespace BCIEvent;


Block* IfEndBlock::run(Actor &callingActor){
    return _next;
}


Block* IfStartBlock::run(Actor &callingActor){
    if (_condition( callingActor ))
	return _next;
    else
	return _endBlock;
}
