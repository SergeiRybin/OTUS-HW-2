#include <cstring>
#include <filter.hpp>
#include <stdexcept>

std::string filtIPStr(std::string s)
{
    auto delPos = s.find("\t");
    if (std::string::npos == delPos)
    {
        throw std::logic_error(std::string("Cannot parse find TAB delimeter in line: ") + s);
    }
    return s.substr(0, delPos);
}