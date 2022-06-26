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

    void add(const std::string &, lua_CFunction, const std::string & = "");
    void add(const std::string &, lua_Number, const std::string & = "");
    void add(const std::string &, lua_Integer, const std::string & = "");

    bool call(const std::string &); // call a lua function in C++

private:
    lua_State *_state;
};
