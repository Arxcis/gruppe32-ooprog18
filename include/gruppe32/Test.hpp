#pragma once

#include <iostream>

/// <summary> Collection of all test helper-functions </summary>
namespace gruppe32::Test 
{

template<class N, class Msg, class Expected, class Result>
constexpr auto printFailed(const N n, const  Msg msg, const Expected expected, const Result result)
{
    std::cout << "-- test " << n << ": "
              << msg
              << " Expected: " << expected 
              << " | Result: " << result 
              << " | FAILING TEST"
              << '\n';
};

template<class N, class Msg, class Expected, class Result>
constexpr auto printSuccess(const N n, const  Msg msg, const Expected expected, const Result result)
{
    std::cout << "-- test " << n << ": "
              << msg 
              << " Expected: " << expected
              << " | Result: " << result 
              << " | SUCCESS"
              << '\n';
};

}