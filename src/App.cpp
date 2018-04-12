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


    IO::waitForEnterPress();
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

    IO::waitForEnterPress();

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

    IO::waitForEnterPress();

}


void App::printIdretterAll(DB::Context& ctx) 
{
    IO::printline();
    IO::printline(Encode::viewIdrettene(ctx.idrettene));

    IO::waitForEnterPress();
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

    IO::waitForEnterPress();
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
            auto nySpiller = new DB::Spiller(++ctx.spillerene.autoIncrementer, spillerNavn, spillerAdresse);
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
    /*
    
    spør etter filnavn [RETURN: fil finnes ikke]

    les fra fil [RETURN: fil finnes ikke]

    parse filstrengen -> nyDivisjon

    smett inn nyDivisjon i context
    
    */
    IO::printline("Velg idrett...");
    auto idrettName = IO::readName("Idrett");

    IO::printline("Choose file to read divisjon from (e.g. \"seed-divisjon\")");
    std::string filepath = IO::readFilepath();
    IO::printline();
    IO::printline("reading", "./data/read/" + filepath + ".yml");
    // @TODO Validate filepath - remove // 
    std::ifstream infile("./data/read/" + filepath + ".yml");

    if (!infile) {
        IO::printline("ERROR - File not found  (!infile)");
        IO::waitForEnterPress();
        return;
    }

    std::stringstream ss;
    ss << infile.rdbuf();
    std::string instring = ss.str();

    DB::Divisjon divisjonen;

    //IO::printline(instring);
    auto err = Decode::inputDivisjon(divisjonen, ctx.spillerene, instring.c_str());
    if (err) {
        IO::printline("Error when decoding divisjon! ", filepath);
        IO::waitForEnterPress();
        return;
    }



    const size_t count = ctx.idrettene.data->noOfElements();
    for (size_t i = 1; i <= count; i++)
    {
        auto idrett = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
        if (idrett->name == idrettName)
        {
            IO::printline("FOUND IDRETT", idrett->name);
            idrett->divisjonene.push_back(divisjonen);
        }
        ctx.idrettene.data->add(idrett);
    }

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
                IO::waitForEnterPress();
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
                Terminal::commandBackPair,
        
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
                    IO::waitForEnterPress();
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
                    IO::waitForEnterPress();
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

                    IO::waitForEnterPress();
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
    using namespace Terminal;

    using std::size_t;
    using std::string;
    using std::pair;

    // 1. Declare valid commands
    const auto validCommands = std::vector<IO::CMD> {
        IO::cmdNameIdrett,
        IO::cmdNameDivisjon,
        IO::cmdPrint,
        IO::cmdFile,
        IO::cmdOptions,
        IO::cmdBack
    };


    // 2. Menu state
    string navnIdrett   = "";
    string navnDivisjon = "";
    string options      = "";
    std::vector<DB::Terminliste> terminlistene;

    for (;;) 
    {   
        // 3. Fetch divisjoner and terminlister
        terminlistene.clear(); 
        auto[divisjonene, statusmsg] = Search::divisjonene(ctx, navnIdrett, navnDivisjon);
        for (const auto& divisjon : divisjonene) {
            terminlistene.push_back(DB::Terminliste { divisjon.navn, divisjon.terminliste });
        }


        // 4. Display menu
        IO::newpage();
        IO::printline();
        IO::printMenu(validCommands, "HOME -> Terminliste");
        IO::printline("------------------------------------ Input -------------------------------------");
        IO::printline("Idrett:",    navnIdrett);
        IO::printline("Divisjon:",  navnDivisjon);
        IO::divider('-', 80);
        IO::printline(Search::makeStatus(terminlistene,statusmsg));
        IO::printline(options); options = "";

        // 5. User Input
        auto cmdid = IO::readCommand(validCommands);
        switch(cmdid) 
        {
            case IO::cmdNameIdrett.id:
                navnIdrett = IO::readName();
                navnDivisjon = "";

                break;

            case IO::cmdNameDivisjon.id:
                navnDivisjon = IO::readName();
                break;

            case IO::cmdOptions.id:
                options = Encode::viewIdretteneCompact(ctx.idrettene, true);
                break;

            case IO::cmdPrint.id: 
            {
                std::string result = "";
                for (const auto& terminliste: terminlistene) {
                    result += Encode::viewTerminliste(terminliste);
                }
                IO::printline(result);
                IO::waitForEnterPress();
            } break;
            
            case IO::cmdFile.id: 
            {
                string filepath = IO::readFilepath();
                std::ofstream outfile("./data/write/"+filepath+".yml");
                if(!outfile) 
                {   
                    IO::printline("Error when writing to file (!outfile)");
                    IO::waitForEnterPress();
                    break;
                }
                for (const auto& divisjon: divisjonene) { 
                    auto terminliste = DB::Terminliste {  divisjon.navn,  divisjon.terminliste };
                    outfile << Encode::viewTerminliste(terminliste);
                }
                outfile.close();

                IO::printlineNoSpace("\nTerminlistene written to file: ", filepath, ".yml");
                IO::waitForEnterPress();
            } break;

            case IO::cmdBack.id:
                return;

            default:
                break;
        }
    }
}

