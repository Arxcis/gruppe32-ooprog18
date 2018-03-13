#include <gruppe32/App.hpp>

namespace gruppe32::App 
{

/**
 * short description. - Doxygen example
 * detailed description.
 * @param int - blah
 * @return int - blah
 */
void printSpillereAll(const DB::Context& ctx);
void printSpillereByName(const DB::Context& ctx);
void printSpillereByNumber(const DB::Context& ctx);

void printIdretterAll(const DB::Context& ctx);
void printIdretterByName(const DB::Context& ctx);

void createSpiller(DB::Context& ctx);
void createIdrett(DB::Context& ctx);
void createDivisjon(DB::Context& ctx);

void deleteSpiller(DB::Context& ctx);
void deleteIdrett(DB::Context& ctx);
void deleteDivisjon(DB::Context& ctx);


// print to terminal
void printTermin(const DB::Context& ctx);
void printResultatKampDivisjon(const DB::Context& ctx);
void printResultatKampIdrett(const DB::Context& ctx);
void printTabellDivisjon(const DB::Context& ctx);
void printTabellIdrett(const DB::Context& ctx);

// or print to file
void writeTermin(const DB::Context& ctx);
void writeResultatKampDivisjon(const DB::Context& ctx);
void writeResultatKampIdrett(const DB::Context& ctx);
void writeTabellDivisjon(const DB::Context& ctx);
void writeTabellIdrett(const DB::Context& ctx);

void readResultatliste(DB::Context& ctx);

void printLagSpillerdata(const DB::Context& ctx);
void insertLagSpiller(DB::Context& ctx);
void removeLagSpiller(DB::Context& ctx);


} // end namespace gruppe32::App