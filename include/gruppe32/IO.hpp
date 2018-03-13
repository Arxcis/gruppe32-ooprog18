#pragma once

#include <iostream>
#include <iomanip>
#include <utility>
#include <map>
#include <string>
#include <cctype>
#include <gruppe32/App.hpp>


// Forward declaration
namespace gruppe32::App {
    enum CommandID : char;
    struct Command;
}

namespace gruppe32::IO  
{
using CommandMap = std::map<App::CommandID, App::Command>;

void printMenu(const CommandMap& commands, const std::string& title);
auto readCommand(const CommandMap& validCommands) -> std::pair<App::CommandID, App::Command>;

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
