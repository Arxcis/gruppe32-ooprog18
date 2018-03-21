#include <gruppe32/App.hpp>

namespace gruppe32::App 
{

//======================================
// COMMAND FUNCTIONS
//======================================

void printSpillereAll(DB::Context& ctx) 
{
    IO::printline(ctx.spillerene.data->noOfElements());
    IO::printline();
    IO::printline(Encode::viewSpillerene(ctx.spillerene));
}
void printSpillereByName(DB::Context& ctx, const std::string name) 
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
void printSpillereByNumber(DB::Context& ctx, const std::size_t number) 
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

void printIdretterAll(DB::Context& ctx) 
{
    IO::printline();
    IO::printline(Encode::viewIdrettene(ctx.idrettene));
}

void printIdretterByName( DB::Context& ctx, const std::string name) 
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

void createSpiller(DB::Context& ctx) 
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
            spillerAdresse = IO::readAdress();
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
void createIdrett(DB::Context& ctx) 
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
void createDivisjon(DB::Context& ctx) 
{
    IO::printline("createDivisjon()");
}

void deleteSpiller(DB::Context& ctx) 
{
    IO::printline("deleteSpiller()");
}
void deleteIdrett(DB::Context& ctx) 
{
    IO::printline("deleteIdrett()");
}
void deleteDivisjon(DB::Context& ctx) 
{
    IO::printline("deleteDivisjon()");
}


// print to terminal
void printTerminDivisjon(DB::Context& ctx) 
{
    using std::size_t;
    using std::string;

    // 0. Skriv ut idretter
    IO::printline();
    IO::divider('_', 80);    
    IO::printline();
    IO::printline(Encode::viewIdrettene(ctx.idrettene));
    IO::divider('_', 80);
    for (;;) 
    {
        // 1. Setup possible commands
        auto commandMap = Terminal::Command::Map {
            Terminal::keyCommandNameIdrett,
            Terminal::keyCommandBack
        };
        // 2. Print menu
        IO::printMenu(commandMap, "HOME -> Skriv Terminliste -> Velg en Idrett");

        // 3. Read command
        auto [cmdkey, command, _, idrettName] = IO::readEitherCommandName(commandMap);
        if (cmdkey == Terminal::CMD_BACK)
            return;


        // 4. Try to find idrett
        auto idrett = (DB::Idrett*)ctx.idrettene.data->remove(idrettName.c_str());
        if (!idrett) {
            IO::printline("Idrett not found");
            continue;
        }
        if (idrett->divisjonene.size() == 0) {
            ctx.idrettene.data->add(idrett);
            IO::printline(idrett->name, "has no divisjoner");
            continue;
        }

        // 5. Print out possible divisjoner to help the user pick
        IO::printline();
        IO::printline();
        IO::printline();
        IO::divider('_', 80);
        printDivisjonene((*idrett));
        IO::divider('_', 80);
            
        // 6. Setup possible commands for read divisjon
        commandMap = Terminal::Command::Map {
            Terminal::keyCommandNameDivisjon,
            Terminal::keyCommandBack
        };
        // 7. Print menu
        IO::printMenu(commandMap, "HOME -> Skriv Terminliste -> Velg en divisjon");

        // 8. Read divisjon
        auto [cmdkey2, command2, _2, divisjonName] = IO::readEitherCommandName(commandMap);
        if (cmdkey2 == Terminal::CMD_BACK) {
            ctx.idrettene.data->add(idrett);
            return;
        }

        IO::divider('_', 80);

        // 9. Iterate through all divisjoner
        for (const auto& divisjon : idrett->divisjonene)
        {
            if (divisjon.navn.find(divisjonName) != std::string::npos)
            {
                IO::printline(divisjon.navn, ": terminliste");
                IO::printline();
                auto terminliste = DB::Terminliste {
                    divisjon.navn,
                    divisjon.terminliste
                };
                IO::printline(Encode::viewTerminliste(terminliste));
                IO::printline();
            }
        }

        IO::divider('_', 80);

        ctx.idrettene.data->add(idrett);
    }
}


void printResultatKampDivisjon(DB::Context& ctx) 
{
   // 0. Skriv ut idretter
    IO::printline();
    IO::divider('_', 80);    
    IO::printline();
    IO::printline(Encode::viewIdrettene(ctx.idrettene));
    IO::divider('_', 80);
    for (;;) 
    {
        // 1. Setup possible commands
        auto commandMap = Terminal::Command::Map {
            Terminal::keyCommandNameIdrett,
            Terminal::keyCommandBack
        };
        // 2. Print menu
        IO::printMenu(commandMap, "HOME -> Resultater Divisjon -> Velg en Idrett");

        // 3. Read command
        auto [cmdkey, command, _, idrettName] = IO::readEitherCommandName(commandMap);
        if (cmdkey == Terminal::CMD_BACK)
            return;


        // 4. Try to find idrett
        auto idrett = (DB::Idrett*)ctx.idrettene.data->remove(idrettName.c_str());
        if (!idrett) {
            IO::printline("Idrett not found");
            continue;
        }
        if (idrett->divisjonene.size() == 0) {
            ctx.idrettene.data->add(idrett);
            IO::printline(idrett->name, "has no divisjoner");
            continue;
        }

        // 5. Print out possible divisjoner to help the user pick
        IO::printline();
        IO::printline();
        IO::printline();
        IO::divider('_', 80);
        printDivisjonene((*idrett));
        IO::divider('_', 80);
            
        // 6. Setup possible commands for read divisjon
        commandMap = Terminal::Command::Map {
            Terminal::keyCommandNameDivisjon,
            Terminal::keyCommandBack
        };
        // 7. Print menu
        IO::printMenu(commandMap, "HOME -> Resultater Divisjon -> Velg Divisjon");

        // 8. Read divisjon
        auto [cmdkey2, command2, _2, divisjonName] = IO::readEitherCommandName(commandMap);
        if (cmdkey2 == Terminal::CMD_BACK) {
            ctx.idrettene.data->add(idrett);
            return;
        }
            
        // 9. Read year
        IO::printline("Årstall: 1970-2099");
        size_t year = IO::readYear();
        IO::printline("Måned:   01-12");
        size_t month = IO::readMonth();
        IO::printline("Dag:     01-31");
        size_t day = IO::readDay();
        ctx.idrettene.data->add(idrett);
    }
}


void writeResultatKampDivisjon(DB::Context& ctx) 
{
    IO::printline("writeResultatKampDivisjon()");
}


void printResultatKampIdrett(DB::Context& ctx) 
{
    IO::printline("printResultatKampIdrett()");
}
void writeResultatKampIdrett(DB::Context& ctx) 
{
    IO::printline("writeResultatKampIdrett()");
}


void printTabellDivisjon(DB::Context& ctx) 
{
    IO::printline("printTabellDivisjon()");
}
void writeTabellDivisjon(DB::Context& ctx) 
{
    IO::printline("writeTabellDivisjon()");
}


void printTabellIdrett(DB::Context& ctx) 
{
    IO::printline("printTabellIdrett()");
}
void writeTabellIdrett(DB::Context& ctx) 
{
    IO::printline("writeTabellIdrett()");
}


// or print to file
void writeTerminDivisjon(DB::Context& ctx) 
{
    IO::printline("writeTermin()");
}





void readResultatliste(DB::Context& ctx) 
{
    IO::printline("readResultatliste()");
}

void printLagSpillerdata(DB::Context& ctx) 
{
    IO::printline("printLagSpillerdata()");
}
void insertLagSpiller(DB::Context& ctx)
{
    IO::printline("insertLagSpiller()");
}
void removeLagSpiller(DB::Context& ctx) 
{
    IO::printline("removeLagSpiller()");
}


void printTopp10Divisjon(DB::Context& ctx)
{
    IO::printline("printToppscorerTopp10Divisjon()");
}
void printTopp10Lag(DB::Context& ctx)
{
    IO::printline("printToppscorerTopp10Lag()");
}


void writeTopp10Divisjon(DB::Context& ctx)
{
    IO::printline("writeToppscorerTopp10Divisjon()");
}
void writeTopp10Lag(DB::Context& ctx)
{
    IO::printline("writeToppscorerTopp10Lag()");
}



//======================================
// HELPER FUNCTIONS
//======================================

// @DEPRECATED jsolsvik 20.03.2018

void printDivisjonene(const DB::Idrett& idrett)
{
    IO::printline("Divisjonene:");
    for (const auto& divisjon : idrett.divisjonene)
    {
        IO::printline("- ", divisjon.navn);
    }
}

void printSpiller(const DB::Spiller& spiller)
{
    IO::printline();
    IO::printline("  ", spiller.name);
    IO::printline("   - Nummer:", spiller.guid);
    IO::printline("   - Adresse:", spiller.address);
};

void printIdrett(const DB::Idrett& idrett)
{
    IO::printline();
    IO::printline("  ", idrett.name);
    IO::printline("   - Tabelltype:", idrett.tabell);
    IO::printline("   - Antall divisjoner:", idrett.divisjonene.size());
}

//======================================
// BACKGROUND FUNCTIONS
//======================================
void readIdrettene(DB::Idrettene& idrettene, const std::string filepath)
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

void readSpillerene(DB::Spillerene& spillerene, const std::string filepath)
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

void writeIdrettene(DB::Idrettene& ctx, const std::string filepath)
{
    std::ofstream outstream(filepath);
    if (!outstream) {
        IO::printline("No files at filepath", filepath);
        return;
    }

    auto outstring = Encode::dataIdrettene(ctx);
    outstream << outstring;
}

void writeSpillerene(DB::Spillerene& ctx, const std::string filepath)
{
    std::ofstream outstream(filepath);
    if (!outstream) {
        IO::printline("No files at filepath", filepath);
        return;
    }

    auto outstring = Encode::dataSpillerene(ctx);
    outstream << outstring; 
}

} // end namespace gruppe32::App
