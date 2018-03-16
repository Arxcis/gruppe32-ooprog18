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
    //defined as lambda for later when we make a place for helperfuncs
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
}

void printIdretterByName( DB::Context& ctx, const std::string name) 
{
    IO::printline("printIdretterByName()");
    IO::printline();
    IO::printline("Idrett med navn \"", name, "\" etterspurt");

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
    IO::printline("Nr:", spiller.guid);
    IO::printline("Navn:", spiller.name);
    IO::printline("Adresse:", spiller.address);
};

} // end namespace gruppe32::App