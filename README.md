# Lua in C++

## A simple bridge between Lua's API and C++.

This repository is still work in progress but starts to be useable. You can find classes to use Lua's API in C++ and use it to script things into your C++ programs.

This has been tested with C++ 20 on g++, Lua 5.4 and Ubuntu 21.10.

## Installation

Clone this repository and compile the static or shared library (see [this](#known-issues)), then you're free to compile it with your program.

## How to use

Here is a a lua file and a C++ file showing you some of the features that this library does:

```lua
function greets(name)
    print("[Lua] Hello "..name)
end

function main()
    print(mymath.add(1, 2))
end
```

```cpp
#include "LuaInCpp.hpp"

int add(int a, int b)
{
    std::cout << "[C++] " << a << " + " << b << std::endl;
    return a + b;
}

int main()
{
    Lua l;
    l.openLibs();

    l.add("add", &add, "mymath");

    if (l.loadFile("test.lua")) {
        LuaFunction<void(const char *)> greets(l, "greets");
        greets("Frodo");

        l.call("main");
    }
}
```

And the output will be:
```
[Lua] Hello Frodo
[C++] 1 + 2
3
```

## What is currently being done ?

This library is able to do:

* Injecting C++ values, functions and tables in a lua instance
* Call thoses C++ functions in lua
* Call lua functions in C++ (cannot call functions with multiple return values for now)

## Known issues

### Why can't I compile in shared library ?

To compile this project into a shared library, you must also have a shared library of lua itself. For that, you can go [here](https://www.lua.org/ftp/) to download the source code of your favorite version of lua and tweak the `Makefile` in the `src` folder to create a `liblua.so` and place it next to the `liblua.a` already installed on your system

### Other issues

If you have any idea on how to solve these problems or you want to contribute, please open an issue, I'll be happy to discuss it with you

- Can't call lua functions with multiple return values

## Support me

You can star this repository, follow me or buy me a [coffee](https://ko-fi.com/pl0xxxy)
