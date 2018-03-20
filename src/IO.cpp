#include <gruppe32/IO.hpp>

namespace gruppe32::IO  
{

void printline()
{  
    std::cout << '\n';    
}

void printSubMenu(const CommandMap & commands, const std::string & title, const std::string & parentTitle)
{
    printMenu(commands, parentTitle + " -> " + title);
}

void divider(char c, size_t count) 
{
    for(size_t i = 0; i < count; ++i) {
        std::cout << c;   
    }
    std::cout << '\n';

    if (c == '_')
        IO::printline();
}

void printMenu(const CommandMap & commands, const std::string & title)
{
    const std::size_t columnSymbolWidth = 6;
    printline();

    divider('*', 80);
    printline("** ", title);
    divider('*',80);

    for (const auto&[_, command] : commands) {
        std::cout << "*   "
            << std::setw(columnSymbolWidth)
            << std::left
            << command.symbol
            << " - "
            << command.help << '\n';
    }
    divider('*', 80);
}


auto readCommand(const CommandMap& validCommands)  -> CommandPair {
    std::string commandString{};
    for(;;) 
    {
        std::cout << "-> ";
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
            if (std::toupper(command.first) == std::toupper(commandString[0])) {
                return command;
            }
        }
        printline("Command not valid");
    }
}


auto readEitherCommandNumberName(const CommandMap & validCommands) -> CommandPairWithData
{
    std::string commandString{};
    for (;;)
    {
        std::cout << "-> ";
        std::getline(std::cin, commandString);
        
        //TODO put into the ifs
        bool userWroteAscii = Valid::isAsciiChar(commandString);
        bool userWroteName = Valid::isName(commandString);
        bool userWroteNumber = Valid::isUint(commandString);


        if (userWroteAscii)
        {
            Terminal::CommandID writtenCommand = (Terminal::CommandID)std::toupper(commandString[0]);
            if (auto pair = validCommands.find(writtenCommand); pair != validCommands.end())
            {
                return {
                    pair->first, //commandID
                    pair->second, //command
                    0,
                    "NONE | NULL | nullptr | nil | \"\""
                };
            }
            printline("Unknown Asciichar-command!");
            continue;
        }
        else if (userWroteNumber)
        {
            auto cmd = validCommands.at(Terminal::CMD_SPILLER_NR);
            std::stringstream strStream;
            strStream << commandString;
            std::size_t number;
            strStream >> number;
            return{
                Terminal::CMD_SPILLER_NR,
                cmd,
                number,
                "NONE | NULL | nullptr | nil | \"\""
            };
        }
        else if (userWroteName)
        {
            auto cmd = validCommands.at(Terminal::CMD_SPILLER_NAVN);
            return {
                Terminal::CMD_SPILLER_NAVN,
                cmd,
                0,
                commandString
            };
        }
        printline("Unknown Command!!!");
    }
    return CommandPairWithData();
}

auto readEitherCommandName(const CommandMap & validCommands) -> CommandPairWithData
{
    std::string commandString{};
    for (;;)
    {
        std::cout << "-> ";

        std::getline(std::cin, commandString);

        if (Valid::isAsciiChar(commandString))
        {
            Terminal::CommandID writtenCommand = (Terminal::CommandID)std::toupper(commandString[0]);
            if (auto pair = validCommands.find(writtenCommand); pair != validCommands.end())
            {
                return {
                    pair->first, //commandID
                    pair->second, //command
                    0,
                    "NONE | NULL | nullptr | nil | \"\""
                };
            }
            printline("Unknown Asciichar-command!");
            continue;
        }
        else if (Valid::isName(commandString))
        {
            auto cmd = validCommands.at(Terminal::CMD_NAME);
            return {
                Terminal::CMD_NAME,
                cmd,
                0,
                commandString
            };
        }
        printline("Unknown Command!!!");
    }
    return CommandPairWithData();
}


auto readNumber() -> size_t
{
    std::string commandString{};
    for (;;)
    {
        std::cout << "Number: ";
        std::getline(std::cin, commandString);
        
        if (Valid::isUint(commandString))
        {
            std::stringstream strStream;
            strStream << commandString;
            std::size_t number;
            strStream >> number;
            
            return number;
        }
        printline("Not a number.");
    }
    return 0;
}


auto readYear() -> size_t 
{
    std::string commandString{};
    for(;;) 
    {
        std::cout << "Year: ";
        std::getline(std::cin, commandString);

        if (Valid::isYear(commandString)) {
            std::stringstream strStream;
            strStream << commandString;
            std::size_t number;
            strStream >> number;

            return number;
        }
        IO::printline("Not a valid year: 1970-2099");
    }
}


auto readMonth() -> size_t 
{
    std::string commandString{};
    for(;;) 
    {
        std::cout << "Month: ";
        std::getline(std::cin, commandString);
   
        if (Valid::isMonth(commandString)) {
            std::stringstream strStream;
            strStream << commandString;
            std::size_t number;
            strStream >> number;

            return number;
        }
        IO::printline("Not a valid month: 01-12");
    }
}


auto readDay() -> size_t 
{
    std::string commandString{};
    for(;;) 
    {
        std::cout << "Day: ";
        std::getline(std::cin, commandString);

        if (Valid::isDay(commandString)) {
            std::stringstream strStream;
            strStream << commandString;
            std::size_t number;
            strStream >> number;
            
            return number;
        }
        IO::printline("Not a day: 01-31");
    }
}


auto readName() -> std::string 
{
    std::string maybeName{};
    for (;;)
    {
        std::cout << "Name: ";

        std::getline(std::cin, maybeName);

        if (Valid::isName(maybeName)) 
        {
            return maybeName;
        }
        printline("Not valid name!");
    }
}

auto readAdress() -> std::string
{
    std::string maybeAddress{};
    for (;;)
    {
        std::cout << "Address: ";

        std::getline(std::cin, maybeAddress);

        if (Valid::isAddress(maybeAddress))
        {
            return maybeAddress;
        }
        printline("Not valid address!");
    }
}
} // end namespace