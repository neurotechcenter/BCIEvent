#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "BCIEVariable.hpp"
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace BCIEvent{
    class GlobalVariables{
	std::map<std::string, std::unique_ptr<BCIEVariable>> _vars;
	public:
	void addVariable(std::unique_ptr<BCIEVariable> var);

	template<typename ReqType>
	ReqType getVariable(std::string name) const{
	    static_assert(std::is_same<ReqType, bool>::value || std::is_floating_point<ReqType>::value || std::is_integral<ReqType>::value,
		    "Template argument for getVariable must be boolean, integral, or floating point");
	    try {
	        if(std::is_same<ReqType, bool>::value){
		    return _vars.at(name)->getAsBool();
		}
		else if (std::is_integral<ReqType>::value){
		    return static_cast<ReqType>(_vars.at(name)->getAsInt());
		}
		else{
		    return static_cast<ReqType>(_vars.at(name)->getAsDouble());
		}
	    } catch (std::out_of_range e) {
		throw std::out_of_range("Variable " + name + " not found locally or globally");
	    }
	}

	template <typename SetType>
	void setVariable(std::string name, SetType value){
	    static_assert(std::is_same<SetType, bool>::value || std::is_same<SetType, BCIEVariable>::value || std::is_floating_point<SetType>::value || std::is_integral<SetType>::value,
		    "Template argument for setVariable must be boolean, integral, or floating point");
	    try {
		*_vars.at(name) = value;
	    } catch (std::out_of_range e) {
		throw std::out_of_range("Could not find variable " + name + " locally or globally");
	    }
	}
    };
}

#endif
