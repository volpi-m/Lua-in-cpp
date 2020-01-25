#include <string>
#include "Lua.hpp"

int main()
{
    Lua lua("example.lua");
    FunctionInfo f1(1, {}, "greets");
    lua.call(f1, "Frodo");

    std::vector<std::string> returnTypes{"x"};
    FunctionInfo f2(2, returnTypes, "add");
    std::vector<std::any> ret = lua.call(f2, 15, 42);
 
    std::cout << "15 + 42 = " << std::any_cast<long long>(ret[0]) << std::endl;
}
