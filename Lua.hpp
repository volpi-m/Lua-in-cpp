#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include <any>
#include <cstring>


extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


typedef struct FunctionInfo_s
{
    FunctionInfo_s()
        : nbParam(0), returnValue({}), function("") {}
    FunctionInfo_s(int nbParam, std::vector<std::string> returnValue, const std::string &fun)
        : nbParam(nbParam), returnValue(returnValue), function(fun) {}

    const std::string toString() const
    {
        std::string r = std::to_string(nbParam) + " ";
        for (auto i : returnValue)
            r += i;
        r += " " + function;
        return r;
    }

    int nbParam;
    std::vector<std::string> returnValue;
    std::string function;
} FunctionInfo;


class Lua
{
public:
    // Constructors
    Lua() : _file(""), _nbParam(0), _returnValue({})
    {
        _lua = luaL_newstate();
        if (!_lua)
            throw std::exception();
        luaL_openlibs(_lua);
    }
    Lua(const std::string &file) : _file(file), _nbParam(0), _returnValue({})
    {
        _lua = luaL_newstate();
        if (!_lua)
            throw std::exception();
        luaL_openlibs(_lua);
        loadFile(_file);
    }


    // Destructor
    ~Lua() { lua_close(_lua); }


    // -------------------- Useful functions --------------------
    bool loadFile(const std::string &name)
    {
        _file = name;
        return luaL_dofile(_lua, name.c_str());
    }
    const std::string &fileLoaded() const { return _file; }


    // -------------------- LOOOADS of overload --------------------
    template<typename T>
    void pushOnStack(T arg)           { lua_pushinteger(_lua, arg); }
    void pushOnStack(lua_Number arg)  { lua_pushnumber(_lua, arg); }
    void pushOnStack(float arg)       { lua_pushnumber(_lua, arg); }
    void pushOnStack(bool arg)        { lua_pushboolean(_lua, arg ? 1 : 0); }
    void pushOnStack(const char *arg) { lua_pushstring(_lua, arg); }


    // -------------------- Call any function in Lua --------------------
    template<typename ...Args> std::vector<std::any> call(const FunctionInfo &info, Args... args)
    {
        _nbParam = info.nbParam;
        _returnValue = info.returnValue;
        lua_getglobal(_lua, info.function.c_str());
        return call(args...);
    }

    std::vector<std::any> call(const FunctionInfo &info)
    {
        lua_getglobal(_lua, info.function.c_str());
        lua_call(_lua, info.nbParam, 0);

        _returnValue = info.returnValue;

        std::vector<std::any> ret = getReturnValues();
        _returnValue = {};

        return ret;
    }

private:
    template<typename T> std::vector<std::any> call(T last)
    {
        pushOnStack(last);
        lua_call(_lua, _nbParam, _returnValue.size());
        std::vector<std::any> ret = getReturnValues();

        _nbParam = 0;
        _returnValue = {};

        return ret;
    }

    template<typename T, typename ... Args> std::vector<std::any> call(T first, Args... args)
    {
        pushOnStack(first);
        return call(args...);
    }


    // -------------------- Return values from Lua's function --------------------
    std::vector<std::any> getReturnValues() const
    {
        std::vector<std::any> result;
        std::any r;
        result.reserve(_returnValue.size());

        for (size_t i = 0; i < _returnValue.size(); i++) {
            if (_returnValue[i] == "c")
                r = lua_tostring(_lua, - (int)(_returnValue.size() - i));

            else if (_returnValue[i] == "d")
                r = lua_tonumber(_lua, - (int)(_returnValue.size() - i));

            else if (_returnValue[i] == "x")
                r = lua_tointeger(_lua, - (int)(_returnValue.size() - i));

            else if (_returnValue[i] == "b")
                r = (bool) lua_toboolean(_lua, - (int)(_returnValue.size() - i));

            result.emplace_back(r);
        }

        for (size_t i = 0; i < _returnValue.size(); i++)
            lua_pop(_lua, 1);

        return result;
    }

private:
    lua_State *_lua;
    std::string _file;
    int _nbParam;
    std::vector<std::string> _returnValue;
};

