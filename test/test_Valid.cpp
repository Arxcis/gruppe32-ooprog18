#include <gruppe32/Test.hpp>
#include <gruppe32/Valid.hpp>


namespace gruppe32
{


void test_ValidIsAsciiChar()
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

    using std::string;

    for(auto [input, expectedResult, msg] : testTable) 
    {   
        auto maybeTrue = Valid::isAsciiChar(input) == expectedResult;
        Test::assertTrue(maybeTrue, count); 
        count++;
    }
}


void test_Valid() 
{
    using namespace gruppe32;
  
	std::cout << "\nRunning test_ValidIsAsciiChar()\n";
    test_ValidIsAsciiChar();
    std::cout << '\n';
}

}
