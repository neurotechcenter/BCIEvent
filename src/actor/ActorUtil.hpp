// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef ACTORUTIL_H
#define ACTORUTIL_H
#include <concepts>
#include <type_traits>
#include "Actor.hpp"

namespace BCIEvent_N{
   
    template<typename T>
    concept ExpressionType = std::convertible_to<T, bool> || std::convertible_to<T, int> || std::convertible_to<T, float>;

    template<typename T, typename U> requires ExpressionType<U> && std::same_as<std::invoke_result<T(const Sequence&)>,U>
    std::function<U ( Sequence&)> getExpressionFn(T in){
	return in; 
    }

    template<typename T, typename U> requires ExpressionType<U> && std::same_as<std::invoke_result<T()>, U>
    std::function<U ( Sequence&)> getExpressionFn(T in){
	return [&]( Sequence&){ return T(); };
    }

    template<typename T, typename U> requires std::convertible_to<T, std::string>
    std::function<U ( Sequence&)> getExpressionFn(T in){
	return [&]( Sequence& a) { return a.getVariable(in); };
    }

    template<typename T>
    std::function<T ( Sequence&)> getExpressionFn(T in){
	return [&]( Sequence&) { return in; };
    }

}

#endif

