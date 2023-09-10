#pragma once
#include <algorithm>
#include <string>
#include <vector>

const static uint8_t octetsNum = 4;

struct IP
{
    uint8_t octets[octetsNum];
};

IP makeIP(const std::string &s);

bool operator>(const IP &lhs, const IP &rhs);

std::string toString(const IP &lhs);