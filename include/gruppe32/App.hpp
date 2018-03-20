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
namespace gruppe32::App 
{

//
// COMMAND FUNCTIONS
//
void printSpillereAll(DB::Context& ctx);
void printSpillereByName(DB::Context& ctx, const std::string name);
void printSpillereByNumber(DB::Context& ctx, const std::size_t number);

void printIdretterAll(DB::Context& ctx);
void printIdretterByName(DB::Context& ctx, const std::string name);

void createSpiller(DB::Context& ctx);
void createIdrett(DB::Context& ctx);
void createDivisjon(DB::Context& ctx);

void deleteSpiller(DB::Context& ctx);
void deleteIdrett(DB::Context& ctx);
void deleteDivisjon(DB::Context& ctx);


// Print to console
void printTerminDivisjon(const DB::Context& ctx);
void printResultatKampDivisjon(const DB::Context& ctx);
void printResultatKampIdrett(const DB::Context& ctx);
void printTabellDivisjon(const DB::Context& ctx);
void printTabellIdrett(const DB::Context& ctx);

// or Write to file
void writeTerminDivisjon(const DB::Context& ctx);
void writeResultatKampDivisjon(const DB::Context& ctx);
void writeResultatKampIdrett(const DB::Context& ctx);
void writeTabellDivisjon(const DB::Context& ctx);
void writeTabellIdrett(const DB::Context& ctx);

void readResultatliste(DB::Context& ctx);

void printLagSpillerdata(const DB::Context& ctx);
void insertLagSpiller(DB::Context& ctx);
void removeLagSpiller(DB::Context& ctx);

// Topp 10
void printTopp10Divisjon(const DB::Context& ctx);
void printTopp10Lag(const DB::Context& ctx);

void writeTopp10Divisjon(const DB::Context& ctx);
void writeTopp10Lag(const DB::Context& ctx);


//
// HELPER FUNCTIONS
//
void printSpiller(const DB::Spiller& spiller);
void printIdrett(const DB::Idrett& idrett);

//
// BACKGROUND FUNCTIONS
//
void readIdrettene(DB::Idrettene& ctx, const std::string filepath);
void writeIdrettene(DB::Idrettene& ctx, const std::string filepath);
void readSpillerene(DB::Spillerene& ctx, const std::string filepath);
void writeSpillerene(DB::Spillerene& ctx, const std::string filepath);


} // end namespace gruppe32::App