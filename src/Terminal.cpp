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
                { CMD_BACK,         Command{ string(1,CMD_BACK), "Back to last menu" }            },     
                { CMD_QUIT,         Command{ string(1,CMD_QUIT), "Quit the application" }         }   
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
                { CMD_IDRETT_NAVN, Command{  "<navn>",                  "Skriv Idrett med <navn>"} },
                { CMD_BACK,         Command{ string(1,CMD_BACK),        "Back to last menu" }},     
                { CMD_QUIT,         Command{ string(1,CMD_QUIT),        "Quit the application" }}   
            },
        }
    },
    {
        CMD_NY, Command{
            string(1,CMD_NY),
            "Ny Spiller, Idrett eller Divisjon/avdeling", 
            "Ny Spiller",
            {
                { CMD_NY_SPILLER, Command{ string(1,CMD_NY_SPILLER), "Ny Spiller"} },
                { CMD_NY_IDRETT, Command{  string(1,CMD_NY_IDRETT), "Ny Idrett"} },
                { CMD_NY_DIVISJON, Command{string(1,CMD_NY_DIVISJON), "Ny Divisjon/avdeling"} },
                { CMD_BACK,         Command{ string(1,CMD_BACK), "Back to last menu" }},     
                { CMD_QUIT,         Command{ string(1,CMD_QUIT), "Quit the application" }}   
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
                { CMD_BACK,         Command{ string(1,CMD_BACK), "Back to last menu" }},     
                { CMD_QUIT,         Command{ string(1,CMD_QUIT), "Quit the application" }}   
            },
        }
    },

    {   CMD_TERMIN, Command{ string(1,CMD_TERMIN), "Skriv terminListe for en gitt divisjon/avdeling til skjerm eller fil", "Termininfo"}},   
    {
        CMD_KAMP, Command{ 
            string(1,CMD_KAMP),  
            "Skriv (resultatet av) alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil" , 
            "Kampinfo",
            {
                {CMD_KAMP_IDRETT,       Command{ string(1, CMD_KAMP_IDRETT), "Skriv alle kamper for en IDRETT"}},
                {CMD_KAMP_IDRETT_FIL,       Command{ string(1, CMD_KAMP_IDRETT_FIL), "Skriv alle kamper for en IDRETT til fil"}},
                {CMD_KAMP_DIVISJON,     Command{ string(1, CMD_KAMP_DIVISJON), "Skriv alle kamper for en DIVISJON"}},
                {CMD_KAMP_DIVISJON_FIL, Command{ string(1, CMD_KAMP_DIVISJON_FIL), "Skriv alle kamper for en DIVISJON til fil"}},
            },
        }
    },     
    {
        CMD_TABELL, Command{ 
            string(1,CMD_TABELL), 
            "skriv Tabell(er) for en hel idrett eller en divisjon/avdeling til skjerm eller fil",
            "Tabellinfo",
            {
                {CMD_TABELL_IDRETT,       Command{ string(1, CMD_TABELL_IDRETT), "Skriv alle tabell(er) for en IDRETT"}},
                {CMD_TABELL_IDRETT_FIL,   Command{ string(1, CMD_TABELL_IDRETT_FIL), "Skriv alle tabell(er) for en IDRETT til fil"}},
                {CMD_TABELL_DIVISJON,     Command{ string(1, CMD_TABELL_DIVISJON), "Skriv alle tabell(er) for en DIVISJON"}},
                {CMD_TABELL_DIVISJON_FIL, Command{ string(1, CMD_TABELL_DIVISJON_FIL), "Skriv alle tabell(er) for en DIVISJON til fil"}},
            },
        }
    },   
    {   CMD_RESULTAT, Command{ string(1,CMD_RESULTAT),"Lese Resultatliste inn fra fil", "Leser Resultatliste ..."}}, 
    {   CMD_LAG,     Command{ string(1,CMD_LAG), "Data om alle spillerne på et lag", "Laginfo"}},      
    {   CMD_ENDRE,   Command{ string(1,CMD_ENDRE), "Endre/redigere (spillerne på et lag)", "Endre spiller på lag"}},    
    {   
        CMD_SCORERE, Command{ 
            string(1,CMD_SCORERE), 
            "Skriv 10-på-topp liste av toppsCorerne for en gitt divisjon/avdeling eller et gitt lag til skjerm eller fil", 
            "Toppscorere"
        }
    },  
    {   CMD_QUIT,         Command{ string(1,CMD_QUIT), "Quit the application" }}   
};


    std::cout << "App running \n";

