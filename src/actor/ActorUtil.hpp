#ifndef ACTORUTIL_H
#define ACTORUTIL_H
#include <concepts>
#include <type_traits>
#include "Actor.hpp"

namespace BCIEvent_N{
   
    template<typename T>
    concept ExpressionType = std::convertible_to<T, bool> || std::convertible_to<T, int> || std::convertible_to<T, float>;

    template<typename T, typename U> requires ExpressionType<U> && std::same_as<std::invoke_result<T(const Sequence&)>,U>
    std::function<U (const Sequence&)> getExpressionFn(T in){
	return in; 
    }

    template<typename T, typename U> requires ExpressionType<U> && std::same_as<std::invoke_result<T()>, U>
    std::function<U (const Sequence&)> getExpressionFn(T in){
	return [&](const Sequence&){ return T(); };
    }

    template<typename T, typename U> requires std::convertible_to<T, std::string>
    std::function<U (const Sequence&)> getExpressionFn(T in){
	return [&](const Sequence& a) { return a.getVariable(in); };
    }

    template<typename T>
    std::function<T (const Sequence&)> getExpressionFn(T in){
	return [&](const Sequence&) { return in; };
    }

}

#endif
