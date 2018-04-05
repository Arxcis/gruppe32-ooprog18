#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <map>

#include <gruppe32/IO.hpp>
#include <gruppe32/DB.hpp>

namespace gruppe32 
{

/// <summary> Doing a search through the data, and returning a vector with the resutls </summary>
namespace Search 
{

using std::vector;
using std::string;
using std::size_t;
using std::tuple;
using std::pair;

using returnSpillerene = pair<vector<DB::Spiller>, string>;
using returnDivisjonene = pair<vector<DB::Divisjon>, string>;
using returnDivisjoneneMedIdrettNavn = pair<vector<pair<DB::Divisjon, string>>, string>;
using returnResultatene = pair<vector<DB::ViewResultat>, string>;
    //  functions
    
template<typename T >// RESULT DATA, RESULT STRING, STATUS STRING
using filterResult = tuple<vector<pair<T, vector<string>>>, string, string>;

auto filterLag(
    DB::Context & ctx,
    const string & navnIdrett,
    const string & navnDivisjon,
    const string & navnLag)
    ->filterResult<DB::Lag>;

auto findAndPrintIdrettDivisjon(
    DB::Context& ctx,
    const string& navnIdrett,
    const string& navnDivisjon)->Search::returnDivisjoneneMedIdrettNavn;

auto divisjonene(
    DB::Context& ctx,
    const string& navnIdrett, 
    const string& navnDivisjon) -> Search::returnDivisjonene;

auto resultatene(
    DB::Context& ctx, 
    const DB::Divisjon& divisjonene, 
    const size_t year, 
    const size_t month, 
    const size_t day) -> Search::returnResultatene;


template<class Container>
auto makeStatus(Container container, const std::string info) -> std::string
{
    return "Search -> " + std::to_string(container.size()) + " hits                  ("+ info + ")";
}
template<class Container>
auto makeStatus(Container container) -> std::string
{
    return "Search -> " + std::to_string(container.size()) + " hits";
}


} // ::Search
} // ::gruppe32