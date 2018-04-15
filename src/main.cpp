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

int main(int argc, char* argv[]) 
{
    //===================================================================================
    // SET UP CONTEXTS
    //===================================================================================
    auto seedContext     = DB::Context();
    auto fileContext     = DB::Context();
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



    //===================================================================================
    // CONTEXT SELECTION
    //===================================================================================

    auto ctxMap = std::unordered_map<std::string, DB::Context&> {
        {"test", testPrintsContext },
        {"seed", seedContext },
        {"file", fileContext } 
    };

    std::string ctxSelector = "file";  // <-- file is default argument
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
            return -1;
        }
        ctxSelector = argv[1];

        if (ctxMap.find(ctxSelector) == ctxMap.end()) 
        {
            IO::printline(ctxSelector, " option does not exist");
            return -1;
        }
    }
    IO::printline("Using context:", ctxSelector);
    auto ctx = ctxMap.at(ctxSelector);

    //===================================================================================
    // READ FILE only for "seed" and "file"
    //===================================================================================
    const string pathSeedIdrettene = "./data/read/seed-idrettene.yml";
    const string pathSeedSpillerene = "./data/read/seed-spillerene.yml";
    const string pathDataIdrettene = "./data/read-write/idrettene.yml";
    const string pathDataSpillerene = "./data/read-write/spillerene.yml";

    // Read from seed
    if (ctxSelector == "seed")
    {
        IO::printline("Reading mandatory seed data @", pathSeedIdrettene);
        App::readIdrettene(seedContext.idrettene, pathSeedIdrettene);
        
        IO::printline("Reading mandatory seed data @", pathSeedSpillerene);
        App::readSpillerene(seedContext.spillerene, pathSeedSpillerene);
    }

    // Read from existing file
    if (ctxSelector == "file")
    {
        IO::printline("Reading existing data @", pathDataIdrettene);
        App::readIdrettene(fileContext.idrettene, pathDataIdrettene);

        IO::printline("Reading existing data @", pathDataSpillerene);
        App::readSpillerene(fileContext.spillerene, pathDataSpillerene);
    }


    //===================================================================================
    // RUN APP
    //===================================================================================
    Terminal::run(ctx);


    //===================================================================================
    // WRITE to FILE (only for "seed" and "file")
    //===================================================================================
    if (ctxSelector == "seed" || ctxSelector == "file") 
    {
        IO::printline("Writing existing data @", pathDataIdrettene);
        App::writeIdrettene(ctx.idrettene, pathDataIdrettene);

        IO::printline("Writing existing data @", pathDataSpillerene);
        App::writeSpillerene(ctx.spillerene, pathDataSpillerene);
    }
    IO::waitForEnterPress();
    return 0;
}
