#include <iostream>

#include <test_Parser.cpp>
#include <test_Valid.cpp>


int main() 
{
    using namespace gruppe32;

    test_Valid();
    test_Parser();

	std::string wait;
    std::cin >> wait;
    return 0;
}