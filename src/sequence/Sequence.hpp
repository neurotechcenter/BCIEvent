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
		std::map<std::string, std::unique_ptr<BCIEVariable>> _variables;
		std::unique_ptr<Sequence> _subProcedure; //subprocedure running within this sequence


	public:
		Sequence(HeadBlock* head);
		~Sequence();

		/*
		* Copying a sequence is not allowed, because I have no idea how copying of the internal sequence of blocks would work,
		* and may well could cause the entire program to explode
		* Creating multiple identical sequences is done using ProtoSequence.
		*/
		Sequence(const Sequence&) = delete;
		Sequence& operator=(const Sequence&) = delete;

		/*
		* Runs one block through this sequence
		* Returns false when sequence has finished
		*/
		bool update();

		void setActor(Actor* actor) { _actor = actor; }



		//Get and set local variables
		template<typename ReqType>
		ReqType getVariable(std::string name) const {
			static_assert(std::is_convertible<ReqType, bool>::value || std::is_floating_point<ReqType>::value || std::is_integral<ReqType>::value,
				"Template argument for getVariable must be boolean, integral, or floating point");
			try {
				if (std::is_same<ReqType, bool>::value) {
					return _variables.at(name)->getAsBool();
				}
				else if (std::is_integral<ReqType>::value) {
					return static_cast<ReqType>(_variables.at(name)->getAsInt());
				}
				else {
					return static_cast<ReqType>(_variables.at(name)->getAsDouble());
				}
			}
			catch (std::out_of_range e) {
				return _actor->getVariable<ReqType>(name);
			}
		}

		template <typename SetType>
		void setVariable(std::string name, SetType value) {
			static_assert(std::is_same<SetType, bool>::value || std::is_same<SetType, BCIEVariable>::value || std::is_floating_point<SetType>::value || std::is_integral<SetType>::value,
				"Template argument for setVariable must be Variable, boolean, integral, or floating point");
			try {
				*(_variables.at(name)) = value;
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

		void addVariable(std::unique_ptr<BCIEVariable>);


		//Methods for controlling the calling actor.
		void actorMove(double, double);
		void actorMoveTo(double, double);


	};
}
#endif