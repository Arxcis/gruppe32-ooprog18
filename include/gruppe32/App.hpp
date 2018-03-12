#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <unordered_map>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

namespace gruppe32::App 
{

enum ReturnCode 
{
    AGAIN,
    BACK,
    EXIT   
};

enum CommandID : char 
{
    CMD_SPILLER          = 'S',
        CMD_SPILLER_ALLE = 'A',

    CMD_IDRETT          = 'I',
        CMD_IDRETT_ALLE = 'A',

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
    CMD_TABELL   = 'T',
    CMD_RESULTAT = 'R',
    CMD_LAG      = 'D',
    CMD_ENDRE    = 'E',
    CMD_SCORERE  = 'C',
    CMD_BACK     = 'B',
    CMD_QUIT     = 'Q'
 };

struct Command {
    std::string helptext;
    std::unordered_map<CommandID, Command> subcmd{};
};

/**
 * short description. - Doxygen example
 * detailed description.
 * @param int - blah
 * @return int - blah
 */
ReturnCode skrivAlleSpillere(DB::Context ctx);
ReturnCode skrivSpiller(DB::Context ctx, const size_t number);
ReturnCode skrivSpiller(DB::Context ctx, const char * name);
void run(DB::Context ctx);


} // end namespace