#pragma once

#include <type_traits>

#include "NonVoidFunction.hpp"
#include "VoidFunction.hpp"

template< class >
class LuaFunction;

template< class T, class ...Args >
class LuaFunction < T(Args...) > : public std::conditional<
    std::is_void<T>::value,
    VoidFunction< void(Args...) >,
    NonVoidFunction< T(Args...) > >::type
{
public:
    LuaFunction(Lua &l, const std::string &fname) : std::conditional< std::is_void<T>::value, VoidFunction< void(Args...) >, NonVoidFunction< T(Args...) > >::type(l, fname)
    {}
};
