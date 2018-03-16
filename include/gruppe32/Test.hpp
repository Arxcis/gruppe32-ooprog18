#pragma once

#include <iostream>
#include <iomanip>

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


template<class N, class Msg, class Expected, class Result>
void printFailed(const N n, const  Msg msg, const Expected expected, const Result result)
{
    std::cout << "-- test " 
              << std::right
              << std::setw(2)
              << n 
              << ": "
              << std::setw(50)
              << std::left
              << msg
              << "!! FAILING"
              << " | Result: " << result 
              << " , Expected: " << expected 
              << " !!"
              << '\n';
}


template<class N, class Msg, class Expected>
void printSuccess(const N n, const  Msg msg, const Expected expected)
{
    std::cout << "-- test " 
              << std::right
              << std::setw(2)
              << n 
              << ": "
              << std::setw(50)
              << std::left
              << msg 
              << "   SUCCESS"
              << " | Result: " << expected 
              << '\n';
}


template<class Maybe, class TestN, class Msg>
void assertNot(const Maybe maybe, const TestN testN, const Msg msg) 
{ 
    if (!maybe) {
        printSuccess(testN, msg, "Does not exist.");
    } else {
        printFailed(testN, msg, "Does not exist.", "Exists");
    }
}


template<class Lhs, class Rhs, class TestN, class Msg>
void assertEqual(const Lhs lhs, const Rhs rhs, const TestN testN, const Msg msg) 
{ 
    if (lhs == rhs) {
        printSuccess(testN, msg, "Is Equal");
    } else {
        printFailed(testN, msg, "Is Equal", "Is Not Equal");
    }
}

template<class Maybe, class TestN, class Msg>
void assertTrue(const Maybe maybe, const TestN testN, const Msg msg) 
{ 
    if (maybe == true) {
        printSuccess(testN, msg, "Is True");
    } else {
        printFailed(testN, msg, "Is True", "Is Not True");
    }
}


}