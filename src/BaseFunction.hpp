#pragma once

#include <iostream>
#include <string>

#include "Lua.hpp"

template< class >
class BaseFunction;

template<class>
struct helper;

template<>
struct helper<int>
{
    static void push(Lua &l, lua_Integer arg) { lua_pushinteger(getState(l), arg); }
};

template<>
struct helper<const char *>
{
    static void push(Lua &l, const char * arg) { lua_pushstring(getState(l), arg); }
};

template<>
struct helper<double>
{
    static void push(Lua &l, lua_Number arg) { lua_pushnumber(getState(l), arg); }
};

template<>
struct helper<bool>
{
    static void push(Lua &l, bool arg) { lua_pushboolean(getState(l), arg); }
};

template<>
struct helper<void *>
{
    static void push(Lua &l, void *arg) { lua_pushlightuserdata(getState(l), arg); }
};

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
        static_assert(std::is_same_v<U, int> || std::is_same_v<U, const char *>
            || std::is_same_v<U, double> || std::is_same_v<U, bool>
            || std::is_same_v<U, void *>);
        _nbArg++;
        //std::cout << "arg: " << arg << std::endl;
        helper<U>::push(_inst, arg);
        intern(args...);
    }

    template< typename U >
    void intern(U arg)
    {
        static_assert(std::is_same_v<U, int> || std::is_same_v<U, const char *>
            || std::is_same_v<U, double> || std::is_same_v<U, bool>
            || std::is_same_v<U, void *>);
        _nbArg++;
        //std::cout << "final arg: " << arg << std::endl;
        helper<U>::push(_inst, arg);
        lua_call(getState(_inst), _nbArg, 1);
    }

    void intern()
    {
        lua_call(getState(_inst), 0, 0);
    }

    Lua &_inst;
    const std::string _fname;
    int _nbArg;
};
