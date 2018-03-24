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

void newpage() 
{
    for(size_t i = 0; i < 40; ++i) {
        IO::printline();
    }
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

void dividerHeading(const std::string& heading, char c, size_t count)
{
    std::string divider(count, c);

    std::size_t dividermid    = count / 2;
    std::size_t headingoffset = heading.size() / 2;

    divider[dividermid - headingoffset - 1] = ' ';
    
    int i = 0;
    for (char c : heading) {
        divider[dividermid - (headingoffset) + (i++)] = c; 
    }
    divider[dividermid + headingoffset+1 ] = ' ';

    IO::printline(divider);
}


void printMenu(const CommandMap & commands, const std::string & title)
{
    //newpage();
    const std::size_t columnSymbolWidth = 6;

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


auto readNumber(std::string fieldName) -> size_t
{
    std::string commandString{};
    for (;;)
    {
        std::cout << fieldName << ": ";
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


auto readName(std::string fieldName) -> std::string
{
    std::string maybeName{};
    for (;;)
    {
        std::cout << fieldName << ": ";

        std::getline(std::cin, maybeName);

        if (Valid::isName(maybeName)) 
        {
            return maybeName;
        }
        printline("Not valid name!");
    }
}

auto readAddress() -> std::string
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

auto readFilepath(std::string fieldName) -> std::string
{
    return IO::readName(fieldName);
}

void waitForAnyKey()
{
    IO::printline("Press enter to continue....");
    std::cin.get();
}

} // end namespace

namespace gruppe32 
{

void IO::printMenu(const std::vector<IO::CMD> & commands, const std::string & title)
{
    //newpage();
    const std::size_t columnSymbolWidth = 16;

    IO::divider('*', 80);
    IO::printline("** ", title);
    IO::divider('*',80);

    for (const auto[id, textshort, textlong] : commands) {
        std::cout << "*   "
            << std::setw(columnSymbolWidth)
            << std::left
            << textshort
            << " - "
            << textlong << '\n';
    }
    IO::divider('*', 80);
}


auto IO::readCommand(const std::vector<IO::CMD>& validCommands)  -> char 
{
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

        for(const auto [id, textshort, _] : validCommands) {
            if (std::toupper(id) == std::toupper(commandString[0])) {
 
                IO::printline(textshort);
                return id;
            }
        }
        printline("Command not valid");
    }
}

}