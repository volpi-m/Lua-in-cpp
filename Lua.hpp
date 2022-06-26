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

    //const std::string &getError() const { return _error; }

    void openLibs() const; // open lua libraries
    void reset(); // reset the internal state, create a new one
    bool loadFile(const std::string &); // load a .lua file
    bool execFile(const std::string &); // load and run a .lua file
    bool loadScript(const std::string &) const; // load a string of lua
    bool execScript(const std::string &) const; // load and run a string of lua

    void callLuaFunction(const std::string &); // call a lua function in C++

private:
    lua_State *_state;
    std::string _error; // do I keep this ?
};
