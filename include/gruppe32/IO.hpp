#pragma once

#include <iostream>
#include <map>
#include <gruppe32/App.hpp>

// Forward declaration
namespace gruppe32::App {
    enum CommandID : char;
    struct Command;
}

namespace gruppe32::IO  
{
void printMenu(const std::map<App::CommandID, App::Command>& commands);
auto readCommand(const std::map<App::CommandID, App::Command>& validCommands) -> std::pair<App::CommandID, App::Command>;

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
