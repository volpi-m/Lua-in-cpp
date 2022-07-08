#include "LuaFunction.hpp"

template< class ...Args >
class VoidFunction : public LuaFunction<void(Args...)>
{
public:
    VoidFunction(Lua &l, const std::string &fname) :
        LuaFunction<void(Args...)>(l, fname)
    {}

    void operator()(Args... args)
    {
        lua_getglobal(getState(this->_inst), this->_fname.c_str());
        this->intern(args...);
    }
};
