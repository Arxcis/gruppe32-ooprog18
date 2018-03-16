#include <iostream>
#include <cctype>
#include <unordered_map>
#include <string>

#include <frode/ListTool2b.h>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>
#include <gruppe32/Terminal.hpp>
using namespace gruppe32;

const std::string DEFAULT_CONTEXT = "default";

int main(int argc, char* argv[]) 
{
    //===================================================================================
    // SET UP CONTEXTS
    //===================================================================================
    auto myContext = DB::Context();
    myContext.spillerene.data->add(new DB::Spiller(4, "Ola Nordmann", "Bergen, Norway"));
    myContext.spillerene.data->add(new DB::Spiller(5, "Kari Nordmann", "Trondheim, Norway"));
    myContext.spillerene.data->add(new DB::Spiller(6, "Tølløf Krambakk", "Kristiansund, Norway"));
    myContext.spillerene.data->add(new DB::Spiller(7, "Hanz Bak", "Berlin, Germany"));

    auto ctxMap = std::unordered_map<std::string, DB::Context&>{
        {DEFAULT_CONTEXT,   DB::Context()},
        {"myContext",       myContext}
    };

    //===================================================================================
    // CONTEXT SELECTION
    //===================================================================================
    std::string ctxSelector = DEFAULT_CONTEXT;
    if (argc > 1)
    {
        if (argc > 2)
        {
            IO::printline("Too many arguments passed!");
            IO::printline("Usage: \"gruppe32.exe <contextKey>\"");
            IO::printline();
            IO::printline("Available contexts are:");
            for (auto[key, _] : ctxMap)
            {
                IO::printline("    -", "\""+key+"\"");
            }
            IO::printline();
        }
        ctxSelector = argv[1];
    }
    auto ctx = ctxMap.at(ctxSelector);
    IO::printline("Using context:", ctxSelector);

    //===================================================================================
    // RUN APP
    //===================================================================================
    Terminal::run(ctx);
    return 0;
}
