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

    if (parsedOctets.size() != octetsNum)
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
        ip.octets[i] = octet;
        i++;
    }
    return ip;
parseFail:
    throw std::logic_error(std::string("Cannot parse the following IP: ") + s);
}

std::string toString(const IP &ip)
{
    std::ostringstream ostream;
    for (size_t i = 0; i < octetsNum; i++)
    {
        ostream << std::to_string(ip.octets[i]);
        if (i != octetsNum - 1)
        {
            ostream << ".";
        }
    }
    return ostream.str();
}

bool operator>(const IP &lhs, const IP &rhs)
{
    for (size_t i = 0; i < octetsNum; i++)
    {
        if (lhs.octets[i] == rhs.octets[i])
        {
            continue;
        }
        return lhs.octets[i] > rhs.octets[i];
    }

    return true; //all octets are the same
}