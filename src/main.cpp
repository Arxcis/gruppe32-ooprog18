#include <iostream>
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

namespace gruppe32::IO  {}
namespace gruppe32::App 
{

void run(DB::Context ctx) 
{
    std::cout << "App running \n";
}

} // end namespace


int main(int argc, char* argv[]) 
{
    using namespace gruppe32;

    auto ctx = DB::Context{
        .idrettene = DB::Idrettene{},
        .spillerne = DB::Spillerne{}
    };
    App::run(ctx);
    return 0;
}