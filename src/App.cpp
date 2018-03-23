#include <gruppe32/App.hpp>

namespace gruppe32 
{

//======================================
// COMMAND FUNCTIONS
//======================================

void App::printSpillereAll(DB::Context& ctx) 
{
    IO::printline(ctx.spillerene.data->noOfElements());
    IO::printline();
    IO::printline(Encode::viewSpillerene(ctx.spillerene));
}


void App::printSpillereByName(DB::Context& ctx, const std::string name) 
{
    IO::printline();
    IO::printlineNoSpace("Spiller \"", name, "\" etterspurt");
    
    DB::Spillerene viewSpillerene;

    std::size_t count = ctx.spillerene.data->noOfElements();
    for (std::size_t i = 1; i <= count; i++)
    {
        auto current = (DB::Spiller*)ctx.spillerene.data->removeNo(i);
        if (current->name.find(name) != std::string::npos)
        {
            viewSpillerene.data->add(new DB::Spiller(current->guid, current->name, current->address));
        }
        ctx.spillerene.data->add(current);
    }

    IO::printline();
    IO::printline(Encode::viewSpillerene(viewSpillerene));
}


void App::printSpillereByNumber(DB::Context& ctx, const std::size_t number) 
{
    IO::printline("printSpillereByNumber()");
    IO::printline();
    IO::printline("Spiller nr", number, "etterspurt");

    DB::Spillerene viewSpillerene;

    auto element = (DB::Spiller*)ctx.spillerene.data->remove((int)number);
    if (!element)
    {
        IO::printline("Ingen spiller med nr:", number);
        return;
    }
    viewSpillerene.data->add(new DB::Spiller(element->guid, element->name, element->address));
    ctx.spillerene.data->add(element);

    IO::printline();
    IO::printline(Encode::viewSpillerene(viewSpillerene));
}


void App::printIdretterAll(DB::Context& ctx) 
{
    IO::printline();
    IO::printline(Encode::viewIdrettene(ctx.idrettene));
}


void App::printIdretterByName( DB::Context& ctx, const std::string name) 
{
    IO::printline();
    IO::printlineNoSpace("Idrett med navn \"", name, "\" etterspurt");

    std::size_t count = ctx.idrettene.data->noOfElements();
    if (count == 0)
    {
        IO::printline("Ingen idretter i systemet!");
        return;
    }
    for (std::size_t i = 1; i <= count; i++)
    {
        auto current = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
        if (current->name.find(name) != std::string::npos)
        {

            IO::printline();
            IO::printline(Encode::viewIdrett(*current));
        }
        ctx.idrettene.data->add(current);
    }
}


void App::createSpiller(DB::Context& ctx) 
{

    auto validCommands = IO::CommandMap{
        { Terminal::CMD_SPILLER_NAVN, Terminal::Command{ string(1, Terminal::CMD_SPILLER_NAVN), "Sett navn" } },
        { Terminal::CMD_SPILLER_ADRESSE, Terminal::Command{ string(1, Terminal::CMD_SPILLER_ADRESSE), "Sett adresse" } },
        Terminal::commandBackPair
    };
    std::string spillerNavn = "";
    std::string spillerAdresse = "";
    for (;;)
    {
        { //VALIDATE
            if (Valid::isName(spillerNavn) && Valid::isAddress(spillerAdresse))
            {
                if (validCommands.find(Terminal::CMD_COMMIT) == validCommands.end())
                {
                    validCommands.insert(validCommands.begin(), Terminal::commandCommitPair);
                }
            }
        }
        IO::printMenu(validCommands, "HOME -> Lag ny -> Spiller" + Valid::isName(spillerNavn) ? "- "+spillerNavn:"");
        IO::printline("Navn:",      spillerNavn);
        IO::printline("Adresse:",   spillerAdresse);
        IO::divider('_', 40);
        
        auto[cmdKey, cmd] = IO::readCommand(validCommands);
        switch (cmdKey)
        {
        case Terminal::CMD_SPILLER_NAVN:
            spillerNavn = IO::readName();
            break;
        case Terminal::CMD_SPILLER_ADRESSE:
            spillerAdresse = IO::readAddress();
            break;
        case Terminal::CMD_COMMIT:
        {
            auto nySpiller = new DB::Spiller(++ctx.spillerene.autoIncrementer, "", "");
            IO::printline("Legger til ", nySpiller->name, "...");
            ctx.spillerene.data->add(nySpiller);
            IO::printline(nySpiller->name, "lagt til med nr:", nySpiller->guid);
            return;
        }
        case Terminal::CMD_BACK:
            IO::printline("Avbryter...");
            IO::printline("Ingen ny spiller lagt til.");
            return;
        default:
            IO::printline("Not a valid command!");
            break;
        }
    }   
}


void App::createIdrett(DB::Context& ctx) 
{
    //Local usages 
    // 
    const auto SEIER_2_UAVGJORT_1_TAP_0           = Terminal::CMD_TABELL_IDRETT_FIL;
    const auto SEIER_3_UAVGJORT_1_TAP_0           = Terminal::CMD_TABELL_DIVISJON;
    const auto SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0 = Terminal::CMD_TABELL_DIVISJON_FIL;
    
    auto validCommands = IO::CommandMap{
        { Terminal::CMD_IDRETT_NAVN, Terminal::Command{ string(1, Terminal::CMD_IDRETT_NAVN), "Sett navn" } },
        { Terminal::CMD_TABELL, 
            Terminal::Command{ 
                string(1, Terminal::CMD_TABELL), "Sett tabelltype", "TabellType",
                {
                { SEIER_2_UAVGJORT_1_TAP_0, Terminal::Command{string(1, SEIER_2_UAVGJORT_1_TAP_0), Encode::viewTabelltype(DB::Idrett::SEIER_2_UAVGJORT_1_TAP_0) } },
                { SEIER_3_UAVGJORT_1_TAP_0, Terminal::Command{ string(1, SEIER_3_UAVGJORT_1_TAP_0), Encode::viewTabelltype(DB::Idrett::SEIER_3_UAVGJORT_1_TAP_0) } },
                { SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0, Terminal::Command{ string(1, SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0), Encode::viewTabelltype(DB::Idrett::SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0) } }
                }
            }
        },
        Terminal::commandBackPair
    };
    //auto nyIdrett = new DB::Idrett{ "", DB::Idrett::SEIER_2_UAVGJORT_1_TAP_0 };
    std::string idrettNavn = "";
    DB::Idrett::TabellType tabellType = DB::Idrett::SEIER_2_UAVGJORT_1_TAP_0;
    for (;;)
    {
        if (Valid::isName(idrettNavn))//VALIDATE
        {
            if (validCommands.find(Terminal::CMD_COMMIT) == validCommands.end())
            {
                validCommands.insert(validCommands.begin(), Terminal::commandCommitPair);
            }
        }
        IO::printMenu(validCommands, "HOME -> Lag ny -> Idrett " + (Valid::isName(idrettNavn) ? "- " + idrettNavn : ""));
        IO::printline("Navn:",       idrettNavn);
        IO::printline("Tabelltype:", Encode::viewTabelltype(tabellType));
        IO::divider('_', 40);

        auto[cmdKey, cmd] = IO::readCommand(validCommands);
        switch (cmdKey)
        {
        case Terminal::CMD_IDRETT_NAVN:
        {
            std::string _name = IO::readName();
            for ( ;ctx.idrettene.data->inList(_name.c_str()); _name = IO::readName())
            {
                IO::printline("Idretten", _name, "finnes allerede!");
            }
            idrettNavn = _name;
            break;
        }
        case Terminal::CMD_TABELL:
            for (;;)
            {
                IO::printSubMenu(cmd.subcmd, cmd.title, "HOME -> Lag ny -> Idrett " + (Valid::isName(idrettNavn) ? "- " + idrettNavn : ""));
                auto[subCmdKey, _] = IO::readCommand(cmd.subcmd);
                switch (subCmdKey)
                {
                case SEIER_2_UAVGJORT_1_TAP_0:
                    tabellType = DB::Idrett::SEIER_2_UAVGJORT_1_TAP_0;
                    break;
                case SEIER_3_UAVGJORT_1_TAP_0:
                    tabellType = DB::Idrett::SEIER_3_UAVGJORT_1_TAP_0;
                    break;
                case SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0:
                    tabellType = DB::Idrett::SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0;
                    break;
                default:
                    IO::printline("Not a valid tabelltype!");
                    break;
                }
                break;
            }
            break;
        case Terminal::CMD_COMMIT:
        {
            auto nyIdrett = new DB::Idrett(idrettNavn, tabellType);
            IO::printline("Legger til ", nyIdrett->name, "...");
            ctx.idrettene.count++;
            ctx.idrettene.data->add(nyIdrett);
            IO::printline(nyIdrett->name, "lagt til!");
            IO::printline();
            return;
        }
        case Terminal::CMD_BACK:
            IO::printline("Avbryter...");
            IO::printline("Ingen ny idrett lagt til.");
            return;
        default:
            IO::printline("Not a valid command!");
            break;
        }
    }
    IO::printline("createIdrett()");
}


void App::createDivisjon(DB::Context& ctx) 
{
    IO::printline("createDivisjon()");
}


void App::deleteSpiller(DB::Context& ctx) 
{
    IO::printline("deleteSpiller()");

    const auto CMD_VELG = Terminal::CommandID('V');
    const auto CMD_SEARCH = Terminal::CommandID('S');

    auto validCommands = IO::CommandMap{
        { CMD_VELG, Terminal::Command{ string(1, CMD_VELG), "Velg spiller..." } },
        { CMD_SEARCH, Terminal::Command{ string(1, CMD_SEARCH), "S�k spiller med navn..." } },
        Terminal::commandBackPair
    };
    std::size_t nummer = -1;
    std::string searchString = "";
    std::string feedback = "";
    for (;;)
    {
        auto spiller = (DB::Spiller*)ctx.spillerene.data->remove(nummer);
        IO::newpage();
        if (spiller)
        {
            if (validCommands.find(Terminal::CMD_COMMIT) == validCommands.end())
            {
                validCommands.insert(validCommands.begin(), Terminal::commandCommitPair);
            }
            IO::printMenu(validCommands, "HOME -> Fjern -> Spiller - " + spiller->name);
            IO::printline("Spiller som skal fjernes:");
            IO::printline("Navn:", spiller->name);
            IO::printline("Adresse:", spiller->address);
            IO::printline("Nummer:", spiller->guid);
            IO::divider('_', 40);
            ctx.spillerene.data->add(spiller);
        }
        else 
        {
            IO::printMenu(validCommands, "HOME -> Fjern -> Spiller - INGEN" );
        }
        if (!searchString.empty())
        {
            printSpillereByName(ctx, searchString);
        }
        if (!feedback.empty())
        {
            IO::printline(feedback);
        }
        auto[cmdKey, cmd] = IO::readCommand(validCommands);
        switch (cmdKey)
        {
        case CMD_SEARCH:
        {
            searchString = IO::readName();
            break;
        }
        case CMD_VELG:
        {
            searchString = "";
            if(ctx.spillerene.data->noOfElements() <= 0)
            {
                IO::printline("Ingen spillere � velge, spillerlisten er tom!");
                break;
            }
            for (;;)
            {
                std::size_t _nr = IO::readNumber();
                if (ctx.spillerene.data->inList(_nr))
                {
                    nummer = _nr;
                    break;
                }
                else
                {
                    IO::printline("Ingen spiller med nr:", _nr);
                }
            }
            break;
        }
        case Terminal::CMD_COMMIT:
        {
            if (auto spiller = (DB::Spiller*)ctx.spillerene.data->remove(nummer); spiller)
            {
                IO::printlineNoSpace("Spiller \"", spiller->name, "\" fjernet");
                delete spiller;
                IO::waitForAnyKey();
            }
            else 
            {
                IO::printline("Something bad happened!!! Spiller should not be null at this point!!!!");
                assert(false);
            }

            return;
        }
        case Terminal::CMD_BACK:
            IO::printline("Avbryter...");
            IO::printline("Ingen spiller fjernet.");
            return;
        default:
            IO::printline("Not a valid command!");
            break;
        }
    }
}


void App::deleteIdrett(DB::Context& ctx) 
{
    const auto CMD_VELG = Terminal::CommandID('V');
    const auto CMD_SEARCH = Terminal::CommandID('S');
    const auto CMD_BACK = Terminal::CommandID('B');
    const auto CMD_REMOVE = Terminal::CommandID('F');

    const auto CMD_YES = Terminal::CommandID('Y');
    const auto CMD_NO = Terminal::CommandID('N');

    const auto removeCommand = IO::CommandPair{ 
        CMD_REMOVE, 
        Terminal::Command{ 
            "[F]jern", "Fjern den valgte idretten", "Bekreft", 
            {
                { CMD_NO,  Terminal::Command{"[N]ei", "Ikke fjern"}},
                { CMD_YES, Terminal::Command{"[Y]es", "Fjern"}}
            }
        }
    };

    auto commandMap = IO::CommandMap{
        { CMD_VELG,   Terminal::Command{"[V]elg", "Velg idretten som skal fjernes"} },
        { CMD_SEARCH, Terminal::Command{"[S]�k", "S�k p� idretter etter navn"} },
        { CMD_BACK, Terminal::Command{ "[B]ack", "G� tilbake" } }
    };
    std::string valgtIdrettStr = "";
    std::string searchString = "";
    std::string feedback = "";

    for (;;)
    {
        IO::newpage();
        
        
        if (auto idrett = (DB::Idrett*)ctx.idrettene.data->remove(valgtIdrettStr.c_str()); idrett)
        {
            if (commandMap.find(Terminal::CMD_COMMIT) == commandMap.end())
            {
                commandMap.insert(commandMap.begin(), removeCommand);
            }
            IO::printSubMenu(commandMap, "Idrett - " + idrett->name, "HOME -> Fjern");
            IO::printline("Idrett som skal fjernes:");
            App::printIdrett(*idrett);
            IO::divider('_', 40);

            ctx.idrettene.data->add(idrett);
        } 
        else
        {
            IO::printSubMenu(commandMap, "Idrett - INGEN", "HOME -> Fjern");
        }
        if (!searchString.empty())
        {
            IO::printlineNoSpace("Idrett med navn \"", searchString, "\" etterspurt");
            std::size_t count = ctx.idrettene.data->noOfElements();
            if (count == 0)
            {
                IO::printline("Ingen idretter i systemet!");
                break;
            }
            for (std::size_t i = 1; i <= count; i++) // Loop listen over idretter
            {
                auto current = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
                if (current->name.find(searchString) != std::string::npos)
                {
                    IO::printline();
                    IO::printline("Navn:", current->name);
                    IO::printline("Tabelltype:", Encode::viewTabelltype(current->tabell));
                    IO::printline("Divisjoner:", current->divisjonene.size());
                }
                ctx.idrettene.data->add(current);
            }
        }
        if (!feedback.empty())
        {
            IO::printline(feedback);
            feedback = "";
        }
        auto[cmdKey, cmd] = IO::readCommand(commandMap);
        switch (cmdKey)
        {
        case CMD_VELG:
        {
            searchString = "";
            if (ctx.idrettene.data->noOfElements() <= 0)
            {
                feedback = "Ingen idretter � velge, idrettlisten er tom!";
                break;
            }
            std::string idrett = IO::readName();
            if (ctx.idrettene.data->inList(idrett.c_str()))
            {
                valgtIdrettStr = idrett;
            }
            else
            {
                feedback = "Ingen idrett \"" + idrett + "\" finnes i systemet...";
            }
            break;
        }
        case CMD_SEARCH:
            searchString = IO::readName();
            break;
        case CMD_REMOVE:
        {
            if (auto valgtIdrett = (DB::Idrett*)ctx.idrettene.data->remove(valgtIdrettStr.c_str()); valgtIdrett)
            {
                IO::printMenu(cmd.subcmd, "Er du sikker p� at du vil fjerne " + valgtIdrett->name);
                auto[subCmdKey, _] = IO::readCommand(cmd.subcmd);
                switch (subCmdKey)
                {
                case CMD_NO:
                    ctx.idrettene.data->add(valgtIdrett); //putt idretten tilbake, den skal ikke fj�rnes alikevel!
                    break;
                case CMD_YES:
                    IO::printline("Fjerner", valgtIdrett->name);
                    delete valgtIdrett;
                    IO::waitForAnyKey();
                    break;
                default:
                    IO::printline("It's a simple YES/NO answer!!! please answer Y/N!");
                    break;
                }
            }
            break;
        }
        case CMD_BACK:
            IO::printline("Avbryter...");
            IO::printline("Ingen idrett fjernet.");
            return;
        default:
            IO::printline("Not a valid command!");
            break;
        }
    }
}


void App::deleteDivisjon(DB::Context& ctx) 
{
    IO::printline("deleteDivisjon()");
    using std::size_t;
    using std::string;
    using std::pair;

    const auto CMD_VELG          = Terminal::CommandID('V');
    const auto CMD_VELG_IDRETT   = Terminal::CommandID('I');
    const auto CMD_VELG_DIVISJON = Terminal::CommandID('D');

    const auto CMD_BACK   = Terminal::CommandID('B');

    const auto CMD_REMOVE = Terminal::CommandID('F');

    const auto CMD_YES = Terminal::CommandID('Y');
    const auto CMD_NO  = Terminal::CommandID('N');

    const auto removeCommand = IO::CommandPair{
        CMD_REMOVE, Terminal::Command{
        "[F]jern", "Fjern den valgte divisjonen", "Bekreft",
            {
                { CMD_NO,  Terminal::Command{ "[N]ei", "Ikke fjern" } },
                { CMD_YES, Terminal::Command{ "[Y]es", "Fjern" } }
            }
        }
    };

    auto menu = IO::CommandMap{
        { CMD_BACK,           Terminal::Command{ "[B]ack", "G� tilbake" } },
        { CMD_VELG_IDRETT,    Terminal::Command{ "[I]drett",   "Input name of an Idrett" } },
        { CMD_VELG_DIVISJON,  Terminal::Command{ "[D]ivisjon", "Input name of a Divisjon" } },
    };

    string searchNavnIdrett = "";
    string searchNavnDivisjon = "";
    string selectedDivisjon = "INGEN";
    for (;;)
    {
        //Logic
        auto[divisjonene, result] = Search::findAndPrintIdrettDivisjon(ctx, searchNavnIdrett, searchNavnDivisjon);
        if (divisjonene.size() == 1)
        {
            if (menu.find(CMD_REMOVE) == menu.end())
            {
                menu.insert(menu.begin(), removeCommand);
            }
            selectedDivisjon = divisjonene[0].first.navn;
        }
        else
        {
            if (menu.find(CMD_REMOVE) != menu.end())
            {
                menu.erase(CMD_REMOVE);
            }
            selectedDivisjon = "INGEN";
        }
        

        IO::newpage();
        // Display menu
        IO::printSubMenu(menu, "Divisjon - " + selectedDivisjon, "HOME -> Fjern");
        IO::printline("Utvalget med filteret: Idrett [",searchNavnIdrett,"], Divisjon [", searchNavnDivisjon, "]");
        if(!result.empty())
        {
            IO::printline(result);
        }
        IO::divider('-', 40);
        IO::printline("Divisjon som skal fjernes:");
        if (divisjonene.size() > 1)
        {
            IO::printline("Utvalget er tvetydig, venligst pressiser!");
        }
        else if (divisjonene.size() == 1)
        {
            IO::printlineNoSpace("\"", selectedDivisjon, "\" i idretten \"", divisjonene[0].second, "\"");
        }
        else
        {
            IO::printline("Ingen divisjoner som resultat av filteret");
        }
        IO::divider('-', 40);
        

        auto[cmdKey, cmd] = IO::readCommand(menu);
        switch (cmdKey)
        {
        case CMD_VELG_DIVISJON:
        {
            searchNavnDivisjon = IO::readName("Divisjon");
            break;
        }
        case CMD_VELG_IDRETT:
        {
            searchNavnIdrett = IO::readName("Idrett");
            searchNavnDivisjon = "";
            break;
        }
        case CMD_REMOVE:
        {
            std::string valgtDivisjon = divisjonene[0].first.navn;
            if (auto valgtIdrett = (DB::Idrett*)ctx.idrettene.data->remove(divisjonene[0].second.c_str()); valgtIdrett)
            {

               /* valgtIdrett->divisjonene.erase(
                    std::remove_if(
                        valgtIdrett->divisjonene.begin(),
                        valgtIdrett->divisjonene.end(),
                        [valgtDivisjon](const DB::Divisjon& div) {return div.navn.compare(valgtDivisjon) == 0;}
                    )
                );*/


                IO::printMenu(cmd.subcmd, "Er du sikker p� at du vil fjerne " + valgtDivisjon);
                auto[subCmdKey, _] = IO::readCommand(cmd.subcmd);
                switch (subCmdKey)
                {
                case CMD_NO:
                    IO::printline("Avbryter...");
                    IO::printline("Ingen divisjon fjernes");
                    IO::waitForAnyKey();
                    ctx.idrettene.data->add(valgtIdrett); //putt idretten tilbake!
                    return;
                case CMD_YES:
                    IO::printline("Fjerner", valgtDivisjon, "...");

                    //TODO make sure this logic is correct
                    valgtIdrett->divisjonene.erase(
                        std::remove_if(
                            valgtIdrett->divisjonene.begin(),
                            valgtIdrett->divisjonene.end(),
                            [valgtDivisjon](DB::Divisjon div) {return div.navn == valgtDivisjon;}
                        ), valgtIdrett->divisjonene.end()
                    );

                    IO::waitForAnyKey();
                    ctx.idrettene.data->add(valgtIdrett); //putt idretten tilbake!
                    return;
                default:
                    IO::printline("It's a simple YES/NO answer!!! please answer Y/N!");
                    break;
                }
                ctx.idrettene.data->add(valgtIdrett); //putt idretten tilbake!
            }
            else 
            {
                assert(false); //OH Fuk !! 
            }
            break;
        }

        case CMD_BACK:
            return;
        default:
            IO::printline("Not a valid command!");
            break;
        }

    }
}


void App::terminliste(DB::Context& ctx) 
{
    using std::size_t;
    using std::string;
    using std::pair;

    const auto validCommands = IO::CommandMap {
        { Terminal::CMD_NAME_IDRETT,  Terminal::Command{   "[I]drett",  "Input name of an Idrett" }},    
        { Terminal::CMD_NAME_DIVISJON,  Terminal::Command{ "[D]ivisjon", "Input name of a Divisjon" }},
        Terminal::keyCommandFile,
        Terminal::keyCommandBack
    };

    string navnIdrett   = "";
    string navnDivisjon = "";

    for (;;) 
    {   
        // Search for divisjoner
        auto[divisjonene, statusmsg] = Search::divisjonene(ctx, navnIdrett, navnDivisjon);
        
        // Display menu
        IO::newpage();
        IO::printline();
        IO::printline(Encode::viewIdretteneCompact(ctx.idrettene, true));
        IO::printMenu(validCommands, "HOME -> Terminliste");
        IO::printline("-- Input");
        IO::printline("Idrett:",    navnIdrett);
        IO::printline("Divisjon:",  navnDivisjon);
        IO::divider('_', 80);

        // Display terminlister
        IO::printline(statusmsg);        
        IO::printline();
        for (const auto& divisjon : divisjonene) {
            auto terminliste = DB::Terminliste { divisjon.navn, divisjon.terminliste };
            IO::printline(Encode::viewTerminliste(terminliste));
        }

        // User Input
        auto [cmdkey, _] = IO::readCommand(validCommands);
        switch(cmdkey) 
        {
            case Terminal::CMD_NAME_IDRETT: 
                navnIdrett = IO::readName();
                break;

            case Terminal::CMD_NAME_DIVISJON: 
                navnDivisjon = IO::readName();
                break;

            case Terminal::CMD_BACK:   
                return;

            case Terminal::CMD_FILE: {
                string filepath = IO::readFilepath();
                std::ofstream outfile("./data/write/"+filepath+".yml");
                if (outfile) 
                {
                    for (const auto& divisjon: divisjonene) { 
                        auto terminliste = DB::Terminliste {  divisjon.navn,  divisjon.terminliste };
                        outfile << Encode::viewTerminliste(terminliste);
                    }
                    outfile.close();

                    IO::printlineNoSpace("\nTerminlistene written to file: ", filepath, ".yml");
                    IO::waitForAnyKey();
                }
            } break;

            default:
                break;
        }
    }
}

void App::resultatene(DB::Context& ctx)
{
    const auto validCommands = IO::CommandMap {
        { Terminal::CMD_NAME_IDRETT,   Terminal::Command{ "[I]drett",  "Input name of an Idrett" }},    
        { Terminal::CMD_NAME_DIVISJON, Terminal::Command{ "[D]ivisjon", "Input name of a Divisjon" }},
        { Terminal::CMD_DATE_YEAR,   Terminal::Command{   "[Y]ear", "Valid year 1970-2099" }},
        { Terminal::CMD_DATE_MONTH,  Terminal::Command{   "[M]onth", "Valid month 01-12" }},
        { Terminal::CMD_DATE_DAY,    Terminal::Command{   "D[A]g", "Valid day 01-31" }},
        Terminal::keyCommandFile,
        Terminal::keyCommandBack
    };

    string navnIdrett   = "";
    string navnDivisjon = "";
    size_t year  = 0;
    size_t month = 0;
    size_t day   = 0;

    for (;;) 
    {
        // Display menu
        IO::newpage();
        IO::printline();
        IO::printline(Encode::viewIdretteneCompact(ctx.idrettene, true));
        IO::printMenu(validCommands, "HOME -> Resultatene for idrett, divisjon og dato");
        IO::printline("-- Input --");
        IO::printline("Idrett  : ",  navnIdrett);
        IO::printline("Divisjon: ",  navnDivisjon);
        IO::printline("Year    : ",  year);
        IO::printline("Month   : ",  month);
        IO::printline("Day     : ",  day);
        IO::divider('_', 80);

        // Search for divisjoner and resultater
        auto[divisjonene, statusDivisjonene] = Search::divisjonene(ctx, navnIdrett, navnDivisjon);
        IO::printline(statusDivisjonene);  
        
        // Search each divisjon for resultatene
        for (const auto& divisjon: divisjonene)
        {         
            auto[resultatene, statusResultatene] = Search::resultatene(ctx, divisjon, year, month, day); 
            IO::printline(Encode::viewResultatene(resultatene));
        }

        // User Input
        auto [cmdkey, _] = IO::readCommand(validCommands);
        switch(cmdkey) 
        {
            case Terminal::CMD_NAME_IDRETT: 
                navnIdrett = IO::readName();
                break;

            case Terminal::CMD_NAME_DIVISJON: 
                navnDivisjon = IO::readName();
                break;

            case Terminal::CMD_DATE_YEAR:
                year = IO::readYear();
                break;

            case Terminal::CMD_DATE_MONTH:
                month = IO::readMonth();
                break;

            case Terminal::CMD_DATE_DAY:
                day = IO::readDay();
                break;


            case Terminal::CMD_FILE: {
                string filepath = IO::readFilepath();
                std::ofstream outfile("./data/write/"+filepath+".yml");

                if(outfile) 
                {
                    for (const auto& divisjon: divisjonene) { 
                        auto[resultatene, statusResultatene] = Search::resultatene(ctx, divisjon, year, month, day); 
                        outfile << Encode::viewResultatene(resultatene);

                    }
                    outfile.close();

                    IO::printlineNoSpace("\nResultatene written to file: ", filepath, ".yml");
                    IO::waitForAnyKey();
                }
            } break;


            case Terminal::CMD_BACK:  
                return;

            default:
                break;            
        }
    }
}



void App::tabell(DB::Context& ctx)
{
    IO::printline("tabellDivisjon()");
}


void App::readResultatliste(DB::Context& ctx) 
{
    IO::printline("readResultatliste()");
}

void App::printLagSpillerdata(DB::Context& ctx) 
{
    IO::printline("printLagSpillerdata()");

    using std::size_t;
    using std::string;
    using std::pair;

    const auto CMD_VELG_IDRETT =    Terminal::CommandID('I');
    const auto CMD_VELG_DIVISJON =  Terminal::CommandID('D');
    const auto CMD_VELG_LAG =       Terminal::CommandID('L');
    const auto CMD_BACK =   Terminal::CommandID('B');
    const auto CMD_VIS = Terminal::CommandID('V');

    const auto displayCommand = IO::CommandPair{
        CMD_VIS, Terminal::Command{ "[V]is", "Vis alle spillere i det valgte laget" }
    };

    auto menu = IO::CommandMap{
        { CMD_BACK,           Terminal::Command{ "[B]ack", "G� tilbake" } },
        { CMD_VELG_IDRETT,    Terminal::Command{ "[I]drett",   "Filtrer Idrett" } },
        { CMD_VELG_DIVISJON,  Terminal::Command{ "[D]ivisjon", "Filtrer Divisjon" } },
        { CMD_VELG_LAG,       Terminal::Command{ "[L]ag",      "Filtrer Lag" } }
    };

    string searchNavnIdrett   = "";
    string searchNavnDivisjon = "";
    string searchNavnLag      = "";
    string selectedLag = "INGEN";

    for (;;)
    {
        IO::newpage();
        const auto[resultatene, resultStr, status] = Search::filterLag(ctx, searchNavnIdrett, searchNavnDivisjon, searchNavnLag);
       
        if (resultatene.size() == 1)
        {
            selectedLag = resultatene[0].first.navn;
            if (menu.find(CMD_VIS) == menu.end())
            {
                menu.insert(menu.begin(), displayCommand);
            }
        }
        else
        {
            selectedLag = "INGEN";
            if (menu.find(CMD_VIS) != menu.end())
            {
                menu.erase(CMD_VIS);
            }
        }

        IO::printSubMenu(menu, "Print Spillere p� Lag - " + selectedLag);
        IO::printline("------------------------------------ FILTRE ------------------------------------");
        IO::printline("Idrett:      ", "[", searchNavnIdrett,   "]");
        IO::printline("Divisjon:    ", "[", searchNavnDivisjon, "]");
        IO::printline("Lag:         ", "[", searchNavnLag,      "]");
        IO::divider('-', 80);
        IO::printline(resultStr);
        IO::divider('-', 80);
        IO::printline("Laget som er valgt:");
        IO::printline(status);
        IO::divider('-', 80);

        const auto[cmdID, _] = IO::readCommand(menu);

        switch (cmdID)
        {
        case CMD_VELG_IDRETT:
            searchNavnIdrett = IO::toUpper(IO::readName("Idrett"));
            break;

        case CMD_VELG_DIVISJON:
            searchNavnDivisjon = IO::toUpper(IO::readName("Divisjon"));
            break;

        case CMD_VELG_LAG:
            searchNavnLag = IO::toUpper(IO::readName("Lag"));
            break;

        case CMD_BACK:
            return;

        case CMD_VIS:
        {
            DB::Spillerene lagSpillerene(0);
            for (const auto& spillerID : resultatene[0].first.spillerene)
            {
                const auto spiller = (DB::Spiller*)ctx.spillerene.data->remove(spillerID);
                
                lagSpillerene.data->add(new DB::Spiller(*spiller));
                ctx.spillerene.data->add(spiller);
            }
            IO::printline("Spillerene p� laget: ", resultatene[0].first.navn);
            IO::printline(Encode::viewSpillerene(lagSpillerene));
            IO::waitForAnyKey();
            break;
        }
        default:
            break;
        }
    }
}
void App::insertLagSpiller(DB::Context& ctx)
{
    IO::printline("insertLagSpiller()");
}
void App::removeLagSpiller(DB::Context& ctx) 
{
    IO::printline("removeLagSpiller()");
}


void App::topp10(DB::Context& ctx)
{
    IO::printline("topp10Divisjon()");
}


//======================================
// HELPER FUNCTIONS
//======================================

// @DEPRECATED possible jsolsvik 20.03.2018
void App::printDivisjonene(const DB::Idrett& idrett)
{
    IO::printline("Divisjonene:");
    for (const auto& divisjon : idrett.divisjonene)
    {
        IO::printline("- ", divisjon.navn);
    }
}


void App::printIdrettene(DB::Idrettene& idrettene)
{

    IO::divider('_', 80);    
    IO::printline();
    IO::printline("Idrettene:");
    for (size_t i = 1; i <= idrettene.data->noOfElements(); ++i) 
    {
        auto idrett = (DB::Idrett* ) idrettene.data->removeNo(i);
        IO::printline("- ", idrett->name);
        idrettene.data->add(idrett);
    }
    IO::divider('_', 80);
}


void App::printSpiller(const DB::Spiller& spiller)
{
    IO::printline("  ", spiller.name);
    IO::printline("   - Nummer:", spiller.guid);
    IO::printline("   - Adresse:", spiller.address);
};

void App::printIdrett(const DB::Idrett& idrett)
{
    IO::printline("  ", idrett.name);
    IO::printline("   - Tabelltype:", Encode::viewTabelltype(idrett.tabell));
    IO::printline("   - Antall divisjoner:", idrett.divisjonene.size());
}

//======================================
// BACKGROUND FUNCTIONS
//======================================
void App::readIdrettene(DB::Idrettene& idrettene, const std::string filepath)
{
    std::ifstream infile(filepath);
    if (!infile) {
        IO::printline("No files at filepath", filepath);
        return;
    }

    std::stringstream ss;
    ss << infile.rdbuf();
    std::string instring = ss.str();

    auto err = Decode::dataIdrettene(idrettene, instring.c_str());
    if (err) {
        IO::printline("Error when encoding idrettene! ", filepath);
        return;
    } 
}

void App::readSpillerene(DB::Spillerene& spillerene, const std::string filepath)
{
    std::ifstream instream(filepath);
    if (!instream) {
        IO::printline("No files at filepath", filepath);
        return;
    }

    std::stringstream ss;
    ss << instream.rdbuf();
    auto err = Decode::dataSpillerene(spillerene, ss.str());
    if (err) {
        IO::printline("Error when encoding spillerene! ", filepath);
        return;
    } 
}

void App::writeIdrettene(DB::Idrettene& ctx, const std::string filepath)
{
    std::ofstream outstream(filepath);
    if (!outstream) {
        IO::printline("No files at filepath", filepath);
        return;
    }

    auto outstring = Encode::dataIdrettene(ctx);
    outstream << outstring;
}

void App::writeSpillerene(DB::Spillerene& ctx, const std::string filepath)
{
    std::ofstream outstream(filepath);
    if (!outstream) {
        IO::printline("No files at filepath", filepath);
        return;
    }

    auto outstring = Encode::dataSpillerene(ctx);
    outstream << outstring; 
}



//======================================
// SEARCH FUNCTIONS
//======================================
using std::vector;
using std::string;
using std::size_t;
using std::pair;

auto Search::filterLag(
    DB::Context& ctx,
    const string& navnIdrett,
    const string& navnDivisjon,
    const string& navnLag
) ->filterResult<DB::Lag>
{   
    vector<pair<DB::Lag, vector<string>>> result{};
    string resultTreeString = "";
    string statusMsg = "";

    const size_t count = ctx.idrettene.data->noOfElements();
    for (size_t i = 1; i <= count; i++)
    {
        const auto idrett = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
        resultTreeString += "|-" + idrett->name + "\n";
        for (const auto& divisjon : idrett->divisjonene)
        {
            resultTreeString += "  |-" + divisjon.navn + "\n";
            for (const auto& lag : divisjon.lagene)
            {
                if ((navnIdrett.empty() || (IO::toUpper(idrett->name).find(navnIdrett) != string::npos)) &&
                    (navnDivisjon.empty() || (IO::toUpper(divisjon.navn).find(navnDivisjon) != string::npos)) &&
                    (navnLag.empty() || (IO::toUpper(lag.navn).find(navnLag) != string::npos)))
                {
                    resultTreeString += "    |=>[ " + IO::toUpper(lag.navn) + " ]\n";
                    result.push_back(std::pair<DB::Lag,vector<string>>{ lag, {idrett->name, divisjon.navn, lag.navn} });
                }
                else 
                {
                    resultTreeString += "    |-" + lag.navn + "\n";
                }
            }
        }
        ctx.idrettene.data->add(idrett);
    }
    if (result.size() > 1)
    {
        statusMsg = "Filteret er tvetydig, venligst pressiser...";
    }
    else if (result.size() == 1)
    {
        statusMsg = "Idretten: " + result[0].second[0] + ", Divisjonen: " + result[0].second[1] + ", Laget: " + result[0].second[2];
    }
    else
    {
        statusMsg = "Ingen lag i filteret, venligst ompresiser";
    }
    
    return { result, resultTreeString, statusMsg };
}

auto Search::findAndPrintIdrettDivisjon(DB::Context & ctx, const string & navnIdrett, const string & navnDivisjon) -> Search::returnDivisjoneneMedIdrettNavn
{
    vector<pair<DB::Divisjon, string>> result{};
    string printout = "";
        const std::size_t count = ctx.idrettene.data->noOfElements();
        for (std::size_t i = 1; i <= count; i++)
        {
            const auto idrett = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
            if (navnIdrett.empty())
            {
                printout += "  " + idrett->name + "\n";
                for (const auto& div : idrett->divisjonene)
                {
                    auto divPair = pair<DB::Divisjon, string>{ div, idrett->name };
                    if (navnDivisjon.empty())
                    {
                        printout += "  - " + div.navn + "\n";
                        result.push_back(divPair);
                    }
                    else if (div.navn.find(navnDivisjon) != std::string::npos)
                    {
                        printout += "  - " + div.navn + "\n";
                        result.push_back(divPair);
                    }
                }
            }
            else if (idrett->name.find(navnIdrett) != std::string::npos)
            {
                printout += "  " + idrett->name + "\n";
                for (const auto& div : idrett->divisjonene)
                {
                    auto divPair = pair<DB::Divisjon, string>{ div, idrett->name };
                    if (navnDivisjon.empty())
                    {
                        printout += "  - " + div.navn + "\n";
                        result.push_back(divPair);
                    }
                    else if (div.navn.find(navnDivisjon) != std::string::npos)
                    {
                        printout += "  - " + div.navn + "\n";
                        result.push_back(divPair);
                    }
                }
            }
            ctx.idrettene.data->add(idrett);
        }
        if (result.size() == 0)
        {
            printout = "Ingen divisjoner funnet!";
        }
    return Search::returnDivisjoneneMedIdrettNavn{ result, printout };
}

auto Search::divisjonene(DB::Context& ctx, const string& navnIdrett, const string& navnDivisjon)
    -> Search::returnDivisjonene
{
    vector<DB::Divisjon> result{};
    string statusmsg = "";

    DB::Idrett* idrett = (DB::Idrett* ) ctx.idrettene.data->remove(navnIdrett.c_str());

    // Error 1
    if (!idrett) {
        statusmsg = "Idrett " + navnIdrett + " not found";
        return Search::returnDivisjonene{result, statusmsg};
    }
    // Error 2
    if (idrett->divisjonene.size() == 0) {
        statusmsg = "Idrett " + navnIdrett + " has no divisjoner";
        
        ctx.idrettene.data->add(idrett);   // because why no
        return Search::returnDivisjonene{result, statusmsg};
    }

    // Success 1 
    if (navnDivisjon.empty()) 
    {
        for (const auto& divisjon : idrett->divisjonene)
        {
            result.push_back(divisjon);
        }

        ctx.idrettene.data->add(idrett);   // because why no    
        statusmsg = "Found " + std::to_string(result.size()) + " divisjoner";
        return Search::returnDivisjonene{result, statusmsg};
    }

    for (const auto& divisjon : idrett->divisjonene)
    {
        // Success 2
        if (divisjon.navn.find(navnDivisjon) != std::string::npos)
        {
            result.push_back(divisjon);
        }
    }
    // Error 4
    if (result.empty()) { 
        statusmsg = "Idrett " + navnIdrett + " has no divisjon matching " + navnDivisjon;

        ctx.idrettene.data->add(idrett);   // because why no
        return Search::returnDivisjonene{result, statusmsg};
    }

    statusmsg = "Found " + std::to_string(result.size()) + " divisjoner";
    ctx.idrettene.data->add(idrett);   // because why no    
    return Search::returnDivisjonene{result, statusmsg};
}

auto Search::resultatene(
    DB::Context& ctx, 
    const DB::Divisjon& divisjon, 
    const size_t year, 
    const size_t month, 
    const size_t day) 
    -> Search::returnResultatene 
{
    string statusmsg = "";
    std::stringstream ss;

    // Encode date
    ss << year << "-";

    if (month < 10) ss << "0" + std::to_string(month) << "-";
    else ss << month << "-";

    if (day < 10) ss << "0"+std::to_string(day);
    else ss << day;

    string encodedDato = ss.str();

    vector<DB::ViewResultat> resultatene;

    for (const auto [hjemmelag, bortelagene] : divisjon.terminliste) // map 
    {
        for (const auto [bortelag, resultat] : bortelagene)    // map
        {
            if (resultat.dato == encodedDato) 
            {
                resultatene.push_back(DB::ViewResultat {
                    divisjon.navn,
                    hjemmelag,
                    bortelag,
                    encodedDato,
                    resultat.hjemmeScorerene.size(),
                    resultat.borteScorerene.size()
                });
            }
        }
    }
    // Error 4
    if (resultatene.empty()) { 
        statusmsg = "Dato " + encodedDato + " has no resultats.";
        return Search::returnResultatene {resultatene, statusmsg};
    }

    statusmsg = "Found " + std::to_string(resultatene.size()) + " resultats on " + encodedDato;
    return Search::returnResultatene {resultatene, statusmsg};
} // ::Search
} // ::gruppe32
