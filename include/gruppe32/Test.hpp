#pragma once

#include <iostream>

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
constexpr auto printFailed(const N n, const  Msg msg, const Expected expected, const Result result)
{
    std::cout << "-- test " << n << ": "
              << msg
              << " | FAILING TEST"
              << " | Expected: " << expected 
              << " , Result: " << result 
              << '\n';
};

template<class N, class Msg, class Expected>
constexpr auto printSuccess(const N n, const  Msg msg, const Expected expected)
{
    std::cout << "-- test " << n << ": "
              << msg 
              << " | SUCCESS"
              << " | Result: " << expected 
              << '\n';
};


}