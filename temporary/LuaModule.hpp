#pragma once

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <unordered_map>
#include <string>

class LuaModule
{
public:
    LuaModule();
    ~LuaModule();

    void addFunction(const std::string &, int (*)(lua_State*));
    luaL_Reg *getFunctions();

private:
    luaL_Reg *_luaFunc;
    std::unordered_map<std::string, int (*)(lua_State*)> _funcList;
};
