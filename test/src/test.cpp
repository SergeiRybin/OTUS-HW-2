#define BOOST_TEST_MODULE static library test // Defines the name of the program which is used in the messages
#include <boost/test/unit_test.hpp>
#include <filter.hpp>
#include <ip.hpp>

BOOST_AUTO_TEST_SUITE(MainSuite)

BOOST_AUTO_TEST_CASE(IpInputFilter)
{
    BOOST_TEST(filtIPStr("1.2.3.4\t1\t2") == "1.2.3.4");
}

BOOST_AUTO_TEST_CASE(IpParse)
{
    IP ip = makeIP("0.12.34.56");
    BOOST_TEST(0 == ip[0]);
    BOOST_TEST(12 == ip[1]);
    BOOST_TEST(34 == ip[2]);
    BOOST_TEST(56 == ip[3]);
}

BOOST_AUTO_TEST_CASE(PrintIP)
{
    const std::string ipstr = "0.12.34.56";
    IP ip = makeIP(ipstr);
    BOOST_TEST(ipstr == toString(ip));
}

BOOST_AUTO_TEST_CASE(FilterIP)
{
    std::vector<IP> ips;

    ips.push_back(makeIP("12.2.3.4"));
    ips.push_back(makeIP("13.2.3.4"));
    ips.push_back(makeIP("1.2.3.4"));
    ips.push_back(makeIP("15.2.3.4"));

    auto selIPs = filter(ips, 13, 2);
    BOOST_TEST(selIPs.size() == 1);
    BOOST_TEST(selIPs.at(0)[0] == 13);
    BOOST_TEST(selIPs.at(0)[1] == 2);
    BOOST_TEST(selIPs.at(0)[2] == 3);
    BOOST_TEST(selIPs.at(0)[3] == 4);
}

BOOST_AUTO_TEST_SUITE_END()