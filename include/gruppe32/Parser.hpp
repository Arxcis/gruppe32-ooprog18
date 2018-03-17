#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <string_view>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

/// <summary> Parsing strings to internal datastructure and vice versa </summary>
    namespace gruppe32::Parser
{


using std::size_t;
using std::string;
using std::pair;
using std::string_view;

class KeyValueGenerator 
{
public:
    string_view strview;
    size_t startofline =  0;
    
    auto nextLine() -> string;
    auto nextStringStringPair() -> pair<string,string>;
    auto nextStringUintPair() -> pair<string, size_t>;
    auto nextStringBoolPair() -> pair<string, bool>;
};


using std::string;
using std::stringstream;
using std::size_t;

class LinePrinter 
{
public:
    string outString = "";

    void lineEmpty();
    void lineString(const string key, const size_t indentCount);
    void lineStringString(const string key, const string value, const size_t indentCount);
    void lineStringUint(const string key, const size_t value, const size_t indentCount);
    void lineStringBool(const string key, const bool value, const size_t indentCount);
    void lineDashStringString(const string key, const string value, const size_t indentCount);
    void lineDashStringUint(const string key, const size_t value, const size_t indentCount); 
    auto getString() -> string;
};


using std::size_t;
using std::string;
using std::string_view;
using std::vector;
using DB::Idrettene;
using DB::Spillerene;
using Error = std::size_t;

constexpr Parser::Error ERROR = 1;


/// <summary> Encode. Has a corresponding decode function. </summary>
/// <returns> string - example found in format-idrettene.yml </returns>
auto encodeIdrettene(DB::Idrettene& idrettene) -> string;

/// <summary> Encode. Has a corresponding decode function. </summary>
/// <returns> string - example found in format-spillerene.yml </returns>
auto encodeSpillerene(DB::Spillerene& spillerene) -> string;

/// <summary> Decode. Has a corresponding encode function. </summary>
/// <param name="strview"> example found in format-idrettene.yml </param>
auto decodeIdrettene(DB::Idrettene& idrettene, string_view strview) -> Parser::Error;

/// <summary> Decode. Has a corresponding encode function. </summary>
/// <param name="strview"> example found in format-spillerene.yml </param>
auto decodeSpillerene(DB::Spillerene& spillerene, string_view strview) -> Parser::Error;



/// <summary> Encode-only. </summary>
/// <returns> string - example found in format-resultatene-divisjon.yml </returns>
auto encodeResultateneDivisjon(const vector<DB::ResultatWithKeys>& resultatene) -> string;

/// <summary> Encode-only.</summary>
/// <returns> string - example found in format-resultatene-idrett.yml </returns>
auto encodeResultateneIdrett(const vector<DB::ResultatWithKeys>& resultatene) -> string;

/// <summary> Encode-only. </summary>
/// <returns> string - example found in format-tabell-divisjon.yml </returns>
auto encodeTabellDivisjon(const DB::TabellDivisjon& tabellDivisjon) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-tabellene-idrett.yml </returns>
auto encodeTabelleneIdrett(const vector<DB::TabellDivisjon&> tabellIdrett) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-terminliste-divisjon.yml </returns>
auto encodeTerminlisteDivisjon(const DB::Terminliste terminliste) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-toppscorerene-divisjon.yml </returns>
auto encodeToppscorereneDivisjon(const DB::Toppscorerene& toppscorerene) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-toppscorerene-lag.yml </returns>
auto encodeToppscorereneLag(const DB::Toppscorerene& toppscorerene, const string lagnavn) -> string;



/// <summary> Decode-only. </summary>
/// <param name="resultatene"> Resultat with additional keys representing hierarchy </param>
/// <param name="strview"> example found in format-resultatene.yml </param>
auto decodeResultatene(vector<DB::ResultatWithKeys>& resultatene, string_view strview) -> Parser::Error;

/// <summary> Decode-only. </summary>
/// <param name="strview"> example found in format-divisjon.yml </param>
auto decodeDivisjon(DB::Divisjon& divisjon, string_view strview) -> Parser::Error; 



} // end namespace Parse