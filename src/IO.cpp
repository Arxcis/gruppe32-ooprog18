#include <gruppe32/IO.hpp>

namespace gruppe32::IO  
{
using namespace gruppe32;

void printMenu(const std::unordered_map<App::CommandID, App::Command>& commands) {

}

auto readCommand(const std::unordered_map<App::CommandID, App::Command>& validCommands)  -> std::pair<App::CommandID, App::Command> {
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