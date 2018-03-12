#include <gruppe32/App.hpp>

namespace gruppe32::App 
{
const static std::map<CommandID, Command> mainCommands
{

    {
        CMD_SPILLER, Command{"skriv Alle Spillerne eller spiller med <nr> / <navn>", 
            {
                { CMD_SPILLER_ALLE, Command{"skriv Alle Spillerne eller spiller med <nr> / <navn>"} },
                {CMD_BACK,    Command{  "Back" }},     
                {CMD_QUIT,    Command{  "Quit" }}  
            }
        }
    },
    {
        CMD_IDRETT, Command{"skriv Alle Idrettene eller idretten med <navn>", 
            {
                { CMD_IDRETT_ALLE, Command{"skriv Alle Idrettene eller idretten med <navn>"} },
                {CMD_BACK,    Command{  "Back" }},     
                {CMD_QUIT,    Command{  "Quit" }}  
            }
        }
    },
    {
        CMD_NY, Command{"Ny Spiller, Idrett eller Divisjon/avdeling", 
            {
                { CMD_NY_SPILLER, Command{"Ny Spiller"} },
                { CMD_NY_IDRETT, Command{"Ny Idrett"} },
                { CMD_NY_DIVISJON, Command{"Ny Divisjon/avdeling"} },
                {CMD_BACK,    Command{  "Back" }},     
                {CMD_QUIT,    Command{  "Quit" }}  
            }
        }
    },
    {
        CMD_FJERN, Command{"Fjern Spiller, Idrett eller Divisjon/avdeling", 
            {
                { CMD_FJERN_SPILLER, Command{"Fjern Spiller"} },
                { CMD_FJERN_IDRETT, Command{"Fjern Idrett"} },
                { CMD_FJERN_DIVISJON, Command{"Fjern Divisjon/avdeling"} },
                {CMD_BACK,    Command{  "Back" }},     
                {CMD_QUIT,    Command{  "Quit" }}
            }
        }
    },

    {CMD_TERMIN, Command{  "skriv terminListe for en gitt divisjon/avdeling til skjerm eller fil" }},   
    {CMD_KAMP,   Command{  "skriv (resultatet av) alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil" }},     
    {CMD_TABELL,  Command{  "skriv Tabell(er) for en hel idrett eller en divisjon/avdeling til skjerm eller fil" }},   
    {CMD_RESULTAT, Command{  "lese Resultatliste inn fra fil" }}, 
    {CMD_LAG,     Command{  "Data om alle spillerne på et lag" }},      
    {CMD_ENDRE,   Command{  "Endre/redigere (spillerne på et lag)" }},    
    {CMD_SCORERE, Command{  "skriv 10-på-topp liste av toppsCorerne for en gitt divisjon/avdeling eller et gitt lag til skjerm eller fil" }},  
    {CMD_QUIT,    Command{  "Quit" }}  
};


void run(DB::Context ctx) 
{
    std::cout << "App running \n";

    // Main menu
    for(;;) 
    {   
        IO::printMenu(mainCommands);
        const auto [cmdID, _] = IO::readCommand(mainCommands);

        switch(cmdID) 
        {
        case CMD_SPILLER:
        
        break;

        case CMD_IDRETT:
        
        break;

        case CMD_NY: 
        {
            for(;;) 
            {
                IO::printMenu(mainCommands.at(CMD_NY).subcmd);
                auto [cmdID, _] = IO::readCommand(mainCommands.at(CMD_NY).subcmd);
                
                switch(cmdID) 
                {
                    case CMD_NY_SPILLER:
                    break;

                    case CMD_NY_IDRETT:
                    break;

                    case CMD_NY_DIVISJON:
                    break;

                    default:
                        break;
                }

                if(cmdID == CMD_BACK) {
                    break;
                }
                if (cmdID == CMD_QUIT) {
                    return;
                }
            }
        break;
        }

        case CMD_FJERN:
        {
            for(;;) 
            {   
                IO::printMenu(mainCommands.at(CMD_FJERN).subcmd);
                auto [cmdID, _] = IO::readCommand(mainCommands.at(CMD_FJERN).subcmd);

                if(cmdID == CMD_BACK) {
                    break;
                }
                if (cmdID == CMD_QUIT) {
                    return;
                }
            }        
        break;
        }


        case CMD_TERMIN:
        
        break;

        case CMD_KAMP:
        
        break;

        case CMD_TABELL:
        
        break;

        case CMD_RESULTAT:
        
        break;

        case CMD_LAG:
        
        break;

        case CMD_ENDRE:
        
        break;

        case CMD_SCORERE:
        
        break;

        case CMD_QUIT:
        
        break;

        default:
            break;
        }

        if (cmdID == CMD_QUIT) {
            return;
        }
    }
}

} // end namespace