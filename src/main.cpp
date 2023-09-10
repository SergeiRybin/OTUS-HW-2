#include <algorithm>
#include <filter.hpp>
#include <iostream>
#include <ip.hpp>
#include <iterator>
#include <vector>

template <typename Container>
static void printIPs(const Container &cont)
{
    for (const auto &ip : cont)
    {
        std::cout << toString(ip) << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<IP> pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            auto ipStr = filtIPStr(line);
            pool.emplace_back(makeIP(ipStr));
        }

        std::sort(pool.begin(), pool.end(), std::greater<IP>());

        printIPs(pool);

        auto filtered1 = filter(pool, 1);
        printIPs(filtered1);

        auto filtered4670 = filter(pool, 46, 70);
        printIPs(filtered4670);

        auto filteredAny46 = filterAny(pool, 46);
        printIPs(filteredAny46);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}