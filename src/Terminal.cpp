#include <gruppe32/Terminal.hpp>

namespace gruppe32::Terminal 
{

using namespace IO;

void run(DB::Context& ctx) 
{
    using string = std::string;

const Command::Map commandMap
{
    {
        CMD_SPILLER, Command{
            string(1,CMD_SPILLER),
            "Skriv informasjon om spillere", 
            "Info spiller(e)",
            {
                { CMD_SPILLER_ALLE, Command{ string(1, CMD_SPILLER_ALLE), "Skriv Alle Spillerne"} },
                { CMD_SPILLER_NR,   Command{ "<navn>", "Skriv spiller med <navn>"}                },
                { CMD_SPILLER_NAVN, Command{ "<nr>",   "Skriv spiller med <nr>"}                  },
                commandBackPair,
            },
        }
    },
    {
        CMD_IDRETT, Command{
            string(1,CMD_IDRETT),
            "Skriv informasjon om idretter", 
            "Info Idrett(er)",
            {
                { CMD_IDRETT_ALLE, Command{  string(1,CMD_IDRETT_ALLE), "Skriv Alle Idrettene"} },
                { CMD_IDRETT_NAVN, Command{ "<navn>", "Søk med navn på idrett"} },
                commandBackPair,
            },
        }
    },
    {
        CMD_NY, Command{
            string(1,CMD_NY),
            "Ny Spiller, Idrett eller Divisjon/avdeling", 
            "Lag ny",
            {
                { CMD_NY_SPILLER, Command{ string(1,CMD_NY_SPILLER), "Ny Spiller" } },
                { CMD_NY_IDRETT, Command{  string(1,CMD_NY_IDRETT), "Ny Idrett"} },
                { CMD_NY_DIVISJON, Command{string(1,CMD_NY_DIVISJON), "Ny Divisjon/avdeling"} },
                commandBackPair,
            },
        }
    },


    {
        CMD_FJERN, Command{
            string(1,CMD_FJERN),
            "Fjern Spiller, Idrett eller Divisjon/avdeling", 
            "Fjern",
            {
                { CMD_FJERN_SPILLER, Command{ string(1,CMD_FJERN_SPILLER), "Fjern Spiller"} },
                { CMD_FJERN_IDRETT,  Command{ string(1,CMD_FJERN_IDRETT), "Fjern Idrett"} },
                { CMD_FJERN_DIVISJON,Command{ string(1,CMD_FJERN_DIVISJON), "Fjern Divisjon/avdeling"} },
                commandBackPair,
            },
        }
    },
    {   
        CMD_TERMIN, Command { 
            string(1,CMD_TERMIN), 
            "Skriv terminliste til skjerm eller fil", 
            "Termininfo"
        }
    },   
    {
        CMD_KAMP, Command{ 
            string(1,CMD_KAMP),  
            "Skriv (resultatet av) alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil" , 
            "Kampinfo"
        }
    },     

    {
        CMD_TABELL, Command{ 
            string(1,CMD_TABELL), 
            "skriv Tabell(er) for en hel idrett eller en divisjon/avdeling til skjerm eller fil",
            "Tabellinfo"
        }
    },   

    {   CMD_RESULTAT, Command{ string(1,CMD_RESULTAT),"Lese Resultatliste inn fra fil", "Leser Resultatliste ..."}}, 
    {   CMD_LAG,      Command{ string(1,CMD_LAG), "Data om alle spillerne på et lag", "Laginfo"}},      
    {   
        CMD_ENDRE, Command{ 
            string(1,CMD_ENDRE), 
            "Endre/redigere (spillerne på et lag)", 
            "Endre spiller på lag",
            {
                {CMD_ENDRE_LEGG_TIL_SPILLER, Command{ string(1, CMD_ENDRE_LEGG_TIL_SPILLER), "Legg til spiller til lag"}},
                {CMD_ENDRE_FJERN_SPILLER,    Command{ string(1, CMD_ENDRE_FJERN_SPILLER),    "Fjern spiller fra lag"}},
                commandBackPair,
            },
        }
    },    
    {   
        CMD_TOPPSCORE, Command{ 
            string(1,CMD_TOPPSCORE), 
            "Skriv 10-på-topp liste av toppsCorerne", 
            "Toppscorere"
        }
    },  
    commandQuitPair
};


const auto menu = std::vector<IO::CMD> {
    cmdSpiller,
    cmdIdrett,
    cmdTermin,
    cmdResultat,
    cmdTabell,
    cmdLag,
    cmdNy,
    cmdFjern,
    cmdLagEndre,
    cmdLesresultat,
    cmdQuit
};


// Main menu
for(;;) 
{   
    IO::newpage();
    IO::printMenu(menu);
    auto cmdid = IO::readCommand(menu);

    switch(cmdid) 
    {
    case cmdSpiller.id:
    cmdid = [&commandMap, &ctx]() -> CommandID {
        for(;;)
        {
            IO::newpage();

            auto command = commandMap.at(CMD_SPILLER);
            IO::printSubMenu(command.subcmd, command.title);
            auto [subcmdID, _, nr, name] = IO::readEitherCommandNumberName(command.subcmd);

            switch (subcmdID)
            {
            case CMD_SPILLER_ALLE:
                App::printSpillereAll(ctx);
                break;

            case CMD_SPILLER_NAVN:
                App::printSpillereByName(ctx, name);
                break;

            case CMD_SPILLER_NR:
                App::printSpillereByNumber(ctx, nr);
                break;

            case CMD_BACK:
                return subcmdID;

            default:
                assert(false && "Command Should never happen!!");
            }

        }
    }();
    break;

    case cmdIdrett.id:
    cmdid = [&commandMap, &ctx]() -> CommandID {
        for(;;) 
        {   
            IO::newpage();

            auto command = commandMap.at(CMD_IDRETT);
            IO::printSubMenu(command.subcmd, command.title);
            auto[subcmdID, _cmd, _nr, name] = IO::readEitherCommandName(command.subcmd);

            switch (subcmdID)
            {
            case CMD_IDRETT_ALLE:
                App::printIdretterAll(ctx);
                break;

            case CMD_NAME:
                App::printIdretterByName(ctx, name);
                break;

            case CMD_BACK:
                return subcmdID;

            default:
                assert(false && "Command Should never happen!!");
            }
        }
    }();
    break;

    case cmdNy.id:
    cmdid = [&commandMap, &ctx]() -> CommandID {
        for(;;) 
        {
            IO::newpage();
            auto command = commandMap.at(CMD_NY);
            IO::printSubMenu(command.subcmd, command.title);
            auto [subcmdID, _] = IO::readCommand(commandMap.at(CMD_NY).subcmd);
            
            switch(subcmdID)
            {
            case CMD_NY_SPILLER:
                App::createSpiller(ctx);
            break;

            case CMD_NY_IDRETT:
                App::createIdrett(ctx);
            break;

            case CMD_NY_DIVISJON:
                App::createDivisjon(ctx);        
            break;

            case CMD_BACK:
                return subcmdID;

            default:
                assert(false && "Command Should never happen!!");
            }
        }
    }();
    break;

    case cmdFjern.id:
    cmdid = [&commandMap, &ctx]() -> CommandID {
        for(;;) 
        {   
            IO::newpage();

            auto command = commandMap.at(CMD_FJERN);
            IO::printSubMenu(command.subcmd, command.title);
            auto [subcmdID, _] = IO::readCommand(command.subcmd);

            switch(subcmdID)
            {
            case CMD_FJERN_SPILLER:
                App::deleteSpiller(ctx);
            break;

            case CMD_FJERN_IDRETT:
                App::deleteIdrett(ctx);        
            break;

            case CMD_FJERN_DIVISJON:
                App::deleteDivisjon(ctx);        
            break;

            case CMD_BACK:
                return subcmdID;

            default:
                assert(false && "Command Should never happen!!");    
            }
        }
    }();
    break;

    case cmdTermin.id:
        App::terminliste(ctx);
    break;

    case cmdResultat.id:
        App::resultatene(ctx);
    break;

    case cmdTabell.id:
        App::tabell(ctx); 
    break;

    case cmdLesresultat.id:
        App::readResultatliste(ctx);
    break;

    case cmdLag.id:
        App::printLagSpillerdata(ctx);
    break;

    case cmdLagEndre.id:
    cmdid = [&commandMap, &ctx](){
        for(;;) 
        {

            IO::newpage();
            auto command = commandMap.at(CMD_ENDRE);
            IO::printSubMenu(command.subcmd, command.title);
            auto [subcmdID, _] = IO::readCommand(commandMap.at(CMD_ENDRE).subcmd);

            switch(subcmdID)
            {
            case CMD_ENDRE_LEGG_TIL_SPILLER:
                App::insertLagSpiller(ctx); 
            break;

            case CMD_ENDRE_FJERN_SPILLER:
                App::removeLagSpiller(ctx);
            break;

            case CMD_BACK:
                return subcmdID;

            default:
                assert(false && "Command Should never happen!!");
            }            
        }
    }();
    break;

    case cmdQuit.id:
        return;

    default:
        assert(false && "Command Should never happen!!");
    }

} // end for
} // end Terminal::run()
} // end namespace Terminal
