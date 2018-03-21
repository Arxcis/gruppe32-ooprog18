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

    const auto validCommands = IO::CommandMap{
        { Terminal::CMD_SPILLER_NAVN, Terminal::Command{ string(1, Terminal::CMD_SPILLER_NAVN), "Sett navn" } },
        { Terminal::CMD_SPILLER_ADRESSE, Terminal::Command{ string(1, Terminal::CMD_SPILLER_ADRESSE), "Sett adresse..." } },
        Terminal::commandCommitPair,
        Terminal::commandBackPair
    };
    auto nySpiller = new DB::Spiller{ 0, "", "" };
    for (;;)
    {
        IO::printMenu(validCommands, "HOME -> Lag ny -> Spiller");
        IO::printline("Navn:",      nySpiller->name);
        IO::printline("Adresse:",   nySpiller->address);
        IO::divider('_', 40);
        auto[cmdKey, cmd] = IO::readCommand(validCommands);
            switch (cmdKey)
            {
            case Terminal::CMD_SPILLER_NAVN:
                nySpiller->name = IO::readName();
                break;
            case Terminal::CMD_SPILLER_ADRESSE:
                nySpiller->address = IO::readAddress();
                break;

            case Terminal::CMD_COMMIT:
                //TODO -> VALIDER SPILLER
                IO::printline("Legger til ", nySpiller->name);
                //TODO assign guid
                IO::printline(nySpiller->name, "lagt til med nr:", nySpiller->guid);
                //ctx.spillerene.data->add(nySpiller);
                return;
            case Terminal::CMD_BACK:
                IO::printline("Avbryter...");
                IO::printline("Ingen ny spiller lagt til.");
                delete nySpiller;
                return;
            default:
                IO::printline("Not a valid command!");
                break;
            }
    }   
}


void App::createIdrett(DB::Context& ctx) 
{
    IO::printline("createIdrett()");
}


void App::createDivisjon(DB::Context& ctx) 
{
    IO::printline("createDivisjon()");
}


void App::deleteSpiller(DB::Context& ctx) 
{
    IO::printline("deleteSpiller()");
}


void App::deleteIdrett(DB::Context& ctx) 
{
    IO::printline("deleteIdrett()");
}


void App::deleteDivisjon(DB::Context& ctx) 
{
    IO::printline("deleteDivisjon()");
}


void App::printTerminliste(DB::Context& ctx) 
{
    using std::size_t;
    using std::string;
    using std::pair;

    const auto validCommands = IO::CommandMap {
        { Terminal::CMD_NAME_IDRETT,  Terminal::Command{   "[I]drett",  "Input name of an Idrett" }},    
        { Terminal::CMD_NAME_DIVISJON,  Terminal::Command{ "[D]ivisjon", "Input name of a Divisjon" }},
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
        for (const auto& div : divisjonene) {
            auto terminliste = DB::Terminliste { div.navn, div.terminliste };
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

            default:
                break;
        }
    }
}


void App::printResultatKampDivisjon(DB::Context& ctx) 
{
    const auto validCommands = IO::CommandMap {
        { Terminal::CMD_NAME_IDRETT,  Terminal::Command{   "[I]drett",  "Input name of an Idrett" }},    
        { Terminal::CMD_NAME_DIVISJON,  Terminal::Command{ "[D]ivisjon", "Input name of a Divisjon" }},
        Terminal::keyCommandBack
    };

    string navnIdrett   = "";
    string navnDivisjon = "";
    size_t month = 0;
    size_t day   = 0;
    size_t year  = 0;

    for (;;) 
    {
        // Display menu
        IO::newpage();
        IO::printline();
        IO::printline(Encode::viewIdretteneCompact(ctx.idrettene, true));
        IO::printMenu(validCommands, "HOME -> Terminliste");
        IO::printline("-- Input");
        IO::printline("Idrett:",    navnIdrett);
        IO::printline("Divisjon:",  navnDivisjon);
        IO::printline("Month:",     year);
        IO::printline("Month:",     month);
        IO::printline("Day:",       day);
        IO::divider('_', 80);

        // Search for divisjoner and resultater
        auto[divisjonene, statusDivisjonene] = Search::divisjonene(ctx, navnIdrett, navnDivisjon);
        IO::printline(statusDivisjonene);  

        auto[resulatene, statusResultatene] = Search::resultatene(ctx, divisjonene, month, day); 
        IO::printline(statusResultatene);        

        // Display resultater
        IO::printline();
        for (const auto& res : resulatene) {

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

            case Terminal::CMD_DATE_MONTH:
                month = IO::readMonth();
                break;

            case Terminal::CMD_DATE_DAY:
                day = IO::readDay();
                break;

            case Terminal::CMD_BACK:   
                return;

            default:
                break;            
        }
    }
}


void App::writeResultatKampDivisjon(DB::Context& ctx) 
{
    IO::printline("writeResultatKampDivisjon()");
}


void App::printResultatKampIdrett(DB::Context& ctx) 
{
    IO::printline("printResultatKampIdrett()");
}
void App::writeResultatKampIdrett(DB::Context& ctx) 
{
    IO::printline("writeResultatKampIdrett()");
}


void App::printTabellDivisjon(DB::Context& ctx) 
{
    IO::printline("printTabellDivisjon()");
}

void App::writeTabellDivisjon(DB::Context& ctx) 
{
    IO::printline("writeTabellDivisjon()");
}


void App::printTabellIdrett(DB::Context& ctx) 
{
    IO::printline("printTabellIdrett()");
}
void App::writeTabellIdrett(DB::Context& ctx) 
{
    IO::printline("writeTabellIdrett()");
}


// or print to file
void App::writeTerminDivisjon(DB::Context& ctx) 
{
    IO::printline("writeTermin()");
}





void App::readResultatliste(DB::Context& ctx) 
{
    IO::printline("readResultatliste()");
}

void App::printLagSpillerdata(DB::Context& ctx) 
{
    IO::printline("printLagSpillerdata()");
}
void App::insertLagSpiller(DB::Context& ctx)
{
    IO::printline("insertLagSpiller()");
}
void App::removeLagSpiller(DB::Context& ctx) 
{
    IO::printline("removeLagSpiller()");
}


void App::printTopp10Divisjon(DB::Context& ctx)
{
    IO::printline("printToppscorerTopp10Divisjon()");
}
void App::printTopp10Lag(DB::Context& ctx)
{
    IO::printline("printToppscorerTopp10Lag()");
}


void App::writeTopp10Divisjon(DB::Context& ctx)
{
    IO::printline("writeToppscorerTopp10Divisjon()");
}
void App::writeTopp10Lag(DB::Context& ctx)
{
    IO::printline("writeToppscorerTopp10Lag()");
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
    IO::printline();
    IO::printline("  ", spiller.name);
    IO::printline("   - Nummer:", spiller.guid);
    IO::printline("   - Adresse:", spiller.address);
};

void App::printIdrett(const DB::Idrett& idrett)
{
    IO::printline();
    IO::printline("  ", idrett.name);
    IO::printline("   - Tabelltype:", idrett.tabell);
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
using std::pair;

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

    // Error 3
    if (navnDivisjon.empty()) {
        statusmsg = "No divisjon specified";

        ctx.idrettene.data->add(idrett);   // because why no
        return Search::returnDivisjonene{result, statusmsg};
    }

    for (const auto& divisjon : idrett->divisjonene)
    {
        // Success
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

auto Search::resultatene(DB::Context& ctx, const std::vector<DB::Divisjon>& divisjonene, const std::size_t month, const std::size_t day) 
    -> Search::returnResultatene 
{

}
} // end namespace gruppe32::App
