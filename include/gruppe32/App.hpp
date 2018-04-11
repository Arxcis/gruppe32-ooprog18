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
#include <gruppe32/Search.hpp>

namespace gruppe32 {


/// <summary> Functions which satifised the functional requirements </summary>
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
auto computeTabell(
    const DB::Divisjon& divisjon,
    const DB::Idrett::TabellType tabelltype)->DB::Tabell;

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

} // ::gruppe32
