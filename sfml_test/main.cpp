#include <string>
#include <iostream>

#include "../src/LuaInCpp.hpp"
#include "Window.hpp"

extern "C"
{
    int createEvent(lua_State *l)
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
    }
}

void printcolor(sfColor c)
{
    std::cout << (int)c.r << " " << (int)c.g << " " << (int)c.b << " " << (int)c.a << std::endl;
}

int main()
{
    Lua l;
    l.openLibs();

    l.add("closed", (lua_Integer) sfEvtClosed, "event");
    l.add("resized", (lua_Integer) sfEvtResized, "event");
    l.add("lostFocus", (lua_Integer) sfEvtLostFocus, "event");
    l.add("gainedFocus", (lua_Integer) sfEvtGainedFocus, "event");
    l.add("textEtered", (lua_Integer) sfEvtTextEntered, "event");
    l.add("keyPressed", (lua_Integer) sfEvtKeyPressed, "event");
    l.add("keyReleased", (lua_Integer) sfEvtKeyReleased, "event");
    l.add("mouseWheelMoved", (lua_Integer) sfEvtMouseWheelMoved, "event");
    l.add("mouseWheelScrolled", (lua_Integer) sfEvtMouseWheelScrolled, "event");
    l.add("mouseButtonPressed", (lua_Integer) sfEvtMouseButtonPressed, "event");
    l.add("mouseButtonReleased", (lua_Integer) sfEvtMouseButtonReleased, "event");
    l.add("mouseMoved", (lua_Integer) sfEvtMouseMoved, "event");
    l.add("mouseEntered", (lua_Integer) sfEvtMouseEntered, "event");
    l.add("mouseLeft", (lua_Integer) sfEvtMouseLeft, "event");
    l.add("joystickButtonPressed", (lua_Integer) sfEvtJoystickButtonPressed, "event");
    l.add("joyStickButtonReleased", (lua_Integer) sfEvtJoystickButtonReleased, "event");
    l.add("joystickMoved", (lua_Integer) sfEvtJoystickMoved, "event");
    l.add("joyStickConnected", (lua_Integer) sfEvtJoystickConnected, "event");
    l.add("joystickDisconnected", (lua_Integer) sfEvtJoystickDisconnected, "event");
    l.add("touchBegan", (lua_Integer) sfEvtTouchBegan, "event");
    l.add("touchMoved", (lua_Integer) sfEvtTouchMoved, "event");
    l.add("touchEnded", (lua_Integer) sfEvtTouchEnded, "event");
    l.add("sensorChanged", (lua_Integer) sfEvtSensorChanged, "event");
    l.add("count", (lua_Integer) sfEvtCount, "event");

    l.add("escape", (lua_Integer) sfKeyEscape, "keys");

    l.add("black", (void *) &sfBlack, "color");
    l.add("white", (void *) &sfWhite, "color");
    l.add("red", (void *) &sfRed, "color");
    l.add("green", (void *) &sfGreen, "color");
    l.add("blue", (void *) &sfBlue, "color");
    l.add("yellow", (void *) &sfYellow, "color");
    l.add("magenta", (void *) &sfMagenta, "color");
    l.add("cyan", (void *) &sfCyan, "color");
    l.add("transparent", (void *) &sfTransparent, "color");

    l.add("createEvent", createEvent, "sfml");
    l.add("getEventType", getEventType, "sfml");
    l.add("destroyEvent", destroyEvent, "sfml");
    l.add("isKeyPressed", isKeyPressed, "sfml");

    l.add("create", &createWindow, "window");
    l.add("clear", &clearWindow, "window");
    l.add("isOpen", &isWindowOpen, "window");
    l.add("display", &displayWindow, "window");
    l.add("pollEvent", &pollEvent, "window");
    l.add("waitEvent", &waitEvent, "window");
    l.add("close", &closeWindow, "window");
    l.add("destroy", &destroyWindow, "window");
    l.add("setSize", &setSize, "window");
    l.add("setTitle", &setTitle, "window");
    l.add("setUnicodeTitle", &setUnicodeTitle, "window");
    l.add("setIcon", &setIcon, "window");
    l.add("setVisible", &setVisible, "window");
    l.add("setVerticalSyncEnabled", &setVerticalSyncEnabled, "window");
    l.add("setMouseCursorVisible", &setMouseCursorVisible, "window");
    l.add("setMouseCursorGrabbed", &setMouseCursorGrabbed, "window");
    l.add("setKeyRepeatEnabled", &setKeyRepeatEnabled, "window");
    l.add("setFramerateLimit", &setFramerateLimit, "window");
    l.add("setJoystickThreshold", &setJoystickThreshold, "window");

    if (l.loadFile("../lua/main_sfml.lua"))
        l.call("main");

    return 0;
}
