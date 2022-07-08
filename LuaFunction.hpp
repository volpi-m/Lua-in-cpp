#pragma once

#include <iostream>
#include <string>
#include <exception>

#include "Lua.hpp"

template< class >
class LuaFunction;

template< typename T, typename ...Args>
class LuaFunction < T(Args...)>
{
public:
    LuaFunction(Lua &l, const std::string &fname) :
        _inst(l), _fname(fname), _nbArg(0)
    {
        //std::cout << _fname << std::endl;
    }

    T operator()(Args... args)
    {
        lua_getglobal(getState(_inst), _fname.c_str());
        intern(args...);
        int a = lua_tointeger(getState(_inst), -1);
        lua_pop(getState(_inst), 1);
        return a;
    }

protected:
    friend class Lua;

    template< typename U, typename ...InternArgs >
    void intern(U arg, InternArgs... args)
    {
        _nbArg++;
        std::cout << "arg: " << arg << std::endl;
        pushOnStack(_inst, arg);
        intern(args...);
    }

    template< typename U >
    void intern(U arg)
    {
        _nbArg++;
        std::cout << "final arg: " << arg << std::endl;
        pushOnStack(_inst, arg);
        lua_call(getState(_inst), _nbArg, 1);
    }

    Lua &_inst;
    const std::string _fname;
    int _nbArg;
};

template< class ...Args >
class VoidFunction : public LuaFunction<void(Args...)>
{
public:
    VoidFunction(Lua &l, const std::string &fname) :
        LuaFunction<void(Args...)>(l, fname)
    {}

    void operator()(Args... args)
    {
        lua_getglobal(getState(this->_inst), this->_fname.c_str());
        this->intern(args...);
    }
};

