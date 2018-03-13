#include <gruppe32/IO.hpp>

namespace gruppe32::IO  
{
using namespace gruppe32;

void printline() 
{  
    std::cout << '\n';    
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