#ifndef TYPENAME_H_INCLUDED
#define TYPENAME_H_INCLUDED

#include <typeinfo>
#include <cxxabi.h>

template <typename T>
std::string type_name()
{
    int status;
    char* name = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
    if(status != 0)
        return std::string("#Unknow#");
    else
        return std::string(name);
}

template <typename T>
std::size_t type_hash()
{
    return typeid(T).hash_code();
}

#endif // TYPENAME_H_INCLUDED
