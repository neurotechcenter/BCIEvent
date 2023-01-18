#ifndef ENDBLOCK_H
#define ENDBLOCK_H
#include "Block.hpp"
namespace BCIEvent{

    /**
     * A block that is meant to be at the end of a series of blocks.
     * It is a normal block without any action but its _next is the null pointer.
     * Calling run will return a null pointer so handle it accordingly.
     */
    class EndBlock : public Block {
	public:
	EndBlock(Block* prev);
	~EndBlock();
	Block* run(Sequence &sequence) override;
    };
}
#endif
