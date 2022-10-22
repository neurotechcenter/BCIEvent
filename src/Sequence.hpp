#include "Block.hpp"
#include <concepts>

namespace BCIEvent {
	/**
	* An object representing a sequence of blocks running.
	* Also acts as an interface for those blocks to access the environment.
	* Holds locally-scoped variables
	*
	*
	*/
	class Sequence {
		bool running = false;
		Actor* _parentActor;
		Block* _currentBlock = nullptr;
		std::unique_ptr<EventListener> _listener; 	
		std::map<std::string, std::unique_ptr<Variable>> _variables; 
	
	public:
		Sequence(Actor*, std::unique_ptr<EventListener>);
		void update();
		


	template<typename ReqType>
        ReqType getVariable(std::string name) const{
            static_assert(std::is_convertible<ReqType, bool>::value || std::is_floating_point<ReqType>::value || std::is_integral<ReqType>::value,
        	    "Template argument for getVariable must be boolean, integral, or floating point");
            try {
                if(std::is_same<ReqType, bool>::value){
        	    return _variables.at(name)->getAsBool();
        	}
        	else if (std::is_integral<ReqType>::value){
        	    return static_cast<ReqType>(_variables.at(name)->getAsInt());
        	}
        	else{
        	    return static_cast<ReqType>(_variables.at(name)->getAsDouble());
        	}
            } catch (std::out_of_range e) {
        	return _parentActor->getVariable<ReqType>(name);
            }
        }

	template <typename SetType>
	void setVariable(std::string name, SetType value){
	    static_assert(std::is_same<SetType, bool>::value || std::is_same<SetType, Variable>::value || std::is_floating_point<SetType>::value || std::is_integral<SetType>::value,
		    "Template argument for setVariable must be Variable, boolean, integral, or floating point");
	    try {
		*_variables.at(name) = value;
	    } catch (std::out_of_range e) {
		_parentActor->setVariable(name, value);
	    }
	}
	
	template <typename T> requires std::integral<T> || std::convertible_to<T, bool>
	void setState(std::string name, T value){
	    _parentActor->setState(value);
	}

	template <typename T> requires std::integral<T> || std::convertible_to<T, bool>
	T getState(std::string name) const{
	    return _parentActor->getState<T>(name);
	}

	addVariable(bool);
	addVariable(int);
	addVariable(double);
	};
}