void App::resultatene(DB::Context& ctx)
{
    using namespace Terminal;
    
    // 1. Declare valid commands
    const auto menu = std::vector<IO::CMD> {
        IO::cmdNameIdrett,
        IO::cmdNameDivisjon,
        IO::cmdYear,
        IO::cmdMonth,
        IO::cmdDay,
        IO::cmdPrint,
        IO::cmdFile,
        IO::cmdOptions,
        IO::cmdBack
    };

    // 2. Menu state
    string navnIdrett   = "";
    string navnDivisjon = "";
    string options      = "";
    size_t year  = 0;
    size_t month = 0;
    size_t day   = 0;

    std::vector<DB::ViewResultat> resultatene;

    for (;;) 
    {
        // 3. Search for divisjoner and resultater
        resultatene.clear();
        auto[divisjonene, statusDivisjonene] = Search::divisjonene(ctx, navnIdrett, navnDivisjon);
        for (const auto& divisjon: divisjonene)
        {         
            auto[_resultatene, statusResultatene] = Search::resultatene(ctx, divisjon, year, month, day); 
            for(const auto result: _resultatene) 
            {
                resultatene.push_back(result);  
            } 
        }


        // 4. Display menu
        IO::newpage();
        IO::printline();
        IO::printMenu(menu, "HOME -> Resultatene");
        IO::printline("------------------------------------ Input -------------------------------------");
        IO::printline("Idrett  : ",  navnIdrett);
        IO::printline("Divisjon: ",  navnDivisjon);
        IO::printline("Year    : ",  year);
        IO::printline("Month   : ",  month);
        IO::printline("Day     : ",  day);
        IO::divider('-', 80);
        IO::printline(Search::makeStatus(resultatene, statusDivisjonene));  
        IO::printline(options); options = "";


        // 5. User Input
        auto cmdid = IO::readCommand(menu);
        switch(cmdid) 
        {
            case IO::cmdNameIdrett.id: 
                navnIdrett = IO::readName();
                navnDivisjon = "";
                break;

            case IO::cmdNameDivisjon.id:
                navnDivisjon = IO::readName();
                break;

            case IO::cmdYear.id:
                year = IO::readYear();
                break;

            case IO::cmdMonth.id:
                month = IO::readMonth();
                break;

            case IO::cmdDay.id:
                day = IO::readDay();
                break;

            case IO::cmdOptions.id:
                options = Encode::viewIdretteneCompact(ctx.idrettene, true);
                break;

            case IO::cmdPrint.id: 
            {
                std::string result = "";
                for (const auto& divisjon: divisjonene) { 
                    auto[resultatene, statusResultatene] = Search::resultatene(ctx, divisjon, year, month, day); 
                    result += (Encode::viewResultatene(resultatene));
                }

                IO::printline(result);
                IO::waitForEnterPress();
            } break;

            case IO::cmdFile.id: 
            {
                string filepath = IO::readFilepath();
                std::ofstream outfile("./data/write/"+filepath+".yml");

                if(!outfile) 
                {   
                    IO::printline("Error when writing to file (!outfile)");
                    IO::waitForEnterPress();
                    break;
                }
                for (const auto& divisjon: divisjonene) { 
                    auto[resultatene, statusResultatene] = Search::resultatene(ctx, divisjon, year, month, day); 
                    outfile << Encode::viewResultatene(resultatene);
                }
                outfile.close();

                IO::printlineNoSpace("\nResultatene written to file: ", filepath, ".yml");
                IO::waitForEnterPress();

            } break;

            case IO::cmdBack.id:   
                return;

            default:
                break;            
        }
    }
}



