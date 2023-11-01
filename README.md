# Lua in C++

## A simple bridge between Lua's API and C++.

This repository is still work in progress but starts to be useable. You can find classes to use Lua's API in C++ and use it to script things into your C++ programs.

This has been tested with C++ 20 on g++, Lua 5.4 and Ubuntu 22.04.

## Installation

Clone this repository and compile the static or shared library (see [this](#known-issues)) like this:

```sh
make libluaincpp.a
make libluaincpp.so
```

Then you're free to use and link it with your program.

## How to use

Here is a a Lua file and a C++ file showing you some of the features that this library does, you can find these files in the `example` folder:

```lua
function greets(name)
    print("[Lua] Hello "..name)
end

function my_sin_int(x)
    print("[Lua] "..math.sin(x))
end

function is_true(b)
    print("[Lua] ", b == true)
end

function my_sin_float(x)
    print("[Lua] "..math.sin(x))
end

function both_sin(x1, x2)
    my_sin_float(x1)
    my_sin_int(x2)
end

function all(name, b, f, i)
    greets(name)
    is_true(b)
    my_sin_float(f)
    my_sin_int(i)
    return 1234
end

function add_test()
    print("[Lua] "..mymath.add(1, 2))
end

```

```cpp
#include <string.h>
#include "LuaInCpp.hpp"

// To call a C++ function in Lua, you have to use the Lua API
// Here's an example:
int add(lua_State *l)
{
    int n = lua_gettop(l); // get the number of arguments

    if (n != 2) {
        lua_pushliteral(l, "bad number of arguments");
        lua_error(l);
    }

    int a = lua_tointeger(l, 1); // get first argument
    int b = lua_tointeger(l, 2); // get second arument

    std::cout << "[C++] " << a << " + " << b << std::endl;
    lua_pushinteger(l, a + b); // the return value
    return 1; // number of argument returned
}

int main()
{
    Lua l;
    l.openLibs();

    l.add("add", &add, "mymath");

    if (l.loadFile("test.lua")) {
        LuaFunction<void(const char *)> greets(l, "greets");
        char *s = strdup("Frodo"); // works with not const too
        greets(s);

        LuaFunction<void(int)> my_sin(l, "my_sin_int");
        long a = 0; // works with long too
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
```

Compile and run like this:
```sh
make test
./test
```

And the output will be:
```
[Lua] Hello Frodo
[Lua] 0.0
[Lua] 0.74570521217672
[Lua] 	false
[Lua] 0.74570521217672
[Lua] -0.75680249530793

[Lua] Hello Frodo
[Lua] 	false
[Lua] 0.74570521217672
[Lua] -0.75680249530793
1234

[C++] 1 + 2
[Lua] 3
```

## What is currently being done ?

This library is able to do:

* Injecting C++ values, functions and tables in a lua instance
* Call thoses C++ functions in lua
* Call lua functions in C++ (cannot call functions with multiple return values for now)

## Known issues

### Why can't I compile it in a shared library ?

To compile this project into a shared library, you must also have a shared library of lua itself. For that, you can go [here](https://www.lua.org/ftp/) to download the source code of your favorite version of lua and tweak the `Makefile` in the `src` folder to create a `liblua.so` and place it next to the `liblua.a` already installed on your system

Then you can have this library in a shared format like that:
```sh
make libluaincpp.so
```

### Other issues

If you have any idea on how to solve these problems or you want to contribute, please open an issue, I'll be happy to discuss it with you

- Can't call lua functions with multiple return values
- The library isn't installed on the machine for now, I believe it's only a few Makefile changes and it would be okay

## Support me

You can star this repository, follow me or buy me a [coffee](https://ko-fi.com/pl0xxxy)
