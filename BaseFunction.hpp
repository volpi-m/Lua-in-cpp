#pragma once

#include <iostream>
#include <string>

#include "Lua.hpp"

template< class >
class BaseFunction;

template< typename T, typename ...Args >
class BaseFunction < T(Args...)>
{
friend class Lua;

public:
    BaseFunction(Lua &l, const std::string &fname) :
        _inst(l), _fname(fname), _nbArg(0)
    {
        //std::cout << _fname << std::endl;
    }
    virtual ~BaseFunction() = default;

    virtual T operator()(Args...) = 0;

    // virtual T operator()(Args... args)
    // {
    //     lua_getglobal(getState(_inst), _fname.c_str());
    //     intern(args...);
    //     int a = lua_tointeger(getState(_inst), -1);
    //     lua_pop(getState(_inst), 1);
    //     return a;
    // }

protected:
    template< typename U, typename ...InternArgs >
    void intern(U arg, InternArgs... args)
    {
        _nbArg++;
        //std::cout << "arg: " << arg << std::endl;
        pushOnStack(_inst, arg);
        intern(args...);
    }

    template< typename U >
    void intern(U arg)
    {
        _nbArg++;
        //std::cout << "final arg: " << arg << std::endl;
        pushOnStack(_inst, arg);
        lua_call(getState(_inst), _nbArg, 1);
    }

    Lua &_inst;
    const std::string _fname;
    int _nbArg;
};