void App::tabell(DB::Context& ctx)
{
    using namespace Terminal;

    // 1. Declare valid commands
    auto validCommands = std::vector<IO::CMD> {
        IO::cmdNameIdrett,
        IO::cmdNameDivisjon,
        IO::cmdPrint,
        IO::cmdFile,
        IO::cmdOptions,
        IO::cmdBack,
    };


    // 2. Menu state
    string navnIdrett   = "";
    string navnDivisjon = "";
    string options      = "";
    DB::Idrett::TabellType tabelltype;
    std::vector<DB::Tabell> tabellene;

    for (;;) 
    {
        // 3. Compute tabellene if we had a search hit
        auto[divisjonene, statusDivisjonene] = Search::divisjonene(ctx, navnIdrett, navnDivisjon);

        // 4. Display menu
        IO::newpage();
        IO::printline();
        IO::printMenu(validCommands, "HOME -> Tabellene");
        IO::printline("------------------------------------ Input -------------------------------------");
        IO::printline("Idrett  : ",  navnIdrett);
        IO::printline("Divisjon: ",  navnDivisjon);
        IO::divider('-', 80);
        IO::printline(Search::makeStatus(tabellene, statusDivisjonene));  
        IO::printline(options); options = "";

        auto idrett = (DB::Idrett*) ctx.idrettene.data->remove(navnIdrett.c_str());
        if (idrett) {
            auto tabelltype = idrett->tabell;
            ctx.idrettene.data->add(idrett);

            tabellene.clear();
            for (const auto& divisjon: divisjonene)
                tabellene.push_back(App::computeTabell(divisjon, tabelltype));
        }

        // 5. User Input
        auto cmdid = IO::readCommand(validCommands);
        switch(cmdid) 
        {
            case IO::cmdNameIdrett.id: 
                navnIdrett = IO::readName();
                navnDivisjon = "";
                break;

            case IO::cmdNameDivisjon.id: 
                navnDivisjon = IO::readName();
                break;

            case IO::cmdPrint.id:

                IO::printline(Encode::viewTabellene(tabellene));
                IO::waitForEnterPress();                
                break;

            case IO::cmdOptions.id:
                options = Encode::viewIdretteneCompact(ctx.idrettene, true);
                break;

            case IO::cmdFile.id: 
            {
                std::string filepath = IO::readFilepath();
                std::ofstream outfile("./data/write/"+filepath+".yml");

                if(!outfile) 
                {   
                    IO::printline("Error when writing to file (!outfile)");
                    IO::waitForEnterPress();
                    break;
                }
                auto _result = Encode::viewTabellene(tabellene);
                IO::printline(_result);
                outfile << _result;
                outfile.close();

                IO::printline();
                IO::printlineNoSpace("\nTabellene written to file: ", filepath, ".yml");
                IO::waitForEnterPress();
            } break;

            case IO::cmdBack.id:   
                return;

            default:
                break;            
        }
    }
}


void App::readResultatliste(DB::Context& ctx) 
{
    IO::dividerHeading("Reading resultatene from file...");
    IO::printline("Write a valid filename");
    std::string filepath = IO::readFilepath();
    
    // @TODO Validate filepath - remove // 
    std::ifstream infile("./data/read/" + filepath + ".yml");

    if (!infile) {
        IO::printline("ERROR - File not found  (!infile)");
        IO::waitForEnterPress();
        return;
    }

    std::stringstream ss;
    ss << infile.rdbuf();
    std::string instring = ss.str();

    std::vector<DB::InputResultat> resultatene;

    //IO::printline(instring);
    auto err = Decode::inputResultatene(resultatene, instring.c_str());
    if (err) {
        IO::printline("Error when decoding resultatene! ", filepath);
        IO::waitForEnterPress();
        return;
    } 

    // @NOTE Insert data into ctx tree structure
    for(auto& result : resultatene) 
    {
        IO::printline(
            result.idrett, 
            result.divisjon,
            result.hjemmelag,
            result.bortelag);


        const size_t count = ctx.idrettene.data->noOfElements();
        for (size_t i = 1; i <= count; i++)
        {
            auto idrett = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
            if (idrett->name == result.idrett) 
            {
                IO::printline("FOUND IDRETT", idrett->name);
                for (auto& divisjon : idrett->divisjonene)
                {
                    if (divisjon.navn == result.divisjon) 
                    {
                        IO::printline("FOUND DIVISJON", divisjon.navn);
                    
                        for (auto& [hjemmelag, bortelagene]: divisjon.terminliste) 
                        {
                            IO::printline("hjemmelag", hjemmelag);
                            if (hjemmelag == result.hjemmelag)
                            {
                                IO::printline("FOUND hjemmelag", hjemmelag);

                                for (auto& [bortelag, resultat]: bortelagene) 
                                {
                                    if (bortelag == result.bortelag) 
                                    {
                                        IO::printline("FOUND bortelag", bortelag);
                                        
                                        resultat = DB::Resultat {
                                            result.dato,
                                            true,
                                            result.overtid,
                                            result.hjemmeScorerene,
                                            result.borteScorerene
                                        };
                                    }
                                }
                            }
                        }
                    }
                }
            }
            ctx.idrettene.data->add(idrett);
        }
    }
}


