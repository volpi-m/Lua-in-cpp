#pragma once

#include <SFML/Window.h>
#include <SFML/Graphics.h>

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

    int createWindow(lua_State *);
    int clearWindow(lua_State *);
    int isWindowOpen(lua_State *);
    int displayWindow(lua_State *);
    int pollEvent(lua_State *);
    int waitEvent(lua_State *);
    int closeWindow(lua_State *);
    int destroyWindow(lua_State *);
    int setSize(lua_State *);
    int setTitle(lua_State *);
    int setUnicodeTitle(lua_State *);
    int setIcon(lua_State *);
    int setVisible(lua_State *);
    int setVerticalSyncEnabled(lua_State *);
    int setMouseCursorVisible(lua_State *);
    int setMouseCursorGrabbed(lua_State *);
    int setKeyRepeatEnabled(lua_State *);
    int setFramerateLimit(lua_State *);
    int setJoystickThreshold(lua_State *);
}
