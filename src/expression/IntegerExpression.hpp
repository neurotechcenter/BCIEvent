// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef INTEGEREXPRESSION_H
#define INTEGEREXPRESSION_H
#include <concepts>
#include<type_traits>
#include "Actor.hpp"

namespace BCIEvent_N{
    
    /**
     * Concepts for integer expressions within blocks.
     * These can be integer values, functions which return an integer,
     * or variable names (in which case they will not be type checked at compile time)
     */

    template<typename T>
    concept ReturnsInt = std::convertible_to<std::invoke_result<T>::type, int> 
    || std::convertible_to<std::invoke_result<T, Sequence&>::type, int>;
    template<typename T>
    concept IntegerExpression = ReturnsInt<T> || std::convertible_to<T, int> || std::convertible_to<T, std::string>;
}


#endif

