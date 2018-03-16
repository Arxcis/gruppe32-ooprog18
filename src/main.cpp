#include <iostream>
#include <cctype>

#include <frode/ListTool2b.h>
#include <gruppe32/DB.hpp>
#include <gruppe32/Terminal.hpp>

int main(int argc, char* argv[]) 
{
    using namespace gruppe32;

    auto ctx = DB::Context{};
    
    Terminal::run(ctx);
    return 0;
}