#include <iostream>
#include <cctype>
#include <unordered_map>
#include <string>

#include <frode/ListTool2b.h>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>
#include <gruppe32/Terminal.hpp>
#include <gruppe32/App.hpp>

using namespace gruppe32;

const std::string DEFAULT_CONTEXT = "default";

int main(int argc, char* argv[]) 
{
    //===================================================================================
    // SET UP CONTEXTS
    //===================================================================================
    auto defaultContext    = DB::Context();
    auto mandatoryContext  = DB::Context();
    auto testPrintsContext = DB::Context();
    {
        testPrintsContext.spillerene.data->add(new DB::Spiller(0, "Arto Keininen", "Olou, Finland"));
        testPrintsContext.spillerene.data->add(new DB::Spiller(1, "Tore Sørlund", "Hamar, Norway"));
        testPrintsContext.spillerene.data->add(new DB::Spiller(2, "Gary Newman", "Orlando, Florida, USA"));
        testPrintsContext.spillerene.data->add(new DB::Spiller(3, "Hanz Frem", "Berlin, Germany"));

        testPrintsContext.spillerene.data->add(new DB::Spiller(4, "Ola Nordmann", "Bergen, Norway"));
        testPrintsContext.spillerene.data->add(new DB::Spiller(5, "Kari Nordmann", "Trondheim, Norway"));
        testPrintsContext.spillerene.data->add(new DB::Spiller(6, "Tølløf Krambakk", "Kristiansund, Norway"));
        testPrintsContext.spillerene.data->add(new DB::Spiller(7, "Hanz Bak", "Berlin, Germany"));

        auto idrettFotball = new DB::Idrett("Fotball", DB::Idrett::SEIER_3_UAVGJORT_1_TAP_0);
        idrettFotball->divisjonene.push_back(
            DB::Divisjon
            { "Eliteserien", 
                { 
                    DB::Lag{"Rosenborg Ballklubb", "Trondheim, Norway",{5, 6, 1, 3, 0}},
                    DB::Lag{"Brann", "Bergen, Norway", {4, 7, 2}},
                } 
            });
        idrettFotball->divisjonene.push_back(DB::Divisjon{ "Premier League" });
        testPrintsContext.idrettene.data->add(idrettFotball);

        auto idrettBasket = new DB::Idrett("Basketball", DB::Idrett::SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0);
        idrettBasket->divisjonene.push_back(DB::Divisjon{ "Test" });
        testPrintsContext.idrettene.data->add(idrettBasket);
    }


    // Map contexts
    auto ctxMap = std::unordered_map<std::string, DB::Context&>{
        {DEFAULT_CONTEXT, defaultContext },
        {"testPrints",    testPrintsContext },
        {"seed",          mandatoryContext }
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
            exit(-1);
        }
        ctxSelector = argv[1];

        if (ctxMap.find(ctxSelector) == ctxMap.end()) 
        {
            IO::printline(ctxSelector, " option does not exist");
            exit(-1);
        }
    }

    // Read from file
    if (ctxSelector == "seed")
    {
        App::readIdrettene(mandatoryContext.idrettene,"./data/read/seed-idrettene.yml");
        App::readSpillerene(mandatoryContext.spillerene,"./data/read/seed-spillerene.yml");
    }        


    auto ctx = ctxMap.at(ctxSelector);
    IO::printline("Using context:", ctxSelector);

    //===================================================================================
    // RUN APP
    //===================================================================================
    Terminal::run(ctx);


    if (ctxSelector == "seed") 
    {

    }

    return 0;
}
