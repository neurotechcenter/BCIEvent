#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP
#include "BCIEVariable.hpp"
#include <concepts>
#include <tuple>
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
	class Sequence {
		bool running = false;
		Actor* _actor;
		HeadBlock* _head; //only used for deleting the underlying sequence of blocks when this is deleted
		Block* _currentBlock = nullptr;
		std::map<std::string, BCIEVariable> _variables;
		std::unique_ptr<Sequence> _subProcedure; //subprocedure running within this sequence


	public:
		Sequence(HeadBlock* head);
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


		void addVariable(std::string name);
		void addVariable(std::string name, BCIEVariable val);

		//methods below this point are to be called by the sequence's blocks.
		//Get and set local variables
		BCIEVariable getVariable(std::string name) {
			try {
				return _variables.at(name);
			}
			catch (std::out_of_range) {
				return _actor.getVariable(name);
			}
		}

		template <typename SetType>
		void setVariable(std::string name, SetType value) { //no need for type checking here, the variant type will handle that on its own
			try {
				_variables.at(name) = value;
			}
			catch (std::out_of_range e) {
				_actor->setVariable(name, value);
			}
		}

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