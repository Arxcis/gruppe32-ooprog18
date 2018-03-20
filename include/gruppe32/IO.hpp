#pragma once

#include <iostream>
#include <iomanip>
#include <utility>
#include <tuple>
#include <map>
#include <string>
#include <cctype>
#include <sstream>

#include <gruppe32/Terminal.hpp>
#include <gruppe32/Valid.hpp>

// Forward declaration
namespace gruppe32::Terminal 
{
    enum CommandID : char;
    struct Command;
}



/// <summary> Input and Ouput functions </summary>
namespace gruppe32::IO  
{

/// <summary>   The command map. </summary>
using CommandMap = std::map<Terminal::CommandID, Terminal::Command>;

/// <summary>   The command pair. </summary>
using CommandPair = std::pair<Terminal::CommandID, Terminal::Command>;

using CommandPairWithData = std::tuple<Terminal::CommandID,
                                       Terminal::Command,
                                       std::size_t,         
                                       std::string>;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Print a sub menu, with the navigation stack in the title. </summary>
/// <param name="commands">     The available commands of the submenu. </param>
/// <param name="title">        The title of this menu. </param>
/// <param name="parentTitle">  (Optional) The parent title, defaults to "HOME". </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void printSubMenu(const CommandMap& commands, 
                  const std::string& title, 
                  const std::string& parentTitle = "HOME");



void divider(char c, size_t count=80);






////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Print a menu with a set of available commands. </summary>
/// <param name="commands"> The available commands in this menu. </param>
/// <param name="title">    (Optional) The title of this menu, defaults to "HOME". </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void printMenu(const CommandMap& commands, 
               const std::string& title = "HOME");

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Read a command and check if it's viable to use based on the command map. </summary>
/// <param name="validCommands">    The valid commands. </param>
/// <returns>   The validated command the user requested. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
auto readCommand(const CommandMap& validCommands) -> CommandPair;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Read either a command, a number or a name, 
///             then check if it's viable to use based on the command map. </summary>
/// <param name="validCommands">    The valid commands. </param>
/// <returns>   Either the command, number or name. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
auto readEitherCommandNumberName (const CommandMap& validCommands) -> CommandPairWithData;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Read either a command or a name, 
///             then check if it's viable to use based on the command map. </summary>
/// <param name="validCommands">    The valid commands. </param>
/// <returns>   Either the command or the name. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
auto readEitherCommandName(const CommandMap& validCommands) -> CommandPairWithData;

auto readEitherCommandNumber(const CommandMap & validCommands) -> CommandPairWithData;


auto readName() -> std::string;
auto readYear() -> size_t;
auto readMonth() -> size_t;
auto readDay() -> size_t ;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Prints a newline </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
void printline();

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Print a line with the s given argument. </summary>
/// <typeparam name="Arg">  Type of the argument. </typeparam>
/// <param name="arg">  The content of the line to be printed. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Arg>
constexpr void printline(Arg arg)
{
    std::cout << arg << '\n';
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Print a line with all the given arguments. </summary>
/// <typeparam name="Arg">      the argument list head-Type. </typeparam>
/// <typeparam name="...Args">  the argument list tail-Type. </typeparam>
/// <param name="arg">  The head of argument list. </param>
/// <param name="args"> The tail of arguments which is passed on recursively. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Arg, class ...Args>
constexpr void printline(Arg arg, Args ... args)
{
    std::cout << arg << ' ';
    printline(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Print a line with the s given argument. </summary>
/// <typeparam name="Arg">  Type of the argument. </typeparam>
/// <param name="arg">  The content of the line to be printed. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Arg>
constexpr void printlineNoSpace(Arg arg)
{
    printline(arg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>   Print a line with no spaces between all the given arguments. </summary>
/// <typeparam name="Arg">      the argument list head-Type. </typeparam>
/// <typeparam name="...Args">  the argument list tail-Type. </typeparam>
/// <param name="arg">  The head of argument list. </param>
/// <param name="args"> The tail of arguments which is passed on recursively. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Arg, class ...Args>
constexpr void printlineNoSpace(Arg arg, Args ... args)
{
    std::cout << arg;
    printlineNoSpace(std::forward<Args>(args)...);
}

} // end namespace
