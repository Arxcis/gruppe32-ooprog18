#include <iostream>
#include <cctype>
#include <array>
#include <vector>
#include <unordered_map>

#include <frode/ListTool2b.h>

namespace gruppe32::DB  
{
using size_t = std::size_t;

class Spillerne 
{
    size_t count;
public:
    frode::List data{ frode::Sorted };
};


class Idrettene 
{
    size_t count;
public:
    frode::List data { frode::Sorted };
};

struct Context 
{
    Idrettene idrettene;
    Spillerne spillerne;
};


} // end namespace 

namespace gruppe32::IO  
{
    using namespace gruppe32;

    void printMenu(const std::unordered_map<App::CommandID, App::Command>& commands) {

    }
    auto readCommand(const std::unordered_map<App::CommandID, App::Command>& validCommands) {
        std::string commandstring{};
        for(;;) 
        {
            std::getline(std::cin, commandstring);
            if (commandstring.size() != 1) {
                std::cout << "commandstring string too long\n";
                continue;
            }

            for(const auto& command : validCommands) {
                std::cout << "command: " << command.first << " commandtext" << command.second.helptext<< '\n';
                if (std::tolower(command.first) == (commandstring[0])) {
                    return command;
                }
            }
            std::cout << "command not valid\n";
        }
    }
}

namespace gruppe32::App 
{
using namespace gruppe32;

enum ReturnCode {
    AGAIN,
    BACK,
    EXIT   
};

enum CommandID : char {
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


ReturnCode skrivAlleSpillere(DB::Context ctx) {}
ReturnCode skrivSpiller(DB::Context ctx, const size_t number) {}
ReturnCode skrivSpiller(DB::Context ctx, const char * name) {}

void run(DB::Context ctx) 
{
    const std::unordered_map<CommandID, Command> mainCommands 
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

        }
    }
}

} // end namespace


int main(int argc, char* argv[]) 
{
    using namespace gruppe32;

    auto ctx = DB::Context{
        .idrettene = DB::Idrettene{},
        .spillerne = DB::Spillerne{}
    };
    App::run(ctx);
    return 0;
}