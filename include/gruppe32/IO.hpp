#pragma once

#include <iostream>
#include <unordered_map>
#include <gruppe32/App.hpp>

// Forward declaration
namespace gruppe32::App {
    enum CommandID : char;
    struct Command;
}

namespace gruppe32::IO  
{
void printMenu(const std::unordered_map<App::CommandID, App::Command>& commands);
auto readCommand(const std::unordered_map<App::CommandID, App::Command>& validCommands) -> std::pair<App::CommandID, App::Command>;

} // end namespace
