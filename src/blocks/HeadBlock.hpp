#ifndef HEADBLOCK_H
#define HEADBLOCK_H
#include "Block.hpp"

namespace BCIEvent{
    class HeadBlock : public Block{
	public:
	/**
	 * Because head blocks are the first block in a series, they have no previous block.
	 * However, the Block constructor expects a previous block, so the HeadBlock
	 * passes itself.
	 * This means that _next will point to itself until more blocks are added.
	 */
	HeadBlock();
	~HeadBlock();
	Block* run(Sequence &sequence);
    };
}


#endif
