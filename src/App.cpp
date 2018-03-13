#include <gruppe32/App.hpp>

namespace gruppe32::App 
{

/**
 * short description. - Doxygen example
 * detailed description.
 * @param int - blah
 * @return int - blah
 */
void printSpillereAll(const DB::Context& ctx) 
{
    IO::printline("printSpillereAll()");
}
void printSpillereByName(const DB::Context& ctx, const std::string name) 
{
    IO::printline("printSpillereByName()");
}
void printSpillereByNumber(const DB::Context& ctx, const std::size_t number) 
{
    IO::printline("printSpillereByNumber()");
}

void printIdretterAll(const DB::Context& ctx) 
{
    IO::printline("printIdretterAll()");
}

void printIdretterByName(const DB::Context& ctx, const std::string name) 
{
    IO::printline("printIdretterByName()");
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


void printToppscorerTopp10Divisjon(const DB::Context& ctx)
{
    IO::printline("printToppscorerTopp10Divisjon()");
}
void printToppscorerTopp10Lag(const DB::Context& ctx)
{
    IO::printline("printToppscorerTopp10Lag()");
}


void writeToppscorerTopp10Divisjon(const DB::Context& ctx)
{
    IO::printline("writeToppscorerTopp10Divisjon()");
}
void writeToppscorerTopp10Lag(const DB::Context& ctx)
{
    IO::printline("writeToppscorerTopp10Lag()");
}



} // end namespace gruppe32::App