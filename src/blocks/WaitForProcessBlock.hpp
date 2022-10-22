#ifndef PROCESSBLOCK_H
#define PROCESSBLOCK_H
#include "BCIEventApplication.hpp"
#include "Actor.hpp"
#include "Block.hpp"


namespace BCIEvent {
	class WaitForProcessBlock : public Block {
		bool _waiting = false;
	public:
		WaitForProcessBlock(Block*);
		void process();
		Block* run(Sequence& sequence);

	};
}



#endif
