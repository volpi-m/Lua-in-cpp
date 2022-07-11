#include "Window.hpp"

int createWindow(lua_State *l)
{
    int n = lua_gettop(l);

    if (!lua_isstring(l, 1) || n != 1) {
        lua_pushliteral(l, "incorrect argument");
        lua_error(l);
    }
    const char *title = lua_tostring(l, 1);
    sfVideoMode mode;

    mode.width = 600;
    mode.height = 400;
    mode.bitsPerPixel = 32;
    sfRenderWindow *w = sfRenderWindow_create(mode, title, sfResize | sfClose, NULL);

    printf("%p\n", w);
    lua_pushlightuserdata(l, w);
    return 1;
}

int clearWindow(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto *color = (sfColor *)lua_touserdata(l, 2);
    sfRenderWindow_clear(w, *color);

    return 0;
}

int isWindowOpen(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 1) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    lua_pushinteger(l, sfRenderWindow_isOpen(w));

    return 1;
}

int displayWindow(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 1) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    sfRenderWindow_display(w);
    return 0;
}

int pollEvent(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto *evt = (sfEvent *)lua_touserdata(l, 2);

    lua_pushboolean(l, sfRenderWindow_pollEvent(w, evt));
    return 1;
}

int waitEvent(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto *evt = (sfEvent *)lua_touserdata(l, 2);

    lua_pushboolean(l, sfRenderWindow_waitEvent(w, evt));
    return 1;
}

int closeWindow(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 1) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    sfRenderWindow_close(w);

    return 0;
}

int destroyWindow(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 1) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    sfRenderWindow_destroy(w);
    return 0;
}

/*int getPosition(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 1) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    sfVector2i pos = sfRenderWindow_getPosition(w);

    lua_pushlightuserdata(l, pos);
    return 1;
}*/

int setSize(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 3) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    unsigned int width = lua_tonumber(l, 2);
    unsigned int height = lua_tonumber(l, 3);

    sfRenderWindow_setSize(w, {width, height});
    return 0;
}

int setTitle(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto *title = (const char *)lua_tostring(l, 2);

    sfRenderWindow_setTitle(w, title);
    return 0;
}

int setUnicodeTitle(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto *title = (sfUint32 *)lua_topointer(l, 2);

    sfRenderWindow_setUnicodeTitle(w, title);
    return 0;
}

int setIcon(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 4) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto width = lua_tonumber(l, 2);
    auto height = lua_tonumber(l, 3);
    auto *pixels = (const sfUint8 *)lua_topointer(l, 4);

    sfRenderWindow_setIcon(w, width, height, pixels);
    return 0;
}

int setVisible(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto visible = lua_toboolean(l, 2);

    sfRenderWindow_setVisible(w, visible);
    return 0;
}

int setVerticalSyncEnabled(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto enabled = lua_toboolean(l, 2);

    sfRenderWindow_setVerticalSyncEnabled(w, enabled);
    return 0;
}

int setMouseCursorVisible(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto show = lua_toboolean(l, 2);

    sfRenderWindow_setMouseCursorVisible(w, show);
    return 0;
}

int setMouseCursorGrabbed(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto grabbed = lua_toboolean(l, 2);

    sfRenderWindow_setMouseCursorGrabbed(w, grabbed);
    return 0;
}

int setKeyRepeatEnabled(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto enabled = lua_toboolean(l, 2);

    sfRenderWindow_setKeyRepeatEnabled(w, enabled);
    return 0;
}

int setFramerateLimit(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto limit = (unsigned int)lua_tonumber(l, 2);

    sfRenderWindow_setFramerateLimit(w, limit);
    return 0;
}

int setJoystickThreshold(lua_State *l)
{
    int n = lua_gettop(l);

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }
    auto *w = (sfRenderWindow *)lua_touserdata(l, 1);
    auto threshold = (float)lua_tonumber(l, 2);

    sfRenderWindow_setJoystickThreshold(w, threshold);
    return 0;
}
