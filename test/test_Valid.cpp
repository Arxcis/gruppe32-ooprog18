#include <gruppe32/Test.hpp>
#include <gruppe32/Valid.hpp>


namespace gruppe32
{


bool test_ValidIsAsciiChar()
{
    std::vector<Test::Testdata> testTable = 
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
    };

	std::size_t count = 0;

    for(auto [input, expectedResult, msg] : testTable) 
    {   
        if (const auto result = Valid::isAsciiChar(input); result != expectedResult) {
            Test::printFailed(count, msg, expectedResult ? "true" : "false", result? "true":"false");
        } 
        else {
            Test::printSuccess(count, msg, expectedResult ? "true" : "false");
        }
        count++;
    }

    return true;
}


bool test_Valid() 
{
    using namespace gruppe32;
    int failcount = 0;
  
	std::cout << "\nRunning test_ValidIsAsciiChar()\n";
    test_ValidIsAsciiChar()? failcount = 0: failcount += 1;

    std::cout << '\n';
    return failcount == 0;
}

}
