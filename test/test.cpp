#include <iostream>

#include <test_Parser.cpp>
#include <test_Valid.cpp>


int main() 
{
    using namespace gruppe32;

    std::cout << !test_Valid()?  "test_Valid() -- success" : "test_Valid() -- had errors";
    std::cout << !test_Parser()? "test_Parser() -- success" : "test_Parser() -- had errors";
    return 0;
}