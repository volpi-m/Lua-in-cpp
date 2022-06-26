#include "Lua.hpp"

int _func(lua_State *l)
{
    std::cout << "[C++] Hello World" << std::endl;
    return 0;
}

int _ouioui(lua_State *l)
{
    std::cout << "[C++] OuiOui" << std::endl;
    return 0;
}

int main()
{
    Lua l;
    l.openLibs();

    l.add("_yeet", &_func, "yeet");
    l.add("_ouioui", &_ouioui, "yeet");
    l.add("red", (lua_Integer) 0, "color");
    l.add("green", (lua_Integer) 1, "color");
    l.add("blue", (lua_Integer) 2);
    if (l.loadFile("lua/test.lua"))
        l.call("main");
}
