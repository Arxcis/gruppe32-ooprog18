#include <gruppe32/App.hpp>

namespace gruppe32::App 
{

/**
 * short description. - Doxygen example
 * detailed description.
 * @param int - blah
 * @return int - blah
 */
void printSpillereAll(DB::Context& ctx) 
{
    IO::printline("printSpillereAll()");
    std::size_t count = ctx.spillerene.data->noOfElements();
    for(std::size_t i = 1; i <= count; i++)
    {
        auto current = (DB::Spiller*)ctx.spillerene.data->removeNo(i);
        printSpiller(*current);
        ctx.spillerene.data->add(current);
    }

}
void printSpillereByName(DB::Context& ctx, const std::string name) 
{
    IO::printline("printSpillereByName()");
    IO::printline();
    IO::printline("Spiller", "\"" + name + "\"", "etterspurt");
    
    std::size_t count = ctx.spillerene.data->noOfElements();
    for (std::size_t i = 1; i <= count; i++)
    {
        auto current = (DB::Spiller*)ctx.spillerene.data->removeNo(i);
        if (current->name.find(name) != std::string::npos)
        {
            IO::printline("Spiller funnet!");
            IO::printline();
            printSpiller(*current);
            IO::printline();
        }
        ctx.spillerene.data->add(current);
    }
}
void printSpillereByNumber(DB::Context& ctx, const std::size_t number) 
{
    IO::printline("printSpillereByNumber()");
    IO::printline();
    IO::printline("Spiller nr", number, "etterspurt");

    auto element = (DB::Spiller*)ctx.spillerene.data->remove((int)number);
    if (element) 
    {
        IO::printline("Spiller funnet!");
        IO::printline();
        printSpiller(*element);
        IO::printline();
        ctx.spillerene.data->add(element);
    }
    else 
    {
        IO::printline("Spiller ikke funnet!");
    }
    
}

void printIdretterAll(DB::Context& ctx) 
{
    IO::printline("printIdretterAll()");
    std::size_t count = ctx.idrettene.data->noOfElements();
    for (std::size_t i = 1; i <= count; i++)
    {
        auto current = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
        printIdrett(*current);
        ctx.idrettene.data->add(current);
    }
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
            }
            ctx.idrettene.data->add(current);
        }
    }
    else
    {
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
void printTerminDivisjon(const DB::Context& ctx) 
{
    IO::printline("printTerminDivisjon()");
}
void printResultatKampDivisjon(const DB::Context& ctx) 
{
    IO::printline("printResultatKampDivisjon()");
}
void printResultatKampIdrett(const DB::Context& ctx) 
{
    IO::printline("printResultatKampIdrett()");
}
void printTabellDivisjon(const DB::Context& ctx) 
{
    IO::printline("printTabellDivisjon()");
}
void printTabellIdrett(const DB::Context& ctx) 
{
    IO::printline("printTabellIdrett()");
}

// or print to file
void writeTerminDivisjon(const DB::Context& ctx) 
{
    IO::printline("writeTermin()");
}
void writeResultatKampDivisjon(const DB::Context& ctx) 
{
    IO::printline("writeResultatKampDivisjon()");
}
void writeResultatKampIdrett(const DB::Context& ctx) 
{
    IO::printline("writeResultatKampIdrett()");
}
void writeTabellDivisjon(const DB::Context& ctx) 
{
    IO::printline("writeTabellDivisjon()");
}
void writeTabellIdrett(const DB::Context& ctx) 
{
    IO::printline("writeTabellIdrett()");
}

void readResultatliste(DB::Context& ctx) 
{
    IO::printline("readResultatliste()");
}

void printLagSpillerdata(const DB::Context& ctx) 
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


void printTopp10Divisjon(const DB::Context& ctx)
{
    IO::printline("printToppscorerTopp10Divisjon()");
}
void printTopp10Lag(const DB::Context& ctx)
{
    IO::printline("printToppscorerTopp10Lag()");
}


void writeTopp10Divisjon(const DB::Context& ctx)
{
    IO::printline("writeToppscorerTopp10Divisjon()");
}
void writeTopp10Lag(const DB::Context& ctx)
{
    IO::printline("writeToppscorerTopp10Lag()");
}



//======================================
// HELPER FUNCTIONS
//======================================

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

} // end namespace gruppe32::App