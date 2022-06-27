#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "Variable.hpp"
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace BCIEvent{
    class GlobalVariables{
	std::map<std::string, std::unique_ptr<Variable>> _vars;
	public:
	void addVariable(Variable var);
	template<typename T>
	T getVariable(std::string name);
	template<typename T>
	void setVariable(std::string name, T value);
    };
}

#endif
