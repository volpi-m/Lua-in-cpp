#include "newLua.hpp"

Lua::Lua()
{
    _state = luaL_newstate();
    if (!_state)
        throw;
}

Lua::~Lua()
{
    lua_close(_state);
}

void Lua::openLibs() const
{
    luaL_openlibs(_state);
}

void Lua::reset()
{
    lua_close(_state);
    _state = luaL_newstate();
    if (!_state)
        throw;
}

bool Lua::loadFile(const std::string &filename)
{
    if (luaL_dofile(_state, filename.c_str()) != LUA_OK) {
        _error = lua_tostring(_state, -1);
        std::cerr << _error << std::endl;
        return false;
    }
    return true;
}

void Lua::execScript(const std::string &script) const
{
    if (luaL_dostring(_state, script.c_str()) != LUA_OK) {
        std::cerr << lua_tostring(_state, -1);
    }
}

void Lua::callLuaFunction(const std::string &name)
{
    lua_getglobal(_state, name.c_str());
    lua_call(_state, 0, 0);
}

/*

void Lua::registerFunction(const std::string &name, const lua_CFunction f)
{
    lua_pushcfunction(_state, f);
    lua_setglobal(_state, name.c_str());
}

void Lua::registerModule(const std::string &moduleName, const luaL_Reg *functions)
{
    lua_getglobal(_state, moduleName.c_str());
    if (!lua_istable(_state, -1)) {
        lua_newtable(_state);
    }
    luaL_setfuncs(_state, functions, 0);
    lua_setglobal(_state, moduleName.c_str());
}

void Lua::registerModule(const std::string &moduleName, LuaModule &module)
{
    lua_getglobal(_state, moduleName.c_str());
    if (!lua_istable(_state, -1)) {
        lua_newtable(_state);
    }
    luaL_setfuncs(_state, module.getFunctions(), 0);
    lua_setglobal(_state, moduleName.c_str());
}

*/