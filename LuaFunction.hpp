#pragma once

#include <type_traits>

#include "NonVoidFunction.hpp"
#include "VoidFunction.hpp"

template< class T, class ...Args >
using DerivingFunction = typename std::conditional<
    std::is_void<T>::value,
    VoidFunction< void(Args...) >,
    NonVoidFunction< T(Args...) >
>::type;

template< class >
class LuaFunction;

template< class T, class ...Args >
class LuaFunction < T(Args...) > : public DerivingFunction<T, Args...>
{
public:
    LuaFunction(Lua &l, const std::string &fname) :
        DerivingFunction<T, Args...>(l, fname)
    {}
};
