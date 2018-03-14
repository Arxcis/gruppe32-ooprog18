#include <cassert>
#include <gruppe32/Valid.hpp>

#define TEST_SUCCESS 0
#define TEST_ERROR 1

/// <summary> Collection of all test functions </summary>
namespace gruppe32::Test
{

auto validIsAsciiChar()
{
	// Should succeed
	if (!Valid::isAsciiChar("s")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (!Valid::isAsciiChar("A")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (!Valid::isAsciiChar("Z")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (!Valid::isAsciiChar("a")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (!Valid::isAsciiChar("z")) {
		assert(false && "isAsciiChar() failed!");
	}


	// Should fail
	if (Valid::isAsciiChar("ø")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (Valid::isAsciiChar("-")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (Valid::isAsciiChar("ss")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (Valid::isAsciiChar("")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (Valid::isAsciiChar("1")) {
		assert(false && "isAsciiChar() failed!");
	}
	if (Valid::isAsciiChar("0")) {
		assert(false && "isAsciiChar() failed!");
	}

	return TEST_SUCCESS;
}
}

int main() 
{
	using namespace gruppe32;

	auto result = Test::validIsAsciiChar();
    return result;
}