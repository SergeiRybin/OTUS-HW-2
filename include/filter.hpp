#pragma once
#include <algorithm>
#include <ip.hpp>
#include <string>
#include <vector>

std::string filtIPStr(std::string);

template <typename T, typename... Args>
static bool IPSelector(const IP &ip, size_t octet, T t, Args... args)
{
    if (octet < octetsNum)
    {
        return ip.octets[octet] == t && IPSelector(ip, ++octet, args...);
    }
    else
    {
        return true;
    }
}

template <typename T>
static bool IPSelector(const IP &ip, size_t octet, T t)
{
    if (octet < octetsNum)
    {
        return ip.octets[octet] == t;
    }
    else
    {
        return true;
    }
}

template <typename T, typename... Args>
static bool anyIPSelector(const IP &ip, T t, Args... args)
{
    for (size_t i = 0; i < octetsNum; i++)
    {
        if (ip.octets[i] == t)
        {
            return true;
        }
    }
    return anyIPSelector(ip, args...);
}

template <typename T>
static bool anyIPSelector(const IP &ip, T t)
{
    for (size_t i = 0; i < octetsNum; i++)
    {
        if (ip.octets[i] == t)
        {
            return true;
        }
    }
    return false;
}

template <typename... Args>
std::vector<IP> filter(const std::vector<IP> &vec, Args... args)
{
    std::vector<IP> selected;
    std::copy_if(vec.cbegin(), vec.cend(), std::back_inserter(selected),
                 [&](auto ip) { return IPSelector(ip, 0, args...); });
    return selected;
}

template <typename... Args>
std::vector<IP> filterAny(const std::vector<IP> &vec, Args... args)
{
    std::vector<IP> selected;
    std::copy_if(vec.cbegin(), vec.cend(), std::back_inserter(selected),
                 [&](auto ip) { return anyIPSelector(ip, args...); });
    return selected;
}