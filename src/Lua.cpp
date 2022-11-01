#include "Lua.hpp"

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
        std::cerr << lua_tostring(_state, -1) << std::endl;
        return false;
    }
    return true;
}

bool Lua::loadScript(const std::string &script) const
{
    if (luaL_dostring(_state, script.c_str()) != LUA_OK) {
        std::cerr << lua_tostring(_state, -1) << std::endl;
        return false;
    }
    return true;
}

void Lua::registerModule(const std::string &modName, const luaL_Reg *functions) const
{
    lua_getglobal(_state, modName.c_str());
    if (!lua_istable(_state, -1)) {
        lua_newtable(_state);
    }
    luaL_setfuncs(_state, functions, 0);
    lua_setglobal(_state, modName.c_str());
}

void Lua::add(const std::string &name, lua_CFunction f, const std::string &modName)
{
    if (modName == "") {
        lua_pushcfunction(_state, f);
        lua_setglobal(_state, name.c_str());
    } else {
        lua_getglobal(_state, modName.c_str()); // get a name on the stack (may be a new or existing table)
        if (!lua_istable(_state, -1)) // create a table if it is not already
            lua_newtable(_state);
        lua_pushstring(_state, name.c_str()); // index of the value in the table
        lua_pushcfunction(_state, f); // value to be set
        lua_settable(_state, -3); // modName.name = f
        lua_setglobal(_state, modName.c_str()); // say that the table is now an accessible variable
    }
}

void Lua::add(const std::string &name, lua_Number n, const std::string &modName)
{
    if (modName == "") {
        lua_pushnumber(_state, n);
        lua_setglobal(_state, name.c_str());
    } else {
        lua_getglobal(_state, modName.c_str());
        if (!lua_istable(_state, -1))
            lua_newtable(_state);
        lua_pushstring(_state, name.c_str());
        lua_pushnumber(_state, n);
        lua_settable(_state, -3);
        lua_setglobal(_state, modName.c_str());
    }
}

void Lua::add(const std::string &name, lua_Integer i, const std::string &modName)
{
    if (modName == "") {
        lua_pushinteger(_state, i);
        lua_setglobal(_state, name.c_str());
    } else {
        lua_getglobal(_state, modName.c_str());
        if (!lua_istable(_state, -1))
            lua_newtable(_state);
        lua_pushstring(_state, name.c_str());
        lua_pushinteger(_state, i);
        lua_settable(_state, -3);
        lua_setglobal(_state, modName.c_str());
    }
}

void Lua::add(const std::string &name, const char *s, const std::string &modName)
{
    if (modName == "") {
        lua_pushstring(_state, s);
        lua_setglobal(_state, name.c_str());
    } else {
        lua_getglobal(_state, modName.c_str());
        if (!lua_istable(_state, -1))
            lua_newtable(_state);
        lua_pushstring(_state, name.c_str());
        lua_pushstring(_state, s);
        lua_settable(_state, -3);
        lua_setglobal(_state, modName.c_str());
    }
}

void Lua::add(const std::string &name, void *data, const std::string &modName)
{
    if (modName == "") {
        lua_pushlightuserdata(_state, data);
        lua_setglobal(_state, name.c_str());
    } else {
        lua_getglobal(_state, modName.c_str());
        if (!lua_istable(_state, -1))
            lua_newtable(_state);
        lua_pushstring(_state, name.c_str());
        lua_pushlightuserdata(_state, data);
        lua_settable(_state, -3);
        lua_setglobal(_state, modName.c_str());
    }
}

bool Lua::call(const std::string &name)
{
    lua_getglobal(_state, name.c_str());
    if (lua_pcall(_state, 0, 0, 0) != LUA_OK) {
        std::cerr << lua_tostring(_state, -1) << std::endl;
        return false;
    }
    return true;
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