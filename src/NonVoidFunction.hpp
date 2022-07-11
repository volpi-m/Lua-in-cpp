#pragma once

#include "BaseFunction.hpp"

template< class >
class NonVoidFunction;

template< class T, class ...Args >
class NonVoidFunction < T(Args...) > : public BaseFunction<T(Args...)>
{
public:
    NonVoidFunction(Lua &l, const std::string &fname) :
        BaseFunction<T(Args...)>(l, fname)
    {}

    T operator()(Args... args) override
    {
        //std::cout << "T operator()" << std::endl;
        lua_getglobal(getState(this->_inst), this->_fname.c_str());
        this->intern(args...);
        int a = lua_tointeger(getState(this->_inst), -1);
        lua_pop(getState(this->_inst), 1);
        return a;
    }
};
