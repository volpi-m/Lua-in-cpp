#pragma once

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <string>
#include <iostream>

class Lua
{
public:
    Lua();
    ~Lua();

    void openLibs() const; // open lua libraries
    void reset(); // reset the internal state, create a new one
    bool loadFile(const std::string &); // load a .lua file
    bool loadScript(const std::string &) const; // load a string of lua

    // Todo: multiple registerModule() to register a bunch of functions or values in one go
    void registerModule(const std::string &, const luaL_Reg *) const;

    void add(const std::string &, lua_CFunction, const std::string & = "");
    void add(const std::string &, lua_Number, const std::string & = "");
    void add(const std::string &, lua_Integer, const std::string & = "");
    void add(const std::string &, const char *, const std::string & = "");
    void add(const std::string &, void *, const std::string & = "");

    bool call(const std::string &); // call a lua function in C++

private:
    friend lua_State *getState(Lua &l) { return l._state; }

    // friend void pushOnStackInt(Lua &l, lua_Integer arg) { lua_pushinteger(l._state, arg); }
    // friend void pushOnStackNum(Lua &l, lua_Number arg) { lua_pushnumber(l._state, arg); }
    // friend void pushOnStackBool(Lua &l, bool arg) { lua_pushboolean(l._state, arg); }
    // friend void pushOnStackString(Lua &l, const char *arg) { lua_pushstring(l._state, arg); }
    // friend void pushOnStackPtr(Lua &l, void *arg) { lua_pushlightuserdata(l._state, arg); }
    // friend void pushOnStackNil(Lua &l) { lua_pushnil(l._state); }

    lua_State *_state;
};
