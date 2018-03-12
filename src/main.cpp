#include <iostream>
#include <cctype>

#include <frode/ListTool2b.h>
#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>
#include <gruppe32/App.hpp>

int main(int argc, char* argv[]) 
{
    using namespace gruppe32;

    auto ctx = DB::Context{
        DB::Idrettene{},
        DB::Spillerne{}
    };
    App::run(ctx);
    return 0;
}