void lagSpillerdataAction(DB::Context& ctx, const IO::CommandPair& actionCommand)
{
    IO::printline("printLagSpillerdata()");

    using std::size_t;
    using std::string;
    using std::pair;

    const auto CMD_VELG_IDRETT = Terminal::CommandID('I');
    const auto CMD_VELG_DIVISJON = Terminal::CommandID('D');
    const auto CMD_VELG_LAG = Terminal::CommandID('L');
    const auto CMD_BACK = Terminal::CommandID('B');
    const auto CMD_VIS = Terminal::CommandID('V');
    const auto CMD_ADD = Terminal::CommandID('A');
    const auto CMD_REMOVE = Terminal::CommandID('F');

    auto menu = IO::CommandMap{
        { CMD_BACK,           Terminal::Command{ "[B]ack", "G?tilbake" } },
        { CMD_VELG_IDRETT,    Terminal::Command{ "[I]drett",   "Filtrer Idrett" } },
        { CMD_VELG_DIVISJON,  Terminal::Command{ "[D]ivisjon", "Filtrer Divisjon" } },
        { CMD_VELG_LAG,       Terminal::Command{ "[L]ag",      "Filtrer Lag" } }
    };

    string searchNavnIdrett = "";
    string searchNavnDivisjon = "";
    string searchNavnLag = "";
    string selectedLag = "INGEN";

    for (;;)
    {
        IO::newpage();
        auto[resultatene, resultStr, status] = Search::filterLag(ctx, searchNavnIdrett, searchNavnDivisjon, searchNavnLag);

        if (resultatene.size() == 1)
        {
            selectedLag = resultatene[0].first.navn;
            if (menu.find(actionCommand.first) == menu.end())
            {
                menu.insert(menu.begin(), actionCommand);
            }
        }
        else
        {
            selectedLag = "INGEN";
            if (menu.find(actionCommand.first) != menu.end())
            {
                menu.erase(actionCommand.first);
            }
        }

        IO::printSubMenu(menu, "Print Spillere p?Lag - " + selectedLag);
        IO::printline("------------------------------------ FILTRE ------------------------------------");
        IO::printline("Idrett:      ", "[", searchNavnIdrett, "]");
        IO::printline("Divisjon:    ", "[", searchNavnDivisjon, "]");
        IO::printline("Lag:         ", "[", searchNavnLag, "]");
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

        case CMD_REMOVE:
        {
            unsigned int spillerToRemove = IO::readNumber("SpillerNr");

            auto idretten = (DB::Idrett*)ctx.idrettene.data->remove(resultatene[0].second[0].c_str()); //remove the idrett with the name from the filtered result's backtraced name
            for (auto& divisjon : idretten->divisjonene)
            {
                if (divisjon.navn.find(resultatene[0].second[1]) != std::string::npos)
                {
                    for (auto& laget : divisjon.lagene)
                    {
                        if (laget.navn.find(resultatene[0].first.navn) != std::string::npos)
                        {
                            std::size_t spillerCount = laget.spillerene.size();
                            laget.spillerene.erase(
                                std::remove_if(
                                    laget.spillerene.begin(),
                                    laget.spillerene.end(),
                                    [spillerToRemove](unsigned int nr) { return spillerToRemove == nr; }
                                ), laget.spillerene.end()
                            );
                            if (spillerCount != laget.spillerene.size())
                            {
                                IO::printline("Spiller nr", spillerToRemove, "Fjernet fra", resultatene[0].second[2]);
                                break;
                            }
                            IO::printline("Spiller nr", spillerToRemove, "var ikke ?finne i", resultatene[0].second[2]);
                        }
                    }
                }
            }
            ctx.idrettene.data->add(idretten);
            IO::waitForEnterPress(); //i.e. wait for ENTER
            break;
        }
        case CMD_ADD:
        {
            IO::printline("add");
            unsigned int spillerToAdd = IO::readNumber("SpillerNr");
            
            auto spilleren = (DB::Spiller*)ctx.spillerene.data->remove(spillerToAdd);
            if (!spilleren)
            {
                IO::printline("Spiller nr", spillerToAdd, "finnes ikke!");
                IO::printline("Legg spilleren til via hovedmenyen");
                IO::waitForEnterPress();
                break;
            }
            ctx.spillerene.data->add(spilleren);
            //HERE WE GOOOOOOOOOO!!!!! WHEoiahiishdia fml
            auto idretten = (DB::Idrett*)ctx.idrettene.data->remove(resultatene[0].second[0].c_str()); //remove the idrett with the name from the filtered result's backtraced name
            for (auto& divisjon : idretten->divisjonene)
            {
                if (divisjon.navn.find(resultatene[0].second[1]) != std::string::npos)
                {
                    for (auto& laget : divisjon.lagene)
                    {
                        if (laget.navn.find(resultatene[0].first.navn) != std::string::npos)
                        {
                            std::size_t spillerCount = laget.spillerene.size();
                            
                            if(std::find(laget.spillerene.begin(), laget.spillerene.end(), spillerToAdd) != laget.spillerene.end())
                            {
                                IO::printline("Spiller nr", spillerToAdd, "er allerede medlem i", resultatene[0].second[2]);
                                break;
                            }
                            IO::printline("Spiller nr", spillerToAdd, "lagt inn som medlem i", resultatene[0].second[2]);
                            laget.spillerene.push_back(spillerToAdd);
                            break;
                        }
                    }
                }
            }
            ctx.idrettene.data->add(idretten);
            
            IO::waitForEnterPress();
            break;
        }
        case CMD_VIS:
        {
            DB::Spillerene lagSpillerene(0);
            for (const auto& spillerID : resultatene[0].first.spillerene)
            {
                const auto spiller = (DB::Spiller*)ctx.spillerene.data->remove(spillerID);

                lagSpillerene.data->add(new DB::Spiller(*spiller));
                ctx.spillerene.data->add(spiller);
            }
            IO::printline("Spillerene p?laget: ", resultatene[0].first.navn);
            IO::printline(Encode::viewSpillerene(lagSpillerene));
            IO::waitForEnterPress();
            break;
        }
        default:
            break;
        }
    }
}

