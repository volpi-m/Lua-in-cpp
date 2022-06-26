#include "newLua.hpp"

int main()
{
    Lua l;
    l.openLibs();

    if (l.loadFile("lua/test.lua"))
        l.callLuaFunction("main");
}