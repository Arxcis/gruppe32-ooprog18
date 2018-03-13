#pragma once 

#include <cassert>
#include <string>
#include <iostream>
#include <map>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>
#include <gruppe32/App.hpp>

namespace gruppe32::Terminal
{

enum CommandID : char 
{
    CMD_SPILLER          = 'S',
        CMD_SPILLER_ALLE = 'A',
        CMD_SPILLER_NR   = 'R',
        CMD_SPILLER_NAVN = 'N',

    CMD_IDRETT          = 'I',
        CMD_IDRETT_ALLE = 'A',
        CMD_IDRETT_NAVN = 'N',

    CMD_NY              = 'N',
        CMD_NY_SPILLER  = 'S',
        CMD_NY_IDRETT   = 'I',
        CMD_NY_DIVISJON = 'D',

    CMD_FJERN              = 'F',
        CMD_FJERN_SPILLER  = 'S',
        CMD_FJERN_IDRETT   = 'I',
        CMD_FJERN_DIVISJON = 'D',

    CMD_TERMIN   = 'L',
    CMD_KAMP     = 'K',
        CMD_KAMP_IDRETT       = 'A',
        CMD_KAMP_IDRETT_FIL   = 'B',
        CMD_KAMP_DIVISJON     = 'C',
        CMD_KAMP_DIVISJON_FIL = 'D',

    CMD_TABELL   = 'T',
        CMD_TABELL_IDRETT       = 'A',
        CMD_TABELL_IDRETT_FIL   = 'B',
        CMD_TABELL_DIVISJON     = 'C',
        CMD_TABELL_DIVISJON_FIL = 'D',

    CMD_RESULTAT = 'R',
    CMD_LAG      = 'D',
    CMD_ENDRE    = 'E',
    CMD_SCORERE  = 'C',
    CMD_BACK     = 'B',
    CMD_QUIT     = 'Q'
 };

struct Command {
    using Map = std::map<CommandID, Command>;
    using Pair = std::pair<CommandID, Command>;

    std::string symbol = "<no symbol>";
    std::string help   = "<no help>";
    std::string title  = "<no title>";
    Map subcmd{};
};


void run(DB::Context& ctx);

} // end namespace terminal