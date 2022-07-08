#include "Lua.hpp"
#include "LuaFunction.hpp"
#include "VoidFunction.hpp"

int _func([[maybe_unused]] lua_State *l)
{
    std::cout << "[C++] Hello World" << std::endl;
    return 0;
}

int _ouioui([[maybe_unused]] lua_State *l)
{
    std::cout << "[C++] OuiOui" << std::endl;
    return 0;
}

int main()
{
    Lua l;
    l.openLibs();

    l.add("_yeet", &_func, "yeet");
    l.add("_ouioui", &_ouioui, "ouioui");
    l.add("red", (lua_Integer) 0, "color");
    l.add("green", (lua_Integer) 1, "color");
    l.add("blue", (lua_Integer) 2);
    if (l.loadFile("lua/test.lua")) {
        //l.call("main");
        //l.call("hello");
    }

    LuaFunction<void(const char *)> greets(l, "greets");
    greets("Frodo");

    LuaFunction<void(const char *, lua_Integer)> printBoth(l, "printBoth");
    printBoth("Nope", 42);

    LuaFunction<lua_Integer(lua_Integer, lua_Integer)> addF(l, "add");
    std::cout << addF(1, 2) << std::endl;
}
