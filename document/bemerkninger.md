##Bemerkninger

#### C++17 features tatt i bruk

1. Multiple return values
```cpp
const auto [key, command] = IO::readCommand(mainCommands);
```

2. Nested namespaces
```cpp
namespace gruppe32::App 
```

3. Inlined static variables
```cpp
const static std::unordered_map<CommandID, Command> mainCommands;
```