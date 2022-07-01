#ifndef BOOLEANEXPRESSION_H
#define BOOLEANEXPRESSION_H
#include <concepts>
#include <type_traits>
#include "Actor.hpp"
#include <functional>

namespace BCIEvent{
    /**
     * Concepts for boolean expressions.
     * These can be boolean values, functions which return a boolean,
     * or variable names (in which case they will not be type checked at compile time)
     */
    template<typename T> //returns a boolean
    concept ReturnsBoolean = std::is_same<std::result_of<T()>, bool>::value 
    || std::is_same<std::result_of<T(const Actor&)>, bool>::value; 
    template <typename T>
    concept BooleanExpression = ReturnsBoolean<T> || std::convertible_to<T, bool> || std::convertible_to<T, std::string>;


}

#endif
