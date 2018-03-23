    #pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <gruppe32/IO.hpp>
#include <gruppe32/DB.hpp>
#include <gruppe32/Parser.hpp>

/// <summary> Functions which satifised the functional requirements </summary>
namespace gruppe32 {

namespace App 
{
    using std::string;
    using std::size_t;
//
// COMMAND FUNCTIONS
//
void printSpillereAll(DB::Context& ctx);
void printSpillereByName(DB::Context& ctx, const string name);
void printSpillereByNumber(DB::Context& ctx, const size_t number);

void printIdretterAll(DB::Context& ctx);
void printIdretterByName(DB::Context& ctx, const string name);

void createSpiller(DB::Context& ctx);
void createIdrett(DB::Context& ctx);
void createDivisjon(DB::Context& ctx);

void deleteSpiller(DB::Context& ctx);
void deleteIdrett(DB::Context& ctx);
void deleteDivisjon(DB::Context& ctx);


void terminliste(DB::Context& ctx);
void resultatene(DB::Context& ctx);
void tabell(DB::Context& ctx);

void readResultatliste(DB::Context& ctx);

void printLagSpillerdata(DB::Context& ctx);
void insertLagSpiller(DB::Context& ctx);
void removeLagSpiller(DB::Context& ctx);

// Topp 10
void topp10(DB::Context& ctx);

//
// HELPER FUNCTIONS
//
void printSpiller(const DB::Spiller& spiller);
void printIdrett(const DB::Idrett& idrett);
void printDivisjonene(const DB::Idrett& idrett);
void printIdrettene(DB::Idrettene& idrettene);

//
// BACKGROUND FUNCTIONS
//
void readIdrettene(DB::Idrettene& ctx, const string filepath);
void writeIdrettene(DB::Idrettene& ctx, const string filepath);
void readSpillerene(DB::Spillerene& ctx, const string filepath);
void writeSpillerene(DB::Spillerene& ctx, const string filepath);


} // ::App

/// <summary> Doing a search through the data, and returning a vector with the resutls </summary>
namespace Search 
{

using std::pair;
using std::vector;
using std::string;
using std::size_t;

using returnSpillerene = pair<vector<DB::Spiller>, string>;
using returnDivisjonene = pair<vector<DB::Divisjon>, string>;
using returnDivisjoneneMedIdrettNavn = pair<vector<pair<DB::Divisjon, string>>, string>;
using returnResultatene = pair<vector<DB::ViewResultat>, string>;
    //  functions
    
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
} // ::Search

} // ::gruppe32
