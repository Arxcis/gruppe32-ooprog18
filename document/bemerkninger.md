##Bemerkninger

#### C++17 features tatt i bruk

1. Multiple return values/ struct unpacking
    ```cpp
    const auto [key, command] = IO::readCommand(mainCommands);
    ```

2. Nested namespaces
    ```cpp
    namespace gruppe32::App 
    ```

3. Inlined static variables
    ```cpp
    inline const static std::unordered_map<CommandID, Command> mainCommands;
    ```

4. If scoped variable initializer
    ```cpp
    if (auto cmdID = menyFJERN(); cmdID == CMD_BACK) 
    {
        break;
    }
    else if (cmdID == CMD_QUIT) 
    {
        return;
    }
    ```