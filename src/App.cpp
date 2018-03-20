#include <gruppe32/App.hpp>

namespace gruppe32::App 
{

//======================================
// COMMAND FUNCTIONS
//======================================


/**
 * short description. - Doxygen example
 * detailed description.
 * @param int - blah
 * @return int - blah
 */
void printSpillereAll(DB::Context& ctx) 
{
    IO::printline(ctx.spillerene.data->noOfElements());
    IO::printline("printSpillereAll()");
    IO::printline();
    IO::printline(Encode::viewSpillerene(ctx.spillerene));

    // @DEPRECATED jsolsvik 20.03.2018
    /*
        std::size_t count = ctx.spillerene.data->noOfElements();
        for(std::size_t i = 1; i <= count; i++)
        {
            auto current = (DB::Spiller*)ctx.spillerene.data->removeNo(i);
            printSpiller(*current);
            ctx.spillerene.data->add(current);
        }
    */      
}
void printSpillereByName(DB::Context& ctx, const std::string name) 
{
    IO::printline("printSpillereByName()");
    IO::printline();
    IO::printline("Spiller", "\"" + name + "\"", "etterspurt");
    
    DB::Spillerene viewSpillerene;

    std::size_t count = ctx.spillerene.data->noOfElements();
    for (std::size_t i = 1; i <= count; i++)
    {
        auto current = (DB::Spiller*)ctx.spillerene.data->removeNo(i);
        if (current->name.find(name) != std::string::npos)
        {

            // @DEPRECATED jsolsvik 20.03.2018 
            /*
                  //  IO::printline("Spiller funnet!");
                   // IO::printline();
                    // printSpiller(*current);
                   // IO::printline();
            */

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
    if (element) 
    {

            // @DEPRECATED jsolsvik 20.03.2018
            /*
                IO::printline("Spiller funnet!");
                IO::printline();
                printSpiller(*element);
                IO::printline();
            */
        viewSpillerene.data->add(new DB::Spiller(element->guid, element->name, element->address));
        ctx.spillerene.data->add(element);

        IO::printline();
        IO::printline(Encode::viewSpillerene(viewSpillerene));
    }
    else 
    {
        IO::printline("Spiller ikke funnet!");
    }
    
}

void printIdretterAll(DB::Context& ctx) 
{
    IO::printline("printIdretterAll()");
    IO::printline();
    IO::printline(Encode::viewIdrettene(ctx.idrettene));
    
    // @DEPRECATED jsolsvik 20.03.2018
    /*
        std::size_t count = ctx.idrettene.data->noOfElements();
        for (std::size_t i = 1; i <= count; i++)
        {
            auto current = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
            
            printIdrett(*current);
            ctx.idrettene.data->add(current);
        }
    */
}

void printIdretterByName( DB::Context& ctx, const std::string name) 
{
    IO::printline("printIdretterByName()");
    IO::printline();
    IO::printline("Idrett med navn \"", name, "\" etterspurt");

    //TODO the entire name needs to be written, we could make it robust by looping through, but that would involve discarding the usefulness of a sorted list.
    auto idrett = (DB::Idrett*)ctx.idrettene.data->remove(name.c_str());
    std::size_t count = ctx.idrettene.data->noOfElements();
    if (!idrett && count > 0) 
    {
        for (std::size_t i = 1; i <= count; i++)
        {
            auto current = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
            if (current->name.find(name) != std::string::npos)
            {

                IO::printline();
                IO::printline(Encode::viewIdrett(*current));

    // @DEPRECATED jsolsvik 20.03.2018
    /*
                IO::printline("Idrett funnet!");
                printIdrett(*current);
                IO::printline();
                for (auto const& divisjon : current->divisjonene)
                {
                    IO::printline("    ", divisjon.navn);
                    IO::printline("     - Antall Lag:", divisjon.lagene.size());
                    IO::printline();
                    for (auto const& lag : divisjon.lagene)
                    {
                        IO::printline("      ", lag.navn);
                        IO::printline("       - Spillere:", lag.spillerene.size());
                        IO::printline("       - Adresse:", lag.adresse);
                    }
                }
      
    */
            }
            ctx.idrettene.data->add(current);
        }
    }
    else
    {
        IO::printline();
        IO::printline(Encode::viewIdrett(*idrett));

    // @DEPRECATED jsolsvik 20.03.2018
    /*
        IO::printline("Idrett funnet!");
        printIdrett(*idrett);
        IO::printline();
        for (auto const& divisjon : idrett->divisjonene)
        {
            IO::printline("    ",divisjon.navn);
            IO::printline("     - Antall Lag:", divisjon.lagene.size());
            IO::printline();
            for (auto const& lag : divisjon.lagene)
            {
                IO::printline("      ", lag.navn);
                IO::printline("       - Spillere:", lag.spillerene.size());
                IO::printline("       - Adresse:", lag.adresse);
            }
        }
        IO::printline();
        */
        ctx.idrettene.data->add(idrett);
    }
}

void createSpiller(DB::Context& ctx) 
{
    IO::printline("createSpiller()");
}
void createIdrett(DB::Context& ctx) 
{
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

    IO::printline("printTerminDivisjon()");
    IO::printline();

    printDivisjonene(ctx.idrettene);


    IO::printline(
        "---------------------------------\n",
        "Skriv inn <divisjon> or b for back:");
    

    auto [cmdkey, command, _, name] = IO::readEitherCommandName({
        Terminal::commandBackPair,
        Terminal::commandNamePair
    });
    if (cmdkey == Terminal::CMD_BACK)
        return;

    IO::printline("--------------");

    for (size_t i = 1; i <= ctx.idrettene.data->noOfElements(); i++)
    {
        auto idrett = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
        for (const auto& divisjon : idrett->divisjonene)
        {
            if (divisjon.navn.find(name) != std::string::npos)
            {
                auto terminliste = DB::Terminliste {
                    divisjon.navn,
                    divisjon.terminliste
                };
                IO::printline(Encode::viewTerminliste(terminliste));
            }
        }
        ctx.idrettene.data->add(idrett);
    }
}


void printResultatKampDivisjon(DB::Context& ctx) 
{
    IO::printline("printResultatKampDivisjon()");
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

void printDivisjonene(DB::Idrettene& idrettene)
{
    IO::printline("Divisjonene:");
    // Print list of divisjon
    for (size_t i = 1; i <= idrettene.data->noOfElements(); i++)
    {
        auto idrett = (DB::Idrett*)idrettene.data->removeNo(i);
        for (const auto& divisjon : idrett->divisjonene)
        {
            IO::printline("- ", divisjon.navn);
        }
        idrettene.data->add(idrett);
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
