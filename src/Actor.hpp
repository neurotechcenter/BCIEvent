#ifndef ACTOR_H
#define ACTOR_H
#include <vector>
#include "EventListener.hpp"
#include <list>

namespace BCIEvent{
    class Actor{
	std::vector<EventListener*> _eventListeners; 	

	/**
	 * List of currently executing blocks.
	 */
	std::list<Block*> _currentBlocks;
	public:

	/**
	 * Main update function: called once every cycle of the main loop.
	 * Runs blocks and handles events.
	 */
	void update();

	~Actor();
    };
}


#endif
