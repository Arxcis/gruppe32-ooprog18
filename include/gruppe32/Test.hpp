#pragma once

#include <iostream>
#include <utility>
#include <iomanip>
#include <sstream>

/// <summary> Collection of all test helper-functions </summary>
namespace gruppe32::Test 
{

namespace Count
{
    using std::size_t;
    size_t total = 0;
    size_t error = 0;
}


struct Testdata
{
    std::string input;
    bool        expectedResult;
    std::string msg;
};


using std::size_t;
using std::string;

void printResult(const string result, const size_t n)
{
    std::cout << "-- test " 
              << std::right
              << std::setw(2)
              << n 
              << ": "
              << std::setw(50)
              << std::left
              << " | Result: " << result;
}


using std::forward;

void printResultSuccess(const string&& result, const size_t n)
{
    printResult(result, n);
    std::cout << "   SUCCESS\n";
}

void printResultFailed(const string&& result, const size_t n)
{
    printResult(result, n);
    std::cout << "   !!! -------> FAILED\n";
}


template<class MaybeNot>
void assertNot(const MaybeNot maybeNot, const size_t testCount) 
{ 
    using std::stringstream;
    stringstream ss;
    string result = "assertNot -> ";

    ss << maybeNot;
    result += ss.str();

    if (!maybeNot) {
        result += " equals not.";
        printResultSuccess(result, testCount);
    } else {
        result += " equals something";
        printResultFailed(result, testCount);
    }
}


template<class Lhs, class Rhs>
void assertEqual(const Lhs lhs, const Rhs rhs, const size_t testCount) 
{ 
    using std::stringstream;
    stringstream ss;
    string result = "assertEqual -> ";

    ss << lhs << " == " << rhs;
    result += ss.str();

    if (lhs == rhs) {
        result +=  " -> is equal";
        printResultSuccess(result, testCount); 
    } else {
        result += " -> is not equal";
        printResultFailed(result, testCount)
    }
}

template<class MaybeTrue>
void assertTrue(const MaybeTrue maybeTrue, const size_t testCount) 
{ 

    using std::stringstream;
    stringstream ss;
    string result = "assertTrue -> ";

    ss << maybeTrue;
    result += ss.str();

    if (maybeTrue == true) {
        result += " is True";
        printResultSuccess(result, testCount);
    } else {
        result += " is not True";
        printResultFailed(result, testCount);
    }
}


}