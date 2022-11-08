#include "GlobalVariables.hpp"
#include "BCIEVariable.hpp"
#include <string>
#include <stdexcept>
#include <type_traits>

using namespace BCIEvent;

void GlobalVariables::addVariable(std::unique_ptr<BCIEVariable> var){
    _vars.insert(std::pair<std::string, std::unique_ptr<BCIEVariable>> (var->name(), std::move(var)));
}



