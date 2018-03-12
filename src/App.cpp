#include <gruppe32/App.hpp>

namespace gruppe32::App 
{
const static std::unordered_map<CommandID, Command> mainCommands
{

    {
        CMD_SPILLER, Command{"", 
            {
                { CMD_SPILLER_ALLE, Command{""} } 
            }
        }
    },
    {
        CMD_IDRETT, Command{"", 
            {
                { CMD_IDRETT_ALLE, Command{""} }  
            }
        }
    },
    {
        CMD_NY, Command{"", 
            {
                { CMD_NY_SPILLER, Command{""} },
                { CMD_NY_IDRETT, Command{""} },
                { CMD_NY_DIVISJON, Command{""} }
            }
        }
    },
    {
        CMD_NY, Command{"", 
            {
                { CMD_FJERN_SPILLER, Command{""} },
                { CMD_FJERN_IDRETT, Command{""} },
                { CMD_FJERN_DIVISJON, Command{""} } 
            }
        }
    },

    {CMD_TERMIN, Command{  "" }},   
    {CMD_KAMP,   Command{  "" }},     
    {CMD_TABELL,  Command{  "" }},   
    {CMD_RESULTAT, Command{  "" }}, 
    {CMD_LAG,     Command{  "" }},      
    {CMD_ENDRE,   Command{  "" }},    
    {CMD_SCORERE, Command{  "" }},  
    {CMD_BACK,    Command{  "" }},     
    {CMD_QUIT,    Command{  "" }}  
};


void run(DB::Context ctx) 
{
    std::cout << "App running \n";

    // Main menu
    for(;;) 
    {   
        IO::printMenu(mainCommands);
        const auto [key, command] = IO::readCommand(mainCommands);

        switch(key) 
        {
        case CMD_SPILLER:
        
        break;

        case CMD_IDRETT:
        
        break;

        case CMD_NY: 
        {
            auto [_key, _command] = IO::readCommand(mainCommands.at(CMD_NY).subcmd);
            break;
        }

        case CMD_FJERN:
        {
            auto [_key, _command] = IO::readCommand(mainCommands.at(CMD_FJERN).subcmd);
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

        case CMD_BACK:
        
        break;

        case CMD_QUIT:
        
        break;

        default:
            assert(false); // Should never happen!
        }
    }
}

} // end namespace