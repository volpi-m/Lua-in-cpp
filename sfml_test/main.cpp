#include <string>
#include <iostream>
//#include "Lua.hpp"
#include "newLua.hpp"
#include "Window.hpp"

extern "C"
{
    /*int createEvent(lua_State *l)
    {
        sfEvent *evt = new sfEvent();

        lua_pushlightuserdata(l, evt);
        return 1;
    }

    int destroyEvent(lua_State *l)
    {
        int n = lua_gettop(l);

        if (n != 1) {
            lua_pushliteral(l, "bad number of arguments");
            lua_error(l);
        }
        auto *evt = (sfEvent *)lua_touserdata(l, 1);
        delete evt;
        return 0;
    }

    int getEventType(lua_State *l)
    {
        int n = lua_gettop(l);

        if (n != 1) {
            lua_pushliteral(l, "bad number of argument");
            lua_error(l);
        }
        auto *evt = (sfEvent *)lua_touserdata(l, 1);
        lua_pushinteger(l, evt->type);

        return 1;
    }

    int isKeyPressed(lua_State *l)
    {
        int n = lua_gettop(l);

        if (n != 1) {
            lua_pushliteral(l, "bad number of arguments");
            lua_error(l);
        }
        sfKeyCode key = (sfKeyCode)lua_tointeger(l, 1);
        lua_pushboolean(l, sfKeyboard_isKeyPressed(key));

        return 1;
    }*/
}

int fun1(lua_State *l)
{
    std::cout << "Hello World" << std::endl;
    return 0;
}

int fun2(lua_State *l)
{
    int n = lua_gettop(l);

    int n1 = lua_tointeger(l, 1);
    int n2 = lua_tointeger(l, 2);
    std::cout << n1 + n2 << std::endl;
    return 0;
}

int fun3(lua_State *l)
{
    lua_pushnumber(l, 1);
    return 1;
}

void printcolor(sfColor c)
{
    std::cout << (int)c.r << " " << (int)c.g << " " << (int)c.b << " " << (int)c.a << std::endl;
}

