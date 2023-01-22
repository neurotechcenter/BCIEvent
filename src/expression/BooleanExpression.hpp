// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef BOOLEANEXPRESSION_H
#define BOOLEANEXPRESSION_H
#include <concepts>
#include <type_traits>
#include "Actor.hpp"
#include <functional>

namespace BCIEvent_N{
    /**
     * Concepts for boolean expressions within blocks.
     * These can be boolean values, functions which return a boolean,
     * or variable names (in which case they will not be type checked at compile time)
     */
    template<typename T> //returns a boolean
    concept ReturnsBoolean = std::convertible_to<std::invoke_result<T>::type, bool> 
    || std::convertible_to<std::invoke_result<T, Sequence&>::type, bool>; 
    template <typename T>
    concept BooleanExpression = ReturnsBoolean<T> || std::convertible_to<T, bool> || std::convertible_to<T, std::string>;


}

#endif

