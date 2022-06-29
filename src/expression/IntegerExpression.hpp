#ifndef INTEGEREXPRESSION_H
#define INTEGEREXPRESSION_H
#include <concepts>
#include "Actor.hpp"

namespace BCIEvent{
    
    /**
     * Concepts for integer expressions.
     * These can be integer values, functions which return an integer,
     * or variable names (in which case they will not be type checked at compile time)
     */

    template<typename T>
    concept ReturnsInt = std::is_convertible<std::result_of<T()>, int>::value 
    || std::is_convertible<std::result_of<T(const Actor&)>, int>::value;
    template<typename T>
    concept IntegerExpression = ReturnsInt<T> || std::convertible_to<T, int> || std::convertible_to<T, std::string>;
}


#endif
