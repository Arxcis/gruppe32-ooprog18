#include <gruppe32/IO.hpp>

namespace gruppe32::IO  
{
using namespace gruppe32;

void printline() 
{  
    std::cout << '\n';    
}

//  @brief A wrapper for std::cout which adds a \n at the end of each print.
void printMenu(const CommandMap& commands, const std::string& title) 
{
    printline();
    printline("*********************************************************");
    printline("** ", title);
    printline("*********************************************************");

    for (const auto& cmd : commands) {
        printline("*  ",char(cmd.first), " - ", cmd.second.help);
    }
    printline("*********************************************************");
}

auto readCommand(const CommandMap& validCommands)  -> std::pair<App::CommandID, App::Command> {
    std::string commandstring{};
    for(;;) 
    {
        std::getline(std::cin, commandstring);
        if (commandstring.size() > 1) {
            printline("Commandstring string too long");
            continue;
        }

        if (commandstring.size() < 1) {
            printline("Please type something");
            continue;
        }

        for(const auto& command : validCommands) {
            if (std::tolower(command.first) == (commandstring[0])) {
                return command;
            }
        }
        printline("Command not valid");
    }
}
}