#include <cassert>
#include <gruppe32/Valid.hpp>

#define TEST_SUCCESS 0
#define TEST_ERROR 1

/// <summary> Collection of all test functions </summary>
namespace gruppe32::Test
{

constexpr auto printFailed = [](const auto n, const auto msg, const auto result, const auto expectedResult)
{
    std::cout << "-- test " << n << ": "
              << msg
              << " -- !_FAIL_! Result: " << result 
              << " Expected result: "    << expectedResult 
              << '\n';
};
constexpr auto printSuccess = [](const auto n, const auto msg, const auto result)
{
    std::cout << "-- test " << n << ": "
              << msg 
              << " -- SUCCESS. Result: " << result 
              << '\n';
};

auto validIsAsciiChar()
{
    struct TestData
    {
        std::string input;
        bool        expectedResult;
        std::string msg;
    };

    std::cout << "\nTesting Valid::isAsciiChar()\n";

    [](auto testFunc, std::vector<TestData> testData) 
    {
        auto count = 0;
        for(const auto [input, expectedResult, msg] : testData) 
        {           
            if (const auto result = testFunc(input); result != expectedResult) {
                printFailed(count, msg, result? "true":"false", expectedResult? "true":"false");
            } 
            else {
                printSuccess(count, msg, result? "true":"false");
            }
            count++;
        }
    } (Valid::isAsciiChar, 
        {
            {"s", true, R"(isAsciiChar("s"))"},
            {"A", true, R"(isAsciiChar("A"))"},
            {"Z", true, R"(isAsciiChar("Z"))"},
            {"a", true, R"(isAsciiChar("a"))"},
            {"z", true, R"(isAsciiChar("z"))"},

            {"ø", false, R"(isAsciiChar("ø"))"}, 
            {" ", false, R"(isAsciiChar(" "))"}, 
            {"-", false, R"(isAsciiChar("-"))"},
            {"ss",false, R"(isAsciiChar("ss"))"},
            {"",  false, R"(isAsciiChar(""))"},
            {"1", false, R"(isAsciiChar("1"))"},
            {"0", false, R"(isAsciiChar("0"))"}
        });

    std::cout << '\n';
    return TEST_SUCCESS;
}
}

int main() 
{
    using namespace gruppe32;

    auto result = Test::validIsAsciiChar();
    return result;
}