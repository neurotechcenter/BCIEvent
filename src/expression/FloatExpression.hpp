#ifndef FLOATEXPRESSION_H
#define FLOATEXPRESSION_H
#include <concepts>
#include <string>
#include <type_traits>
#include "Actor.hpp"
#include "IntegerExpression.hpp"

namespace BCIEvent{
    
    /**
     * Concepts for floating point expressions.
     * These can be float values, functions which return a floating point,
     * or variable names (in which case they will not be type checked at compile time)
     */

    template <typename T>
    concept ReturnsFloat = std::is_convertible<std::result_of<T()>, long double>::value
    || std::is_convertible<std::result_of<T(const Actor&)>, long double>::value;
    
    template<typename T>
    concept FloatExpression = ReturnsFloat<T> || std::convertible_to<T, long double> || std::convertible_to<T, std::string>
    || IntegerExpression<T>; //integer expressions are a subset of float expressions


}


#endif
