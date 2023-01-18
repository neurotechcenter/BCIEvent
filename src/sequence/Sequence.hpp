#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP
#include "BCIEVariable.hpp"
#include "SequenceEnvironment.hpp"
#include <concepts>
#include <tuple>
#include <queue>
#include <deque>
#include <functional>
#include "Actor.hpp"

namespace BCIEvent {
	class HeadBlock;
	class Block;
	/**
	* An object representing a sequence of blocks.
	* Also acts as an interface for those blocks to access the environment.
	* Holds locally-scoped variables
	* Can be cloned, which will generate a copy of the sequence, with newly-initialized blocks.
	*/
	
	class Sequence : public SequenceEnvironment {
		bool running = false;
		Actor* _actor;
		std::unique_ptr<HeadBlock> _head; //only used for deleting the underlying sequence of blocks when this is deleted
		Block* _currentBlock = nullptr;
		std::map<std::string, BCIEVariable> _variables;
		std::unique_ptr<Sequence> _subProcedure; //subprocedure running within this sequence
		std::map<std::string, TImer> _timers;


	public:
		Sequence(std::unique_ptr<HeadBlock> head);
		~Sequence();

		/*
		* Copying a sequence is not allowed, because I have no idea how copying of the internal sequence of blocks would work,
		* and may well could cause the entire program to explode
		* Creating multiple identical sequences is done using ProtoSequence.
		*/
		//Sequence(const Sequence&) = delete;
		//Sequence& operator=(const Sequence&) = delete;

		/*
		* Runs one block through this sequence
		* Returns false when sequence has finished
		*/
		bool update();

		void setActor(Actor* actor) { _actor = actor; }


		//methods below this point are to be called by the sequence's blocks.
		
		void addTimer(std::string name);
		Timer& getTimer(std::string name);

		void addVariable(std::string name);
		void addVariable(std::string name, BCIEValue val);

		BCIEValue getVariable(std::string name);
		void setVariable(std::string name, BCIEValue value);

		//These methods remove local variables and timers, and should never be called by user-generated code.
		//They are called by blocks generated by a SequenceBuilder at the end of a scope (interior sequence of an if, loop, or other construct)
		void removeVariable(std::string name);
		void removeTimer(std::string name);

		template <typename T> requires std::integral<T> || std::convertible_to<T, bool>
		void setState(std::string name, T value) {
			_actor->setState(value);
		}

		template <typename T> requires std::integral<T> || std::convertible_to<T, bool>
		T getState(std::string name) const {
			return _actor->getState<T>(name);
		}

		void callProcedure(std::string name, std::vector<BCIEVariable> params);

		void callBCI2000Event(std::string name, uint32_t value);

		BCIEValue callFunction(std::string name, std::vector<BCIEValue> params);

		//Methods for controlling the calling actor.
		void actorMove(double, double);
		void actorMoveTo(double, double);


	};
}
#endif