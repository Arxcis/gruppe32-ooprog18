#include <iostream>

#include <test_Parser.cpp>
#include <test_Valid.cpp>


int main() 
{
    using namespace gruppe32;

    std::cout << (test_Valid()?  "test_Valid() -- success\n" : "test_Valid() -- had errors\n");
    std::cout << (test_Parser()? "test_Parser() -- success\n" : "test_Parser() -- had errors\n");

	std::string wait;
    std::cin >> wait;
    return 0;
}