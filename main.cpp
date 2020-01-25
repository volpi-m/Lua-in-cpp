#include <string>
#include "Lua.hpp"

int main()
{
    try {
	Lua lua("test.lua");
	FunctionInfo f1(0, {}, "greets");
	lua.call(f1);
	/*
	std::vector<std::string> types{"c"};
	FunctionInfo f(1, types, "catHello");
	lua.call(f, "Ouais ");

	std::vector<std::string> types2{"x", "x"};
	FunctionInfo f2(2, types2, "add");
	std::vector<std::any> r = lua.call(f2, 15, 42);

	for (auto a : r)
	    std::cout << std::any_cast<long long int>(a) << std::endl;
	*/
	std::vector<std::string> types3{"x", "c", "d", "b", "x"};
	FunctionInfo f3(1, types3, "returnAllType");
	std::vector<std::any> r2 = lua.call(f3, 1);
	for (size_t i = 0; i < types3.size(); i++) {
	    if (types3[i] == "x")
		std::cout << std::any_cast<long long>(r2[i]) << std::endl;
	}
    } catch (std::exception &e) {
	std::cerr << e.what() << std::endl;
    }
    return 0;
}
