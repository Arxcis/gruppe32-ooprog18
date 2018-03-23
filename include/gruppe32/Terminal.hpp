#pragma once 

#include <cassert>
#include <string>
#include <iostream>
#include <tuple>
#include <map>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>
#include <gruppe32/App.hpp>


/// <summary> Running you through the menus and accepting commands. </summary>
namespace gruppe32::Terminal
{
using std::string;

enum CommandID : char 
{
    CMD_SPILLER          = 'S',
        CMD_SPILLER_ALLE = 'A',
        CMD_SPILLER_NR   = 'R',
        CMD_SPILLER_NAVN = 'N',
        CMD_SPILLER_ADRESSE = 'A',

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
        CMD_KAMP_IDRETT       = 'W',
        CMD_KAMP_IDRETT_FIL   = 'X',
        CMD_KAMP_DIVISJON     = 'Y',
        CMD_KAMP_DIVISJON_FIL = 'Z',

    CMD_TABELL   = 'T',
        CMD_TABELL_IDRETT       = 'W',
        CMD_TABELL_IDRETT_FIL   = 'X',
        CMD_TABELL_DIVISJON     = 'Y',
        CMD_TABELL_DIVISJON_FIL = 'Z',

    CMD_RESULTAT = 'R',
    CMD_LAG      = 'D',
    CMD_ENDRE    = 'E',
        CMD_ENDRE_LEGG_TIL_SPILLER = 'X',
        CMD_ENDRE_FJERN_SPILLER    = 'Y',

    CMD_TOPPSCORE  = 'C',
        CMD_TOPPSCORE_DIVISJON     = 'W',
        CMD_TOPPSCORE_DIVISJON_FIL = 'X',
        CMD_TOPPSCORE_LAG          = 'Y',
        CMD_TOPPSCORE_LAG_FIL      = 'Z',

    CMD_BACK     = 'B',
    CMD_QUIT     = 'Q',
    CMD_COMMIT   = 'F',
    CMD_SEARCH   = 'S',
    CMD_PRINT   = 'P',
    CMD_NAME     = 'N',
    CMD_FILE     = 'F',
    CMD_NAME_DIVISJON = 'D',
    CMD_NAME_IDRETT = 'I',
    CMD_DATE_DAY = 'A',
    CMD_DATE_MONTH = 'M',
    CMD_DATE_YEAR = 'Y',
    CMD_OPTIONS = 'O'
 };

struct Command {
    using Map = std::map<CommandID, Command>;
    using Pair = std::pair<CommandID, Command>;

    std::string symbol = "<no symbol>";
    std::string help   = "<no help>";
    std::string title  = "<no title>";
    Map subcmd{};
};

static const Command::Pair commandCommitPair       = { CMD_COMMIT, Command{ string(1,CMD_COMMIT), "Fullført!" } };
static const Command::Pair commandBackPair         = { CMD_BACK, Command{ string(1,CMD_BACK), "Back to last menu" }};     
static const Command::Pair commandQuitPair         = { CMD_QUIT, Command{ string(1,CMD_QUIT), "Quit the application"}};   

static const Command::Pair keyCommandSearch        = { CMD_SEARCH,         Command{ "[S]earch",     "Search with given data" }};     
static const Command::Pair keyCommandFile          = { CMD_FILE,           Command{ "[F]ile",     "Write search result to file" }};     
static const Command::Pair keyCommandOptions       = { CMD_OPTIONS,      Command{ "[O]ptions",    "What are my options?" }};     
static const Command::Pair keyCommandPrint         = { CMD_PRINT,      Command{ "[P]rint",    "Print search result" }};     
static const Command::Pair keyCommandBack          = { CMD_BACK,           Command{ "[B]ack",       "Back to previous menu" }};     
static const Command::Pair keyCommandNameIdrett    = { CommandID('I'),  Command{ "[I]drett",  "Type name of Idrett" }};
static const Command::Pair keyCommandNameDivisjon  = { CommandID('D'),  Command{ "[D]ivisjon", "Type name of Divisjon" }};

void run(DB::Context& ctx);

} // end namespace terminal