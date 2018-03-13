#pragma once

#include <iostream>
#include <iomanip>
#include <utility>
#include <map>
#include <string>
#include <cctype>
#include <gruppe32/Terminal.hpp>

// Forward declaration
namespace gruppe32::Terminal {
    enum CommandID : char;
    struct Command;
}

namespace gruppe32::IO  
{

/// <summary>	The command map. </summary>
using CommandMap = std::map<Terminal::CommandID, Terminal::Command>;

/// <summary>	The command pair. </summary>
using CommandPair = std::pair<Terminal::CommandID, Terminal::Command>;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Print a sub menu, with the navigation stack in the title. </summary>
/// <param name="commands">   	The available commands of the submenu. </param>
/// <param name="title">	  	The title of this menu. </param>
/// <param name="parentTitle">	(Optional) The parent title, defaults to "HOME". </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void printSubMenu(const CommandMap& commands, const std::string& title, const std::string& parentTitle = "HOME");

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Print a menu with a set of available commands. </summary>
/// <param name="commands">	The available commands in this menu. </param>
/// <param name="title">   	(Optional) The title of this menu, defaults to "HOME". </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void printMenu(const CommandMap& commands, const std::string& title = "HOME");

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Reads a command and checks if it's viable to use based on the command map. </summary>
/// <param name="validCommands">	The valid commands. </param>
/// <returns>	The validated command the user requested. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
auto readCommand(const CommandMap& validCommands) -> CommandPair;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Prints a newline </summary>
/// <remarks>	Halvo, 13/03/2018. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
void printline();


template<class Arg>
constexpr void printline(Arg arg) {  
    std::cout << arg << '\n';    
}

template<class Arg, class ...Args>
constexpr void printline(Arg arg, Args ... args) { 
    std::cout << arg << ' ';
    printline(std::forward<Args>(args)...);  
}

} // end namespace