void App::printLagSpillerdata(DB::Context& ctx) 
{
    IO::printline("printLagSpillerdata()");


    const auto CMD_VIS = Terminal::CommandID('V');
    const auto displayCommand = IO::CommandPair{
        CMD_VIS, Terminal::Command{ "[V]is", "Vis alle spillere i det valgte laget" }
    };
    lagSpillerdataAction(ctx, displayCommand);
}
void App::insertLagSpiller(DB::Context& ctx)
{
    IO::printline("insertLagSpiller()");

    const auto CMD_ADD = Terminal::CommandID('A');
    const auto insertCommand = IO::CommandPair{
        CMD_ADD, Terminal::Command{ "[A]dd", "legg inn spiller" }
    };

    lagSpillerdataAction(ctx, insertCommand);
}

void App::removeLagSpiller(DB::Context& ctx) 
{
    IO::printline("removeLagSpiller()");

    const auto CMD_REMOVE = Terminal::CommandID('F');
    const auto insertCommand = IO::CommandPair{
        CMD_REMOVE, Terminal::Command{ "[F]jern", "legg inn spiller" }
    };

    lagSpillerdataAction(ctx, insertCommand);
}


void App::topp10(DB::Context& ctx)
{
    IO::printline("topp10Divisjon()");
    IO::printline();
    IO::divider('_', 80);
    IO::printline("!!!! ------------> FOREVER UNIMPLEMENTED <-----------!!!!");
    IO::divider('_', 80);
    IO::printline();
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


auto App::computeTabell (
    const DB::Divisjon& divisjon, 
    const DB::Idrett::TabellType tabelltype) -> DB::Tabell 
{         
    DB::Tabell tabell;

    for (const auto& [hjemmelag, bortelagene]: divisjon.terminliste) 
    {
        if (tabell.lagene.find(hjemmelag) == tabell.lagene.end()) {
            tabell.lagene[hjemmelag] = DB::Tabell::Lag{ };
        }

        for(const auto& [bortelag, resultat]: bortelagene) 
        {
            if (tabell.lagene.find(bortelag) == tabell.lagene.end()) {
                tabell.lagene[bortelag] = DB::Tabell::Lag{};
            }

            // 0. Continue if kamp has not been spilt
            if (!(resultat.spilt)) {
                continue;
            }

            // 1. Tell scoringer
            tabell.lagene[hjemmelag].hjemmeScoringer += resultat.hjemmeScorerene.size();
            tabell.lagene[hjemmelag].hjemmeBaklengs  += resultat.borteScorerene.size();
            tabell.lagene[bortelag].borteScoringer   += resultat.borteScorerene.size();
            tabell.lagene[bortelag].borteBaklengs    += resultat.hjemmeScorerene.size();

            using namespace DB;
            
            // 2. If   HJEMMELAG: SEIER                 BORTELAG: TAP     ? 
            if (resultat.hjemmeScorerene.size() > resultat.borteScorerene.size()) 
            {
                tabell.lagene[hjemmelag].seier += 1;
                tabell.lagene[bortelag].tap    += 1;

                switch (tabelltype) 
                {
                    case Idrett::SEIER_2_UAVGJORT_1_TAP_0:   
                        tabell.lagene[hjemmelag].poeng += 2;
                    break;

                    case Idrett::SEIER_3_UAVGJORT_1_TAP_0:   
                        tabell.lagene[hjemmelag].poeng += 3;
                    break;
                    case Idrett::SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0: 
                        if (resultat.overtid) 
                            tabell.lagene[hjemmelag].poeng += 2;
                        else 
                            tabell.lagene[hjemmelag].poeng += 3;
                    break;
                }
            }
            // 2. If    HJEMMELAG: UAVGJORT               BORTELAG: UAVGJORT
            else if (resultat.hjemmeScorerene.size() == resultat.borteScorerene.size())
            {
                tabell.lagene[hjemmelag].uavgjort += 1;
                tabell.lagene[bortelag].uavgjort  += 1;

                switch (tabelltype) 
                {
                    case Idrett::SEIER_2_UAVGJORT_1_TAP_0:   
                        tabell.lagene[hjemmelag].poeng += 1;
                        tabell.lagene[bortelag].poeng  += 1;
                    break;
                    case Idrett::SEIER_3_UAVGJORT_1_TAP_0:   
                        tabell.lagene[hjemmelag].poeng += 1;
                        tabell.lagene[bortelag].poeng  += 1;
                    break;
                    case Idrett::SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0: 
                        tabell.lagene[hjemmelag].poeng += 1;
                        tabell.lagene[bortelag].poeng  += 1;
                    break;
                }
            }
            // 3. If  HJEMMELAG:  TAP                    BORTELAG: SEIER                    
            else if(resultat.hjemmeScorerene.size() < resultat.borteScorerene.size()) 
            {
                tabell.lagene[hjemmelag].tap  += 1;
                tabell.lagene[bortelag].seier += 1;
                switch (tabelltype) 
                {
                    case Idrett::SEIER_2_UAVGJORT_1_TAP_0:   
                        tabell.lagene[bortelag].poeng  += 1;
                    break;
                    case Idrett::SEIER_3_UAVGJORT_1_TAP_0:   
                        tabell.lagene[bortelag].poeng  += 1;
                    break;
                    case Idrett::SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0: 
                        if (resultat.overtid) 
                            tabell.lagene[bortelag].poeng += 2;
                        else 
                            tabell.lagene[bortelag].poeng += 3;
                    break;
                }
            }
        }
    }
    return tabell;
};

//======================================
// BACKGROUND FUNCTIONS
//======================================
void App::readIdrettene(DB::Idrettene& idrettene, const std::string filepath)
{
    std::ifstream infile(filepath);
    if (!infile) {
        IO::printline("ERROR - No files at filepath", filepath);
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
        IO::printline("ERROR - No files at filepath", filepath);
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
        IO::printline("ERROR - No files at filepath", filepath);
        return;
    }

    auto outstring = Encode::dataIdrettene(ctx);
    outstream << outstring;
}

void App::writeSpillerene(DB::Spillerene& ctx, const std::string filepath)
{
    std::ofstream outstream(filepath);
    if (!outstream) {
        IO::printline("ERROR - No files at filepath", filepath);
        return;
    }

    auto outstring = Encode::dataSpillerene(ctx);
    outstream << outstring; 
}

} // ::gruppe32
