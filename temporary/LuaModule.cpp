#include "LuaModule.hpp"
#include <iostream>

LuaModule::LuaModule() : _luaFunc(nullptr) {}

LuaModule::~LuaModule()
{
    delete[] _luaFunc;
}

void LuaModule::addFunction(const std::string &name, int (*func)(lua_State*))
{
    _funcList[name] = func;
}

luaL_Reg *LuaModule::getFunctions()
{
    if (_luaFunc)
        delete[] _luaFunc;
    _luaFunc = new luaL_Reg[_funcList.size() + 1];

    int i = 0;
    for (auto &elem : _funcList) {
        _luaFunc[i].name = elem.first.c_str();
        _luaFunc[i].func = elem.second;
        i++;
    }
    _luaFunc[i].name = NULL;
    _luaFunc[i].func = NULL;
    return _luaFunc;
}
