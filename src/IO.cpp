#include <gruppe32/IO.hpp>

namespace gruppe32::IO  
{

void printline()
{  
    std::cout << '\n';    
}


template<class Arg>
constexpr void printline(Arg arg)
{  
    std::cout << arg << '\n';    
}


template<class Arg, class ...Args>
constexpr void printline(Arg arg, Args ... args)
{ 
    std::cout << arg << ' ';
    printline(std::forward<Args>(args)...);  
}


void printSubMenu(const CommandMap & commands, const std::string & title, const std::string & parentTitle)
{
    printMenu(commands, parentTitle + " -> " + title);
}


void printMenu(const CommandMap & commands, const std::string & title)
{
    const std::size_t columnSymbolWidth = 6;
    printline();
    printline("*********************************************************");
    printline("** ", title);
    printline("*********************************************************");

    for (const auto&[_, command] : commands) {
        std::cout << "*   "
            << std::setw(columnSymbolWidth)
            << std::left
            << command.symbol
            << " - "
            << command.help << '\n';
    }
    printline("*********************************************************");
}


auto readCommand(const CommandMap& validCommands)  -> CommandPair {
    std::string commandString{};
    for(;;) 
    {
        std::getline(std::cin, commandString);
        if (commandString.size() > 1) {
            printline("commandString string too long");
            continue;
        }

        if (commandString.size() < 1) {
            printline("Please type something");
            continue;
        }

        for(const auto& command : validCommands) {
            if (std::tolower(command.first) == (commandString[0])) {
                return command;
            }
        }
        printline("Command not valid");
    }
}


auto readEitherCommandNumberName(const CommandMap & validCommands) -> CommandPair
{
    std::string commandString{};
    for (;;)
    {
        std::getline(std::cin, commandString);
        

        for (const auto& command : validCommands) {
                
            if (std::tolower(command.first) == (commandString[0])) {
                return command;
            }
        }
        printline("Command not valid");
    }
    return CommandPair();
}


auto readEitherCommandName(const CommandMap & validCommands) -> CommandPair
{

    return CommandPair();
}

} // end namespace