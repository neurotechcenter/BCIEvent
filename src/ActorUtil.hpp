#ifndef ACTORUTIL_H
#define ACTORUTIL_H
#include <concepts>
#include "Actor.hpp"

namespace BCIEvent{
   
    template<typename T>
    concept ExpressionType = std::convertible_to<T, bool> || std::convertible_to<T, int> || std::convertible_to<T, float>;

    template<typename T, typename U> requires ExpressionType<U> && std::same_as<std::result_of<T(const Actor&)>,U>
    std::function<U (const Actor&)> getExpressionFn(T in){
	return in; 
    }

    template<typename T, typename U> requires ExpressionType<U> && std::same_as<std::result_of<T()>, U>
    std::function<U (const Actor&)> getExpressionFn(T in){
	return [&](const Actor&){ return T(); };
    }

    template<typename T, typename U> requires std::convertible_to<T, std::string>
    std::function<U (const Actor&)> getExpressionFn(T in){
	return [&](const Actor& a) { return a.getVariable(in); };
    }

    template<typename T>
    std::function<T (const Actor&)> getExpressionFn(T in){
	return [&](const Actor&) { return in; };
    }

}

#endif
