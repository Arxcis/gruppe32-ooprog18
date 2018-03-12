#pragma once
#include <cstddef>
#include <frode/ListTool2b.h>

namespace gruppe32::DB  
{
using size_t = std::size_t;

class Spillerne 
{
    size_t count;
public:
    frode::List data{ frode::Sorted };
};


class Idrettene 
{
    size_t count;
public:
    frode::List data { frode::Sorted };
};

struct Context 
{
    Idrettene idrettene;
    Spillerne spillerne;
};


} // end namespace 
