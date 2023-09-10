#pragma once
#include <algorithm>
#include <string>
#include <array>

#ifndef IP_VERSION
#define IPv4
#define IP_LENGTH 4
#else
#define IPv6
#define IP_LENGTH 16
#endif

using IP = std::array<uint8_t, IP_LENGTH>;

IP makeIP(const std::string &s);

bool operator>(const IP &lhs, const IP &rhs);

std::string toString(const IP &lhs);