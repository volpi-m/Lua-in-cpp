//#include "Lua.hpp"
//#include "LuaFunction.hpp"
#include "LuaInCpp.hpp"

int add(lua_State *l)
{
    int n = lua_gettop(l); // get the number of arguments

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }

    int a = lua_tointeger(l, 1); // get first arg
    int b = lua_tointeger(l, 2); // get second ard

    std::cout << "[C++] " << a << " + " << b << std::endl;
    lua_pushinteger(l, a + b); // the return value
    return 1; // number of argument returned
}

int main()
{
    Lua l;
    l.openLibs();

    l.add("add", &add, "mymath");

    if (l.loadFile("example/test.lua")) {
        LuaFunction<void(const char *)> greets(l, "greets");
        greets("Frodo");

        l.call("main");
    }
}
