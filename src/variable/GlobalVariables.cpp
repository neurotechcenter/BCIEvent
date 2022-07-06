#include "GlobalVariables.hpp"
#include "variable/Variable.hpp"
#include <string>
#include <stdexcept>
#include <type_traits>

using namespace BCIEvent;

void GlobalVariables::addVariable(Variable var){
    _vars.insert(std::pair<std::string, std::unique_ptr<Variable>> (var.name(), std::unique_ptr<Variable>(&var)));
}



