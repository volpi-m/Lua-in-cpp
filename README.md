# C++ encapsulation of Lua's C API (the function calling part)

With this only `Lua.hpp` file, you can call basic functions from a Lua script in your C++ code, not all functions however.

Might be a good tool to use when you want to script some part of your C++ project, like doing AI in a game ?

Tested with Lua 5.3, Ubuntu 19.04, C++17 and g++ 8.3 (won't work without C++17).

## Parameter types

For now, when you want to call a Lua function you can use: `char *`, `long long int`, `double` and `bool` types from C++.

You can't use table in you Lua functions because I haven't figured how to get a table in Lua from C++ yet.

You don't need to specify the types of your parameter, just give them, C++ template system will figure types on its own.
However you need to specify how many arguments you want to use.

## Return Types

Your Lua code can return as much value as it want, they'll be stored in `std::any` (that's why you need C++17).

You can get: `char *`, `long long int`, ` double` and `bool` as return types in C++.

You need to specify the types of each value returned by the Lua function in a vector
(explained [here](https://github.com/matteovol/Lua-in-cpp#the-functioninfo-structure)).

See [here](https://github.com/matteovol/Lua-in-cpp#some-error-cases) for some error cases linked to return values.

## Call a Lua function

So now we're coming to the real part, calling a function.

### The FunctionInfo structure

The `FunctionInfo` structrue is used to contain informations about the function you want to call, such as the number of parameter,
the name of the function and a vector for return types.

Use `FunctionInfo` with a simple function in Lua:
```lua
function greets(name)
    print("Hello " .. name)
end
```

Now in C++:
```cpp
#include "Lua.hpp"

int main()
{
    // 1 is the number of parameter
    // {} is an empty vector because our function don't return anything
    // "greets" is the name of the Lua function we want to call
    FunctionInfo f(1, {}, "greets");
}
```

So now, imagine I have a function which return multiple parameter, how am I gonna catch'em ?
Good question, let's find out !

Let's pretend I have the following function in Lua:
```lua
function returnTypes(a)
    return a, "2", true, 4.5
end
```

```cpp
#include "Lua.hpp"

int main()
{
    // ... Lua initialization

    std::vector<std::string> returnTypes{"x", "c", "b", "d"};
    FunctionInfo f(1, returnTypes, "returnTypes");

    // ... function call
}
```

In FunctionInfo's constructor the second parameter is a list of single character. Each character
represent a type and they are put in the same order as the Lua function is going to return its values.

"Which means ?!"

Which means that in this case, our function return an integer, then a string, then a boolean and finally a double.
You want to return a `double` then an `int`, your vector should looks like this : `{"d", "x"}`

Here is a table to summarize:

Character | C++ type
----------|--------------
"x"       | long long
"c"       | const char *
"b"       | bool
"d"       | double

Every integer is passed and returned as a C++ `long long`.

Every floating point number is passed and returned as a C++ `double`.

To call the function, see below.

### Calling the function

To call a function from C++:
```cpp
int main()
{
    // FunctionInfo initialization

    Lua lua("example.lua");         // Create a Lua object and open "example.lua"
                                    // ready to execute function inside it
    lua.call(f, param1, param2);    // Call a function with param1 and param2 passed.
                                    // f is a FunctionInfo structure, see above for details
}
```

### Catch return values

Values returned from the `call` method are wrapped in a `std::vector` of `std::any` (that's why you need C++17),
so you need to create one:
```cpp
int main()
{
    // FunctionInfo and Lua initialization

    std::vector<std::any> returnValues = lua.call(f, 15, 42); // Let's pretend you're calling "add" with 2 parameters

    std::cout << "15 + 42 = " << std::any_cast<long long>(returnValues[0]) << std::endl;
}
```

### Full example

Now a full example with a Lua file:
```lua
function greets(name)
    print("Hello " .. name)
end

function add(nb1, nb2)
    return nb1 + nb2
end
```

And you C++ source file:
```cpp
#include "Lua.hpp"

int main()
{
    Lua lua("example.lua");

    // Call greets, one parameter, no return value
    FunctionInfo f1(1, {}, "greets");
    lua.call(f1, "Frodo");

    // Call add, two parameter, one return value
    std::vector<std::string> returnTypes{"x"};
    FunctionInfo f2(2, returnTypes, "add");
    std::vector<std::any> ret = lua.call(f2, 15, 42);

    std::cout << "15 + 42 = " << std::any_cast<long long>(ret[0]) << std::endl;
}
```

Output:
```
Hello Frodo
15 + 42 = 57
```

In fact, it's the exact program built by the `build.sh` script.

You can see more example in the `tests` folder of this repository

## Some error cases

The C API crash when you want to call a function with multiple return values but
no parameter for no particular reason. Maybe I'm dumb but I couldn't get it working
