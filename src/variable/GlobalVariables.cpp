#include "GlobalVariables.hpp"
#include "variable/Variable.hpp"
#include <string>
#include <stdexcept>
#include <type_traits>

using namespace BCIEvent;

void GlobalVariables::addVariable(Variable var){
    _vars.insert(std::pair<std::string, std::unique_ptr<Variable>> (var.name(), std::unique_ptr<Variable>(&var)));
}

bool GlobalVariables::getBoolVariable(std::string name){
    try{
    return _vars.at(name)->getAsBool();
    } catch (std::out_of_range e){
    throw std::out_of_range("Variable " + name + " not found locally or globally.");
    }
}
int GlobalVariables::getIntVariable(std::string name){
    try{
    return _vars.at(name)->getAsInt();
    } catch (std::out_of_range e){
    throw std::out_of_range("Variable " + name + " not found locally or globally.");
    }
}
double GlobalVariables::getNumberVariable(std::string name){
    try{
    return _vars.at(name)->getAsDouble();
    } catch (std::out_of_range e){
    throw std::out_of_range("Variable " + name + " not found locally or globally.");
    }
}

template<typename ReqType>
ReqType GlobalVariables::getVariable(std::string name){
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
void GlobalVariables::setVariable(std::string name, SetType value){
    static_assert(std::is_same<SetType, bool>::value || std::is_same<SetType, Variable>::value || std::is_floating_point<SetType>::value || std::is_integral<SetType>::value,
	    "Template argument for setVariable must be boolean, integral, or floating point");
    try {
	_vars.at(name) = value;
    } catch (std::out_of_range e) {
	throw std::out_of_range("Could not find variable " + name + " locally or globally");
    }
}
