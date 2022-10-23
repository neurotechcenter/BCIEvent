#ifndef INTEGEREXPRESSION_H
#define INTEGEREXPRESSION_H
#include <concepts>
#include<type_traits>
#include "Actor.hpp"

namespace BCIEvent{
    
    /**
     * Concepts for integer expressions within blocks.
     * These can be integer values, functions which return an integer,
     * or variable names (in which case they will not be type checked at compile time)
     */

    template<typename T>
    concept ReturnsInt = std::convertible_to<std::invoke_result<T>::type, int> 
    || std::convertible_to<std::invoke_result<T,const Sequence&>::type, int>;
    template<typename T>
    concept IntegerExpression = ReturnsInt<T> || std::convertible_to<T, int> || std::convertible_to<T, std::string>;
}


#endif