int main()
{/*
    Lua lua("example.lua");
    FunctionInfo f1(1, {}, "greets");
    lua.call(f1, "Frodo");

    std::vector<std::string> returnTypes{"x"};
    FunctionInfo f2(2, returnTypes, "add");
    std::vector<std::any> ret = lua.call(f2, 15, 42);
 
    std::cout << "15 + 42 = " << std::any_cast<long long>(ret[0]) << std::endl;*/

    //lua_State *state = luaL_newstate();
    //luaL_openlibs(state);

    /*const luaL_Reg window[] = {
        { "create", &createWindow },
        { "clear", &clearWindow },
        { "isOpen", &isWindowOpen },
        { "display", &displayWindow },
        { "pollEvent", &pollEvent },
        { "waitEvent", &waitEvent },
        { "close", &closeWindow },
        { "destroy", &destroyWindow },
        { "setSize", &setSize },
        { "setTitle", &setTitle },
        { "setUnicodeTitle", &setUnicodeTitle },
        { "setIcon", &setIcon },
        { "setVisible", &setVisible },
        { "setVerticalSyncEnabled", &setVerticalSyncEnabled },
        { "setMouseCursorVisible", &setMouseCursorVisible },
        { "setMouseCursorGrabbed", &setMouseCursorGrabbed },
        { "setKeyRepeatEnabled", &setKeyRepeatEnabled },
        { "setFramerateLimit", &setFramerateLimit },
        { "setJoystickThreshold", &setJoystickThreshold },
        { NULL, NULL }
    };

    const luaL_Reg sfml[] = {
        { "createEvent", &createEvent },
        { "getEventType", &getEventType },
        { "destroyEvent", &destroyEvent },
        { "isKeyPressed", &isKeyPressed },
        { NULL, NULL }
    };*/

    /*const LuaTable<sfColor>colors[] = {
        { "White", sfWhite },
        { "Black", sfBlack },
        { "Red", sfRed },
        { "Green", sfGreen },
        { "Blue", sfBlue },
        { "Yellow", sfYellow },
        { "Magenta", sfMagenta },
        { "Cyan", sfCyan },
        { "Transparent", sfTransparent },
        { nullptr, nullptr }
    };

    const LuaTable<lua_Integer>keys[] = {
        { "escape", sfKeyEscape },
        { nullptr, nullptr }
    };

    const LuaTable<lua_Integer>eventType[] = {
        { "Closed", sfEvtClosed },
        { "Resized", sfEvtResized },
        { "LostFocus", sfEvtLostFocus },
        { "GainedFocus", sfEvtGainedFocus },
        { "TextEtered", sfEvtTextEntered },
        { "KeyPressed", sfEvtKeyPressed },
        { "KeyReleased", sfEvtKeyReleased },
        { "MouseWheelMoved", sfEvtMouseWheelMoved },
        { "MouseWheelScrolled", sfEvtMouseWheelScrolled },
        { "MouseButtonPressed", sfEvtMouseButtonPressed },
        { "MouseButtonReleased", sfEvtMouseButtonReleased },
        { "MouseMoved", sfEvtMouseMoved },
        { "MouseEntered", sfEvtMouseEntered },
        { "MouseLeft", sfEvtMouseLeft },
        { "JoystickButtonPressed", sfEvtJoystickButtonPressed },
        { "JoyStickButtonReleased", sfEvtJoystickButtonReleased },
        { "JoystickMoved", sfEvtJoystickMoved },
        { "JoyStickConnected", sfEvtJoystickConnected },
        { "JoystickDisconnected", sfEvtJoystickDisconnected },
        { "TouchBegan", sfEvtTouchBegan },
        { "TouchMoved", sfEvtTouchMoved },
        { "TouchEnded", sfEvtTouchEnded },
        { "SensorChanged", sfEvtSensorChanged },
        { "Count", sfEvtCount },
        { nullptr, nullptr }
    };*/

    Lua l;
    l.openLibs();
    // l.addTable<sfColor>("color", colors);
    // l.addTable<lua_Integer>("keys", keys);
    // l.addTable<lua_Integer>("event", eventType);
    // l.registerModule("sfml", sfml);
    // l.registerModule("window", window);
    if (l.loadFile("lua/test.lua"))
        l.callLuaFunction("main");

    /*lua_createtable(state, 0, 1);
    lua_pushinteger(state, sfEvtClosed);
    lua_setfield(state, -2, "sfEvtClosed");
    lua_setglobal(state, "eventType");



    lua_createtable(state, 0, 1);
    lua_pushlightuserdata(state, &sfWhite);
    lua_setfield(state, -2, "White");
    lua_pushlightuserdata(state, &sfBlack);
    lua_setfield(state, -2, "Black");
    lua_pushlightuserdata(state, &sfRed);
    lua_setfield(state, -2, "Red");
    lua_pushlightuserdata(state, &sfGreen);
    lua_setfield(state, -2, "Green");
    lua_pushlightuserdata(state, &sfBlue);
    lua_setfield(state, -2, "Blue");
    lua_pushlightuserdata(state, &sfYellow);
    lua_setfield(state, -2, "Yellow");
    lua_pushlightuserdata(state, &sfMagenta);
    lua_setfield(state, -2, "Magenta");
    lua_pushlightuserdata(state, &sfCyan);
    lua_setfield(state, -2, "Cyan");
    lua_pushlightuserdata(state, &sfTransparent);
    lua_setfield(state, -2, "Transparent");
    lua_setglobal(state, "color");

    lua_getglobal(state, "sfml");
    if (!lua_istable(state, -1)) {
        lua_newtable(state);
    }
    luaL_setfuncs(state, sfml, 0);
    lua_setglobal(state, "sfml");
    luaL_dofile(state, "example.lua");

    lua_getglobal(state, "window");
    lua_call(state, 0, 0);


    /*printcolor(sfBlack);
    printcolor(sfWhite);
    printcolor(sfRed);
    printcolor(sfGreen);
    printcolor(sfBlue);
    printcolor(sfYellow);
    printcolor(sfMagenta);
    printcolor(sfCyan);
    printcolor(sfTransparent);*/

    /*

    /// Prepare C functions to be added to Lua
    const luaL_Reg functions[] = {
        {"yeet", &yeet},
        {NULL, NULL}
    };

    /// Add C functions to Lua via a module called "ouep"
    lua_getglobal(state, "ouep");
    if (!lua_istable(state, -1)) {
        lua_newtable(state);
    }
    luaL_setfuncs(state, functions, 0);
    lua_setglobal(state, "ouep");
    luaL_dostring(state, "ouep.yeet()");*/

    /// Setup one C function alone to be called directly via its name
    /*lua_pushcfunction(state, &sum);
    lua_setglobal(state, "sum");
    lua_pushcfunction(state, &yeet);
    lua_setglobal(state, "yeet");
    luaL_dostring(state, "print(sum(1, 2, 3))");*/

/*
    /// Open a lua file with a call tu a C function that was added just above
    luaL_dofile(state, "example.lua");
    lua_getglobal(state, "greets");
    lua_pushliteral(state, "Frodo");
    lua_call(state, 1, 0);

    /// A string to be interperted as Lua
    //luaL_dostring(state, "print('nope')");
    */

    /*

    Lua lua("example.lua");
    lua.loadStandardLibraries();
    lua.script("print('hello world')");

    lua.addFunction("un nom", [une fonction en C]);
    lua.call<type(type)>([fonction en lua]);

    on veut lancer des fonctions lua en C et récupérer les valeurs de retour
    créer des fonctions C dans le contexte lua et elles sont exécutable depuis lua
    mettre des variables globales entre lua et C
    exécuter du code lua sous forme de string en C

    */
   //lua_close(state);
}
