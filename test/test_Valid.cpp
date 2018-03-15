#include <gruppe32/Test.hpp>
#include <gruppe32/Valid.hpp>


namespace gruppe32
{


bool test_ValidIsAsciiChar()
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
                Test::printFailed(count, msg, expectedResult ? "true" : "false", result? "true":"false");
            } 
            else {
                Test::printSuccess(count, msg, expectedResult ? "true" : "false", result? "true":"false");
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
    return true;
}

bool test_Valid() 
{
    using namespace gruppe32;
    int failcount = 0;
    test_ValidIsAsciiChar()? failcount += 1: failcount += 0;
    return failcount == 0;
}

}

