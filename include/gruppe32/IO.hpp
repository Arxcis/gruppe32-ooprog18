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

using CommandMap = std::map<Terminal::CommandID, Terminal::Command>;
using CommandPair = std::pair<Terminal::CommandID, Terminal::Command>;


void printSubMenu(const CommandMap& commands, const std::string& title, const std::string& parentTitle = "HOME");
void printMenu(const CommandMap& commands, const std::string& title = "HOME");
auto readCommand(const CommandMap& validCommands) -> CommandPair;

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