// Main menu
for(;;) 
{   
    IO::printMenu(commandMap, "MAIN");
    auto [cmdID, _] = IO::readCommand(commandMap);

    switch(cmdID) 
    {
    case CMD_SPILLER:
    cmdID = [&commandMap, &ctx]() -> CommandID {
        for(;;) 
        {
            auto command = commandMap.at(CMD_SPILLER);
            IO::printMenu(command.subcmd, command.title);
            auto [cmdID, _] = IO::readCommand(command.subcmd);

            App::printSpillereAll(ctx);

            if(cmdID == CMD_BACK || cmdID == CMD_QUIT) {
                return cmdID;
            }
        }
    }();
    break;

    case CMD_IDRETT:
    cmdID = [&commandMap, &ctx]() -> CommandID {
        for(;;) 
        {   
            auto command = commandMap.at(CMD_IDRETT);
            IO::printMenu(command.subcmd, command.title);
            auto [cmdID, _] = IO::readCommand(command.subcmd);
            
            App::printIdretterAll(ctx);

            if(cmdID == CMD_BACK || cmdID == CMD_QUIT) {
                return cmdID;
            }
        }
    }();
    break;

    case CMD_NY: 
    cmdID = [&commandMap, &ctx]() -> CommandID {
        for(;;) 
        {
            auto command = commandMap.at(CMD_NY);
            IO::printMenu(command.subcmd, command.title);
            auto [cmdID, _] = IO::readCommand(commandMap.at(CMD_NY).subcmd);
            
            switch(cmdID) 
            {
            case CMD_NY_SPILLER:
            [&ctx](){
                App::createSpiller(ctx);
            }();
            break;

            case CMD_NY_IDRETT:
            [&ctx](){
                App::createIdrett(ctx);
        
            }();
            break;

            case CMD_NY_DIVISJON:
            [&ctx](){
                App::createDivisjon(ctx);        
            }();
            break;

            case CMD_BACK:
            case CMD_QUIT:
                return cmdID;
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
            auto command = commandMap.at(CMD_FJERN);
            IO::printMenu(command.subcmd, "MAIN > " + command.title);
            auto [cmdID, _] = IO::readCommand(command.subcmd);

            switch(cmdID) 
            {
            case CMD_FJERN_SPILLER:
            [&ctx](){
                App::deleteSpiller(ctx);
            }();
            break;

            case CMD_FJERN_IDRETT:
            [&ctx](){
                App::deleteIdrett(ctx);        
            }();
            break;

            case CMD_FJERN_DIVISJON:
            [&ctx](){
                App::deleteDivisjon(ctx);        
            }();
            break;

            case CMD_BACK:
            case CMD_QUIT:
                return cmdID;

            default:
                assert(false && "Command Should never happen!!");    
            }
        }
    }();
    break;

    case CMD_TERMIN:
    [&commandMap, &ctx](){
        App::printTerminDivisjon(ctx);
    }();    
    break;

    case CMD_KAMP:
    [&commandMap, &ctx](){
        App::printResultatKampDivisjon(ctx);
        /* @TOOD        
        App::printResultatKampIdrett(ctx);
        App::writeResultatKampDivisjon(ctx);
        App::writeResultatKampIdrett(ctx);
        */
    }();
    break;

    case CMD_TABELL:
    [&commandMap, &ctx](){
        App::printTabellDivisjon(ctx); 
        /* @todo 
        App::printTabellIdrett(ctx);
        App::writeTabellDivisjon(ctx);
        App::writeTabellIdrett(ctx);
        */
    }();
    break;

    case CMD_RESULTAT:
    [&commandMap, &ctx](){
        App::readResultatliste(ctx);
    }();
    break;

    case CMD_LAG:
    [&commandMap, &ctx](){
        App::printLagSpillerdata(ctx);
    }();
    break;

    case CMD_ENDRE:
    [&commandMap, &ctx](){
        App::insertLagSpiller(ctx); 
        /* @TODO 
        App::removeLagSpiller(ctx);
        */
    }();
    break;

    case CMD_SCORERE:
    [&commandMap, &ctx](){

        App::printToppscorerTopp10Divisjon(ctx);
        /* @TODO
        App::printToppscorerTopp10Lag(ctx);
        */
    }();
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