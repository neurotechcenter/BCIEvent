// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef FLOATEXPRESSION_H
#define FLOATEXPRESSION_H
#include <concepts>
#include <string>
#include <type_traits>
#include "Actor.hpp"
#include "IntegerExpression.hpp"

namespace BCIEvent_N{
    
    /**
     * Concepts for general number expressions within expressions.
     * These can be float values, functions which return a floating point,
     * or variable names (in which case they will not be type checked at compile time)
     * This also includes integer expressions.
     */

    template <typename T>
    concept ReturnsNumber = std::convertible_to<std::invoke_result<T>::type, long double>
    || std::convertible_to<std::invoke_result<T, Sequence&>::type, long double>;
    
    template<typename T>
    concept NumberExpression = ReturnsNumber<T> || std::convertible_to<T, long double> || std::convertible_to<T, std::string>
    || IntegerExpression<T>; //integer expressions are a subset of float expressions


}


#endif

