#include <string.h>
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
        char *s = strdup("Frodo");
        greets(s);

        LuaFunction<void(int)> my_sin(l, "my_sin_int");
        long a = 0;
        my_sin(a);

        LuaFunction<void(double)> my_sin_float(l, "my_sin_float");
        my_sin_float(2.3);

        LuaFunction<void(bool)> is_true(l, "is_true");
        is_true(false);

        LuaFunction<void(double, int)> both_sin(l, "both_sin");
        both_sin(2.3, 4);

        std::cout << std::endl;

        LuaFunction<int(const char *, bool, double, int)> all(l, "all");
        int b = all(s, false, 2.3, 4);
        std::cout << b << std::endl;

        l.call("main");
    }
}
