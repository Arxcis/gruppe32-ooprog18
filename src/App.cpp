#include <gruppe32/App.hpp>

namespace gruppe32::App 
{


void run(DB::Context ctx) 
{
    using CommandMap = std::map<CommandID, Command>;
    using string = std::string;

    const CommandMap commandMap
{
    {
        CMD_SPILLER, Command{
            string(1,CMD_SPILLER),
            "Skriv Alle Spillerne eller spiller med <nr> / <navn>", 
            "Info spiller(e)",
            {
                { CMD_SPILLER_ALLE, Command{"skriv Alle Spillerne eller spiller med <nr> / <navn>"} },
                { CMD_BACK,    Command{     string(1,CMD_BACK), "Back" }},     
                { CMD_QUIT,    Command{     string(1,CMD_QUIT), "Quit" }}   
            },
        }
    },
    {
        CMD_IDRETT, Command{
            string(1,CMD_IDRETT),
            "Skriv Alle Idrettene eller idretten med <navn>", 
            "Info Idrett(er)",
            {
                { CMD_IDRETT_ALLE, Command{"skriv Alle Idrettene eller idretten med <navn>"} },
                { CMD_BACK,    Command{     string(1,CMD_BACK), "Back" }},     
                { CMD_QUIT,    Command{     string(1,CMD_QUIT), "Quit" }}  
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
                { CMD_BACK,    Command{     string(1,CMD_BACK), "Back" }},     
                { CMD_QUIT,    Command{     string(1,CMD_QUIT), "Quit" }}  
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
                { CMD_BACK,          Command{ string(1,CMD_BACK), "Back" }},     
                { CMD_QUIT,          Command{ string(1,CMD_QUIT), "Quit" }}
            },
        }
    },

    {CMD_TERMIN, Command{ string(1,CMD_FJERN), "Skriv terminListe for en gitt divisjon/avdeling til skjerm eller fil", "Termininfo"}},   
    {CMD_KAMP,   Command{ string(1,CMD_KAMP),  "Skriv (resultatet av) alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil" , "Kampinfo"}},     
    {CMD_TABELL,  Command{ string(1,CMD_TABELL), "skriv Tabell(er) for en hel idrett eller en divisjon/avdeling til skjerm eller fil", "Tabellinfo"}},   
    {CMD_RESULTAT, Command{ string(1,CMD_RESULTAT),"Lese Resultatliste inn fra fil", "Leser Resultatliste ..."}}, 
    {CMD_LAG,     Command{ string(1,CMD_LAG), "Data om alle spillerne på et lag", "Laginfo"}},      
    {CMD_ENDRE,   Command{ string(1,CMD_ENDRE), "Endre/redigere (spillerne på et lag)", "Endre spiller på lag"}},    
    {CMD_SCORERE, Command{ string(1,CMD_SCORERE), "Skriv 10-på-topp liste av toppsCorerne for en gitt divisjon/avdeling eller et gitt lag til skjerm eller fil", "Toppscorere"}},  
    {CMD_QUIT,    Command{ string(1,CMD_QUIT), "Quit" }}  
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
    cmdID = [&commandMap]() -> App::CommandID {
        for(;;) 
        {
            auto command = commandMap.at(CMD_SPILLER);
            IO::printMenu(command.subcmd, command.title);
            auto [cmdID, _] = IO::readCommand(command.subcmd);

            if(cmdID == CMD_BACK || cmdID == CMD_QUIT) {
                return cmdID;
            }
        }
    }();
    break;

    case CMD_IDRETT:
    cmdID = [&commandMap]() -> App::CommandID {
        for(;;) 
        {   
            auto command = commandMap.at(CMD_IDRETT);
            IO::printMenu(command.subcmd, command.title);
            auto [cmdID, _] = IO::readCommand(command.subcmd);
            
            if(cmdID == CMD_BACK || cmdID == CMD_QUIT) {
                return cmdID;
            }
        }
    }();
    break;

    case CMD_NY: 
    cmdID = [&commandMap]() -> App::CommandID {
        for(;;) 
        {
            auto command = commandMap.at(CMD_IDRETT);
            IO::printMenu(command.subcmd, command.title);
            auto [cmdID, _] = IO::readCommand(commandMap.at(CMD_NY).subcmd);
            
            switch(cmdID) 
            {
            case CMD_NY_SPILLER:
            [&commandMap](){
        
            }();
            break;

            case CMD_NY_IDRETT:
            [&commandMap](){
        
            }();
            break;

            case CMD_NY_DIVISJON:
            [&commandMap](){
        
            }();
            break;

            default:
            break;
            }

            if(cmdID == CMD_BACK || cmdID == CMD_QUIT) {
                return cmdID;
            }
        }
    }();
    break;

    case CMD_FJERN:
    cmdID = [&commandMap]() -> App::CommandID {
        for(;;) 
        {   
            auto command = commandMap.at(CMD_FJERN);
            IO::printMenu(command.subcmd, command.title);
            auto [cmdID, _] = IO::readCommand(command.subcmd);

            switch(cmdID) 
            {
            case CMD_FJERN_SPILLER:
            [&commandMap](){
        
            }();
            break;

            case CMD_FJERN_IDRETT:
            [&commandMap](){
        
            }();
            break;

            case CMD_FJERN_DIVISJON:
            [&commandMap](){
        
            }();
            break;

            default:
            break;
            }

            if (cmdID == CMD_BACK || cmdID == CMD_QUIT) {
                return cmdID;
            }
        }
    }();
    break;

    case CMD_TERMIN:
    [&commandMap](){

    }();    
    break;

    case CMD_KAMP:
    [&commandMap](){

    }();
    break;

    case CMD_TABELL:
    [&commandMap](){

    }();
    break;

    case CMD_RESULTAT:
    [&commandMap](){

    }();
    break;

    case CMD_LAG:
    [&commandMap](){

    }();
    break;

    case CMD_ENDRE:
    [&commandMap](){

    }();
    break;

    case CMD_SCORERE:
    [&commandMap](){

    }();
    break;

    case CMD_QUIT:
    [&commandMap](){

    }();
    break;

    default:
        break;
    }

    if (cmdID == CMD_QUIT) {
        return;
    }
} // end for
} // end App::run()
} // end namespace App