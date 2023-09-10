#include <ip.hpp>
#include <sstream>
#include <stdexcept>
#include <vector>

IP makeIP(const std::string &s)
{
    IP ip;
    uint8_t i = 0;
    uint8_t lowindex = 0;
    uint8_t currindex = 0;
    std::vector<std::string> parsedOctets;

    for (const auto &ch : s)
    {
        if ('.' == ch)
        {
            parsedOctets.push_back(s.substr(lowindex, currindex - lowindex));
            lowindex = currindex + 1;
        }
        currindex++;
    }

    parsedOctets.push_back(s.substr(lowindex));

    if (parsedOctets.size() != IP_LENGTH)
    {
        goto parseFail;
    }
    for (const auto &str : parsedOctets)
    {
        auto octet = std::stoi(str);
        if (octet < 0 || octet > 0xff)
        {
            goto parseFail;
        }
        ip[i] = octet;
        i++;
    }
    return ip;
parseFail:
    throw std::logic_error(std::string("Cannot parse the following IP: ") + s);
}

std::string toString(const IP &ip)
{
    std::ostringstream ostream;
    for (size_t i = 0; i < IP_LENGTH; i++)
    {
        ostream << std::to_string(ip[i]);
        if (i != IP_LENGTH - 1)
        {
            ostream << ".";
        }
    }
    return ostream.str();
}

bool operator>(const IP &lhs, const IP &rhs)
{
    for (size_t i = 0; i < IP_LENGTH; i++)
    {
        if (lhs[i] == rhs[i])
        {
            continue;
        }
        return lhs[i] > rhs[i];
    }

    return true; //all octets are the same
}