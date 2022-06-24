#include "HeadBlock.hpp"

using namespace BCIEvent;

HeadBlock::HeadBlock() : Block(&this){}
HeadBlock::~HeadBlock(){
    if (_next == this){
 //just in case this is the only block in a series, so that it doesnt try to delete itself
	_next = nullptr;
    }
}
