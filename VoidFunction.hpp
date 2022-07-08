#pragma once

#include "BaseFunction.hpp"

template< class >
class VoidFunction;

template< class ...Args >
class VoidFunction <void(Args...)> : public BaseFunction<void(Args...)>
{
public:
    VoidFunction(Lua &l, const std::string &fname) :
        BaseFunction<void(Args...)>(l, fname)
    {}

    void operator()(Args... args) override
    {
        //std::cout << "void operator()" << std::endl;
        lua_getglobal(getState(this->_inst), this->_fname.c_str());
        this->intern(args...);
    }
};
