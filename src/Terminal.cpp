#include <gruppe32/Terminal.hpp>

namespace gruppe32::Terminal 
{

void run(DB::Context& ctx) 
{
    using string = std::string;
    
const Command::Map commandMap
{
    {
        CMD_SPILLER, Command{
            string(1,CMD_SPILLER),
            "Skriv Alle Spillerne eller spiller med <nr> / <navn>", 
            "Info spiller(e)",
            {
                { CMD_SPILLER_ALLE, Command{ string(1, CMD_SPILLER_ALLE), "Skriv Alle Spillerne"} },
                { CMD_SPILLER_NR,   Command{ "<navn>", "Skriv spiller med <navn>"}                },
                { CMD_SPILLER_NAVN, Command{ "<nr>",   "Skriv spiller med <nr>"}                  },
                commandBackPair,
                commandQuitPair
            },
        }
    },
    {
        CMD_IDRETT, Command{
            string(1,CMD_IDRETT),
            "Skriv Alle Idrettene eller idretten med <navn>", 
            "Info Idrett(er)",
            {
                { CMD_IDRETT_ALLE, Command{  string(1,CMD_IDRETT_ALLE), "Skriv Alle Idrettene"} },
                { CMD_IDRETT_NAVN, Command{ "<navn>", "Søk med navn på idrett"} },
                commandBackPair,
                commandQuitPair
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
                commandQuitPair
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
                commandQuitPair
            },
        }
    },

    {   
        CMD_TERMIN, Command { 
            string(1,CMD_TERMIN), 
            "Skriv terminListe for en gitt divisjon/avdeling til skjerm eller fil", 
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
                commandQuitPair
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

// Main menu
for(;;) 
{   
    IO::newpage();
    IO::printMenu(commandMap);
    auto [cmdID, _] = IO::readCommand(commandMap);

    switch(cmdID) 
    {
    case CMD_SPILLER:
    cmdID = [&commandMap, &ctx]() -> CommandID {
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
            case CMD_QUIT:
                return subcmdID;
                break;

            default:
                assert(false && "Command Should never happen!!");
            }

        }
    }();
    break;

    case CMD_IDRETT:
    cmdID = [&commandMap, &ctx]() -> CommandID {
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
            case CMD_QUIT:
                return subcmdID;
                break;

            default:
                assert(false && "Command Should never happen!!");
            }
        }
    }();
    break;

    case CMD_NY: 
    cmdID = [&commandMap, &ctx]() -> CommandID {
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
            case CMD_QUIT:
                return subcmdID;
                break;

            default:
                assert(false && "Command Should never happen!!");
            }
        }
    }();
    break;

    case CMD_FJERN:
    cmdID = [&commandMap, &ctx]() -> CommandID {
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
            case CMD_QUIT:
                return subcmdID;

            default:
                assert(false && "Command Should never happen!!");    
            }
        }
    }();
    break;

    case CMD_TERMIN:
        App::terminliste(ctx);
    break;

    case CMD_KAMP:
        App::resultatene(ctx);
    break;

    case CMD_TABELL:
        App::tabell(ctx); 
    break;

    case CMD_RESULTAT:
        App::readResultatliste(ctx);
    break;

    case CMD_LAG:
        App::printLagSpillerdata(ctx);
    break;

    case CMD_ENDRE:
    cmdID = [&commandMap, &ctx](){
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
            case CMD_QUIT:
                return subcmdID;
                break;

            default:
                assert(false && "Command Should never happen!!");
            }            
        }
    }();
    break;

    case CMD_TOPPSCORE:
        App::topp10(ctx);
    break;

    case CMD_BACK:
        continue;
    case CMD_QUIT:
        break;

    default:
        assert(false && "Command Should never happen!!");
    }

    if (cmdID == CMD_QUIT) {
        return;
    }
} // end for
} // end Terminal::run()
} // end namespace Terminal
