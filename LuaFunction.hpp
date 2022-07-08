#pragma once

#include <iostream>
#include <string>
#include <exception>

#include "Lua.hpp"

template< std::size_t ret, class >
class LuaFunction;

template< std::size_t ret, typename T, typename ...Args>
class LuaFunction < ret, T(Args...)>
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
        if (ret != 0) {
            int a = lua_tointeger(getState(_inst), -1);
            lua_pop(getState(_inst), 1);
            return a;
        }
    }

protected:
    friend class Lua;

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
        lua_call(getState(_inst), _nbArg, ret);
    }

    Lua &_inst;
    const std::string _fname;
    int _nbArg;
};

template< class ...Args >
class Function : public LuaFunction<0, void(Args...)>
{
public:
    Function(Lua &l, const std::string &fname) :
        LuaFunction<0, void(Args...)>(l, fname)
    {}

    void operator()(Args... args)
    {
        intern(args...);
    }

    template< class T >
    void intern(T arg)
    {
        std::cout << "final arg: " << arg << std::endl;
    }

    template< class T, class ...InternArgs >
    void intern(T arg, InternArgs... args)
    {
        std::cout << "arg: " << arg << std::endl;
        intern(args...);
    }
};

